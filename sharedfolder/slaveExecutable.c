#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>
#include "chacha20.h"
#include <ctype.h>
#include "mpi.h"

#define MAX_WORD_LENGTH 100

void findMostRepeatedWord(const char *filename, int index, int rank) {
    FILE *file;
    char ch, *line;
    size_t len = 0, read;
    char **words = NULL;
    char word[MAX_WORD_LENGTH];
    int i = 0, j, k, maxCount = 0, count;

    // Opens file in read mode
    file = fopen(filename, "r");

    // If file doesn't exist
    if (file == NULL) {
        printf("File not found\n");
        return;
    }

    // Reads the file line by line and splits content into words
    while ((read = getline(&line, &len, file)) != -1) {
        j = 0;
        k = 0;
        while (line[k] != '\0') {
            if (line[k] != ' ' && line[k] != '\n' && line[k] != ',' && line[k] != '.') {
                word[j++] = tolower(line[k]);
            } else {
                word[j] = '\0';
                if (j > 0) {
                    words = realloc(words, (i + 1) * sizeof(char *));
                    words[i] = malloc((strlen(word) + 1) * sizeof(char));
                    strcpy(words[i], word);
                    i++;
                }
                j = 0;
            }
            k++;
        }
    }

    int length = i;

    // Determines the most repeated word in the file
    for (i = 0; i < length; i++) {
        count = 1;
        for (j = i + 1; j < length; j++) {
            if (strcmp(words[i], words[j]) == 0 && (strcmp(words[i], " ") != 0)) {
                count++;
            }
        }
        if (count > maxCount) {
            maxCount = count;
            strcpy(word, words[i]);
        }
    }
	printf("La palbra mas repetida en la parte %d es: %s (se repite %d veces)\n", index, word, maxCount);
	
    // Free allocated memory
    for (i = 0; i < length; i++) {
        free(words[i]);
    }
    free(words);

    fclose(file);
}


// Función para leer una cadena hexadecimal desde un archivo de texto
char *read_hex_file(const char *filename) {
    FILE *pFile = fopen(filename, "r");

    if (pFile == NULL) {
        printf("No se pudo abrir el pFile %s\n", filename);
        return NULL;
    }

    fseek(pFile, 0, SEEK_END);
    long txt_len = ftell(pFile);
    fseek(pFile, 0, SEEK_SET);

    char *hex_text = (char *)malloc(txt_len + 1);

    if (hex_text == NULL) {
        fclose(pFile);
        printf("Error en la asignación de memoria.\n");
        return NULL;
    }

    fread(hex_text, 1, txt_len, pFile);
    hex_text[txt_len] = '\0';

    fclose(pFile);
    return hex_text;
}


char *hex_to_char(const char *hex_txt) {
    int txt_len = strlen(hex_txt);
    char *text_hex = (char *)malloc(txt_len / 2 + 1);

    if (text_hex == NULL) {
        printf("Error en la asignación de memoria.\n");
        return NULL;
    }

    for (int i = 0, j = 0; i < txt_len; i += 2, j++) {
        char byte[3];
        byte[0] = hex_txt[i];
        byte[1] = hex_txt[i + 1];
        byte[2] = '\0';
        text_hex[j] = (char)strtol(byte, NULL, 16);
    }

    text_hex[txt_len / 2] = '\0';
    return text_hex;
}



int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <index> <size>\n", argv[0]);
        return 1;
    }

    int index = atoi(argv[1]); // Convert the first argument to an integer
    int OGsize = atoi(argv[2]);  // Convert the second argument to an integer

    // Your code using 'index' and 'size'

    printf("Index: %d, Size: %d\n", index, OGsize);

    int rank, size, len;
    char version[MPI_MAX_LIBRARY_VERSION_STRING];

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Get_library_version(version, &len);

    uint8_t key[32] = {"00112233445566778899AABBCCDDEEFF"};
    uint32_t counter = 0; // Initial counter value
    uint8_t nonce[12] = {"0000000000F0F1F2"};

    uint8_t decrypted_text[OGsize];

    char filename [100];
    snprintf(filename, sizeof(filename), "/home/curso/Desktop/sharedfolder/encrypt%d.txt", index);
    char *hex_text = read_hex_file(filename);
    char *u_char = NULL;

    if (hex_text != NULL) {
        u_char = hex_to_char(hex_text);
    }

    ChaCha20XOR(key, counter, nonce, u_char, decrypted_text, OGsize);

    char filename_d [100];
    snprintf(filename_d, sizeof(filename_d), "/home/curso/Desktop/sharedfolder/decrypted%d.txt", index);
    FILE *file = fopen(filename_d, "w");

    if (file != NULL) {
        // Escribir la cadena en el archivo
        fprintf(file, "%s", decrypted_text);

        // Cerrar el archivo
        fclose(file);
        printf("El contenido se ha guardado en el archivo \"%s\".\n", filename_d);

    } else {
        printf("Error al abrir el archivo \"%s\" para escritura.\n", filename_d);

    }
    findMostRepeatedWord(filename_d, index, rank);

    MPI_Finalize();

    return 0;

}

