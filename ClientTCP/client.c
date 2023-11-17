//
// Created by curso on 15/11/23.
//

#include "client.h"

/**
 * Establece una conexión de cliente con un servidor remoto y envía un mensaje.
 *
 * @param SERVER_ADDRESS La dirección IP del servidor al que se va a conectar.
 * @param PORT El número de puerto del servidor al que se va a conectar.
 * @param buf_tx El búfer que contiene los datos que se enviarán al servidor.
 * @param nDIv Cantidad de divisiones en la que se debe dividir el texto a encriptar.
 * @return 0 si la operación se realiza con éxito, -1 si hay un error.
 */
int clientMessage(char *SERVER_ADDRESS, int PORT, char *buf_tx, char *nDiv) {
    char buf_rx[100];
    int sockfd;
    struct sockaddr_in servaddr;

    /* Socket creation */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1)
    {
        printf("CLIENT: socket creation failed...\n");
        return -1;
    }
    else
    {
        printf("CLIENT: Socket successfully created..\n");
    }


    memset(&servaddr, 0, sizeof(servaddr));

    /* assign IP, PORT */
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr( SERVER_ADDRESS );
    servaddr.sin_port = htons(PORT);

    /* try to connect the client socket to server socket */
    if (connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) != 0)
    {
        printf("Connection with the server failed...\n");
        return -1;
    }

    printf("Connected to the server..\n");

    int8_t key[32] = {"00112233445566778899AABBCCDDEEFF"};
    uint32_t counter = 0; // Initial counter value
    uint8_t nonce[12] = {"0000000000F0F1F2"};
    char *endptr;
    int cuts = strtol(nDiv, &endptr, 10);


    int sizeBuffer = strlen(buf_tx);
    write(sockfd, &sizeBuffer, sizeof(int));
    write(sockfd, buf_tx, sizeBuffer);

    char file[260] = "/home/curso/CLionProjects/ClientTCP/";
    strcat(file, buf_tx);
    const char *plaintext = read_txt(file);

    int wordCount = 0;
    int cutIndices[cuts-1];  // índices de corte

    int ogSizes[cuts+1];

    // Contar palabras y encontrar índices de cortes
    countWordsAndFindCuts(plaintext, &wordCount, cutIndices, cuts);

    // Imprimir la cantidad de palabras y los índices de corte
    printf("Word Count: %d\n", wordCount);

    //Guardar encriptado
    delete();
    save(cuts, cutIndices, plaintext, key, counter, nonce, ogSizes);

    write(sockfd, &cuts, sizeof(int));

    for (int i = 1; i < cuts+1; i++){
        int ogSize = ogSizes[i];
        write(sockfd, &ogSize, sizeof(int));
        char filename[100];
        snprintf(filename, sizeof(filename), "/home/curso/CLionProjects/ClientTCP/encrypt%d.txt", i);
        char *hex_text = read_hex_file(filename);
        int hex_textlen = strlen(hex_text);
        write(sockfd, &hex_textlen, sizeof(int));
        write(sockfd, hex_text, hex_textlen);

    }

    /* close the socket */
    close(sockfd);
    return 0;
}

/**
 * Reads a text file and returns its content as a string.
 * 
 * @param txt The path to the text file to be read.
 * @return A dynamically allocated string containing the file content, or NULL if an error occurs.
 */
char *read_txt(const char *txt) {
    FILE *pFile = fopen(txt, "r");

    if (pFile == NULL) {
        printf("No se pudo abrir el pFile.\n");
        return NULL;
    }

    // Calcula el tamaño del pFile
    fseek(pFile, 0, SEEK_END);
    long file_len = ftell(pFile);
    fseek(pFile, 0, SEEK_SET);

    // Crea una cadena para almacenar el string del pFile
    char *string = (char *)malloc(file_len + 1);

    if (string == NULL) {
        fclose(pFile);
        printf("Error en la asignación de memoria.\n");
        return NULL;
    }

    // Lee el string del pFile
    fread(string, 1, file_len, pFile);
    string[file_len] = '\0'; // Añade el carácter nulo al final

    // Cierra el pFile
    fclose(pFile);

    return string;

}
/**
 * Counts words in a text and finds indices for cutting the text into parts based on a given ratio.
 * 
 * @param text The text to analyze.
 * @param wordCount Pointer to an integer to store the total word count.
 * @param cutIndices Array to store the indices where the text will be cut.
 * @param n The ratio for dividing the text into parts.
 */
void countWordsAndFindCuts(const char *text, int *wordCount, int cutIndices[], int n) {
    int length = strlen(text);
    int words = 0;
    int inWord = 0;  // Flag para indicar si estamos dentro de una palabra
    int targetIndexInitial = length / n;
    int targetIndex = targetIndexInitial;
    int index = 0;


    // Contar palabras y encontrar índices de cortes
    for (int i = 0; i < length; i++) {

        if (isspace(text[i]) || ispunct(text[i])) {
            // Si el carácter actual es espacio o signo de puntuación, no estamos en una palabra
            inWord = 0;
            // Calculamos el índice del corte correspondiente

            // Si alcanzamos el índice deseado, almacenamos el índice del corte
            if (i >= targetIndex) {
                cutIndices[index] = i + 1;
                targetIndex = targetIndex + targetIndexInitial;
                index = index + 1;
            }
        } else {
            // Si el carácter actual no es espacio ni signo de puntuación y no estábamos en una palabra,
            // incrementamos el contador de palabras y marcamos que estamos dentro de una palabra
            if (!inWord) {
                inWord = 1;
                words++;
            }
        }
    }
    *wordCount = words;  // Actualizamos el recuento total de palabras
}
/**
 * Divides a text into parts, encrypts each part, and saves them in separate files.
 * 
 * @param cuts The number of cuts for dividing the text.
 * @param cutIndices Array of indices indicating where the text will be cut.
 * @param plaintext The original text to be divided and encrypted.
 * @param key The encryption key.
 * @param counter The counter for encryption.
 * @param nonce The nonce for encryption.
 * @param ogSizes Array to store the sizes of the original parts.
 */
void save(int cuts, int *cutIndices, const char *plaintext, uint8_t *key, uint32_t counter,  uint8_t *nonce, int *ogSizes) {
    char filename[100];
    for (int i=0; i<cuts; i++){
        if (i == 0){
            int len = cutIndices[0] + 1 ;
            char part[len];
            uint8_t ciphertext[len];
            // Dividir el texto en partes
            strncpy(part, plaintext, cutIndices[0]);
            part[cutIndices[0]] = '\0';
            ChaCha20XOR(key, counter, nonce, (uint8_t *)part, ciphertext, len);
            sprintf(filename, "/home/curso/CLionProjects/ClientTCP/encrypt%d.txt", i+1);
            save_crypto(filename, ciphertext, len);

            printf("%s %d \n", filename, len);
            ogSizes[i+1] = len;
        }
        else if (i == cuts - 1){
            int len = strlen(plaintext) - cutIndices[i-1] + 1;
            char part[len];
            uint8_t ciphertext[len];
            strncpy(part, plaintext + cutIndices[i-1], strlen(plaintext) - cutIndices[i-1]);
            part[strlen(plaintext) - cutIndices[i-1]] = '\0';
            ChaCha20XOR(key, counter, nonce, (uint8_t *)part, ciphertext, len);
            sprintf(filename, "/home/curso/CLionProjects/ClientTCP/encrypt%d.txt", i+1);
            save_crypto(filename, ciphertext, len);
            printf("%s %d \n", filename, len);
            ogSizes[i+1] = len;
        }
        else{
            int len = cutIndices[i] - cutIndices[i-1] + 1;
            char part[len];
            uint8_t ciphertext[len];
            strncpy(part, plaintext + cutIndices[i-1], cutIndices[i] - cutIndices[i-1]);
            part[cutIndices[i] - cutIndices[i-1]] = '\0';
            ChaCha20XOR(key, counter, nonce, (uint8_t *)part, ciphertext, len);
            sprintf(filename, "/home/curso/CLionProjects/ClientTCP/encrypt%d.txt", i+1);
            save_crypto(filename, ciphertext, len);
            printf("%s %d \n", filename, len);
            ogSizes[i+1] = len;
        }

    }
}

/**
 * Saves encrypted text into a file in hexadecimal format.
 * 
 * @param txt The path to the file where the encrypted text will be saved.
 * @param crypto The encrypted text.
 * @param txt_len The length of the encrypted text.
 */
void save_crypto(const char *txt, unsigned char *crypto, unsigned long txt_len) {
    FILE *pFile = fopen(txt, "w");

    if (pFile == NULL) {
        printf("No se pudo abrir el pFile %s.\n", txt);
        return;
    }

    for (size_t i = 0; i < txt_len; i++) {
        fprintf(pFile, "%02X", crypto[i]);
    }

    // Cierra el pFile
    fclose(pFile);
}
/**
 * Deletes encrypted files.
 */
void delete(){
    int i = 1;
    while (1){
        char filename[100];
        snprintf(filename, sizeof(filename), "/home/curso/CLionProjects/ClientTCP/encrypt%d.txt", i);
        if (remove(filename) == 0){
            printf("File %s deleted succesfully. \n", filename);
        }
        else{
            break;
        }
        i++;
    }
}
/**
 * Reads a file containing hexadecimal text and returns it as a string.
 * 
 * @param filename The path to the file containing hexadecimal text.
 * @return A dynamically allocated string containing the hexadecimal text, or NULL if an error occurs.
 */
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