//
// Created by usuario on 8/24/23.
//

#include <ctype.h>
#include "serverInit.h"
#include "driver_lib.h"

/**
 * This method initializes and runs the server on a specified port and host address,
 * handling incoming connections iteratively.
 *
 * @param SERV_PORT       The server port number.
 * @param SERV_HOST_ADDR  The server host address.
 * @param S3              The count for S3.
 * @param S1              The count for S1.
 * @param S2              The count for S2.
 * @return Returns 0 on successful server operation, -1 otherwise.
 */
int serverOn(int SERV_PORT, char* SERV_HOST_ADDR, int S3, int S1, int S2){
    int sockfd, connfd ;  /* listening socket and connection socket file descriptors */
    unsigned int len;     /* length of client address */
    struct sockaddr_in servaddr, client;

    int len_rx, len_tx = 0;                     /* received and sent length, in bytes */
    //char buff_tx[BUF_SIZE] = "Hello client, I am the server";
    //char buff_rx[BUF_SIZE];   /* buffers for reception  */


    /* socket creation */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1)
    {
        fprintf(stderr, "[SERVER-error]: socket creation failed. %d: %s \n", errno, strerror( errno ));
        return -1;
    }
    else
    {
        printf("[SERVER]: Socket successfully created..\n");
    }

    /* clear structure */
    memset(&servaddr, 0, sizeof(servaddr));

    /* assign IP, SERV_PORT, IPV4 */
    servaddr.sin_family      = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr(SERV_HOST_ADDR);
    servaddr.sin_port        = htons(SERV_PORT);


    /* Bind socket */
    if ((bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr))) != 0)
    {
        fprintf(stderr, "[SERVER-error]: socket bind failed. %d: %s \n", errno, strerror( errno ));
        return -1;
    }
    else
    {
        printf("[SERVER]: Socket successfully binded \n");
    }

    /* Listen */
    if ((listen(sockfd, BACKLOG)) != 0)
    {
        fprintf(stderr, "[SERVER-error]: socket listen failed. %d: %s \n", errno, strerror( errno ));
        return -1;
    }
    else
    {
        printf("[SERVER]: Listening on SERV_IP %s \n", inet_ntoa(servaddr.sin_addr));
        printf("[SERVER]: Listening on SERV_PORT %d \n\n", ntohs(servaddr.sin_port) );
    }

    len = sizeof(client);
    /* Accept the data from incoming sockets in a iterative way */
    while(1)
    {
        connfd = accept(sockfd, (struct sockaddr *)&client, &len);
        if (connfd < 0)
        {

            fprintf(stderr, "[SERVER-error]: connection not accepted. %d: %s \n", errno, strerror( errno ));
            return -1;
        }
        else
        {
            while(1) /* read data from a client socket till it is closed */
            {

                //Size name
                int name_size = 0;
                len_rx = read(connfd, &name_size, sizeof(int));

                if(len_rx < 0){
                    fprintf(stderr, "[SERVER-error]: Size could not be read. %d: %s \n", errno, strerror( errno ));
                }

                printf("Size name: %d \n", name_size);

                char *file_name = NULL;
                file_name = malloc(name_size);

                //Name txt
                len_rx = read(connfd, file_name, name_size);
                if(len_rx < 0){
                    fprintf(stderr, "[SERVER-error]: Name could not be read. %d: %s \n", errno, strerror( errno ));
                }
                printf("Name txt: %s\n", file_name);

                //Size name
                int nDiv = 0;
                len_rx = read(connfd, &nDiv, sizeof(int));

                if(len_rx < 0){
                    fprintf(stderr, "[SERVER-error]: Amount of divisions not be read. %d: %s \n", errno, strerror( errno ));
                }

                printf("Amount of divisions: %d \n", nDiv);

                int ogSizes[nDiv+1];

                delete();


                for (int i = 1; i < nDiv+1; i++){
                    //OG Size text
                    int og_size = 0;
                    len_rx = read(connfd, &og_size, sizeof(int));

                    if(len_rx < 0){
                        fprintf(stderr, "[SERVER-error]: Size could not be read. %d: %s \n", errno, strerror( errno ));
                    }
                    ogSizes[i] = og_size;
                    printf("OG Size: %d \n", ogSizes[i]);

                    //Size text
                    int buffer_size = 0;
                    len_rx = read(connfd, &buffer_size, sizeof(int));

                    if(len_rx < 0){
                        fprintf(stderr, "[SERVER-error]: Size could not be read. %d: %s \n", errno, strerror( errno ));
                    }

                    printf("Size txt: %d \n", buffer_size);

                    //Txt content

                    char *buffer = NULL;
                    buffer = malloc(buffer_size);

                    char *tempB = NULL;
                    tempB = malloc(buffer_size);

                    int tempL = 0;
                    while(tempL < buffer_size){
                        len_rx = read(connfd, buffer, buffer_size-tempL);
                        if (len_rx <=0){
                            break;
                        }
                        tempB = concat(tempB, buffer, tempL, len_rx);

                        tempL += len_rx;
                        //printf("Receiving data...\n");
                    }

                    if(tempL < buffer_size || tempL < 0){
                        fprintf(stderr, "[SERVER-error]: File could not be read. %d: %s \n", errno, strerror( errno ));
                    }

                    tempB [buffer_size] = '\0';

                    char filename[100];
                    snprintf(filename, sizeof(filename), "/home/adri/Desktop/sharedfolder/encrypt%d.txt", i);
                    printf("Save in file: %s\n", filename);

                    FILE *file = fopen(filename, "w");

                    if(file != NULL){
                        fprintf(file, "%s", tempB);
                        fclose(file);
                    }
                    else{
                        fprintf(stderr, "[SERVER-error]: File could not be opened. %d: %s \n", errno, strerror( errno ));
                    }

                    free(buffer);
                    free(tempB);
                }

                printf("[SERVER]: client socket closed \n\n");
                close(connfd);
                free(file_name);

                //Division de trabajo
                struct Core cores[] = {{"S3", S3}, {"S1", S1}, {"S2", S2}};

                int totalCores = cores[0].count + cores[1].count + cores[2].count;


                char *command = NULL;
                command = malloc(3500);

                command[0] = 'm';
                command[1] = 'p';
                command[2] = 'i';
                command[3] = 'r';
                command[4] = 'u';
                command[5] = 'n';
                command[6] = ' ';


                assignNodes(cores, totalCores, nDiv, command, ogSizes);

                printf("\n%s\n", command);

                int status = system(command);

                char filename_r[] = "/home/adri/Desktop/sharedfolder/mostRepeated1.txt";

                char* mostrepeated = read_txt(filename_r);

                printf("La palabra mas repetida en la parte 1: %s\n", mostrepeated);

                char* morseCode = textToMorse(mostrepeated);

                printf("La palabra mas repetida en la parte 1 (codigo morse): %s\n", morseCode);

                char resultado[15];

                // Copia la cadena original a la nueva cadena
                strcpy(resultado, morseCode);

                // Transforma la cadena
                transformarString(resultado);

                printf("Resultado: %s\n", resultado);

                sleep(2);
                enviarCaracteresSerial(morseCode);

                free(command);

                break;

            }
        }
    }
}
/**
 * Concatena dos cadenas de caracteres y devuelve el resultado.
 *
 * @param str1 La primera cadena de caracteres.
 * @param str2 La segunda cadena de caracteres.
 * @param l1 La longitud de la primera cadena.
 * @param l2 La longitud de la segunda cadena.
 * @return Una nueva cadena que es la concatenación de str1 y str2.
 */
char* concat(char const *str1, char const *str2, const size_t l1, size_t const l2){
    char *result = malloc(l1+ l2+ 1);
    if(!result) return result;
    memcpy(result, str1, l1);
    memcpy(result+l1, str2, l2+1);
    return result;
}
/**
 * Executes a specific command based on the current core, core amount, division number, and original size.
 * Updates the 'command' string with the executed command.
 *
 * @param currentCore The current core for execution.
 * @param coreAmount  The number of cores to execute the command.
 * @param command     The command string to be updated.
 * @param nDiv        The division number.
 * @param ogSize      The original size of the data.
 */
void executeCommand(struct Core *currentCore, int coreAmount, char* command, int nDiv, int ogSize) {
    if (strcmp(currentCore->name, "S3") == 0) {
        /*Mandar mensaje de ejecutar con la cantidad de nodos en coreAmount al server master
          y con el numero de txt que le toca decifrar
        */
        printf("Realizar comando en %s con %d nucleos.\n", currentCore->name, coreAmount);
        char restCommand[200];
        snprintf(restCommand, sizeof (restCommand),
                 "--cpu-set %d-%d --bind-to core -n %d --hostfile /home/adri/Desktop/sharedfolder/hostfile3 -np 1 /home/curso/Desktop/sharedfolder/slaveExecutable %d %d : ",
                 (currentCore->count - coreAmount), (currentCore->count - 1), coreAmount, nDiv, ogSize);

        strcat(command, restCommand);



    } else if (strcmp(currentCore->name, "S1") == 0) {
        /*Mandar mensaje de ejecutar con la cantidad de nodos en coreAmount al server slave1
          y con el numero de txt que le toca decifrar
        */
        printf("Realizar comando en %s con %d nucleos.\n", currentCore->name, coreAmount);
        char restCommand[200];
        snprintf(restCommand, sizeof(restCommand),
                 "--cpu-set %d-%d --bind-to core -n %d --hostfile /home/adri/Desktop/sharedfolder/hostfile1 -np 1 /home/curso/Desktop/sharedfolder/slaveExecutable %d %d : ",
                 (currentCore->count - coreAmount), (currentCore->count - 1), coreAmount, nDiv, ogSize);

        strcat(command, restCommand);

    } else if (strcmp(currentCore->name, "S2") == 0) {
        /*Mandar mensaje de ejecutar con la cantidad de nodos en coreAmount al server slave2
          y con el numero de txt que le toca decifrar
        */
        printf("Realizar comando en %s con %d nucleos.\n", currentCore->name, coreAmount);
        char restCommand[200];
        snprintf(restCommand, sizeof (restCommand),
                 "--cpu-set %d-%d --bind-to core -n %d --hostfile /home/adri/Desktop/sharedfolder/hostfile2 -np 1 /home/curso/Desktop/sharedfolder/slaveExecutable %d %d : ",
                 (currentCore->count - coreAmount), (currentCore->count - 1), coreAmount, nDiv, ogSize);

        strcat(command, restCommand);
    }
}

/**
 * Assigns nodes to cores based on division and original sizes, updating the 'command' string accordingly.
 *
 * @param cores       Array of cores.
 * @param totalCores  Total number of available cores.
 * @param nDiv        Division number.
 * @param command     The command string to be updated.
 * @param ogSizes     Array containing original sizes.
 */
void assignNodes(struct Core *cores, int totalCores, int nDiv, char* command, int *ogSizes) {
    while (nDiv > 0) {
        if (nDiv > totalCores) {
            printf("Demasiadas divisiones\n");
            break;
        }

        struct Core *currentCore = &cores[0];
        for (int i = 1; i < 3; ++i) {
            if (cores[i].count > currentCore->count) {
                currentCore = &cores[i];
            }
        }

        for (int i = 3; i <= totalCores; i += 3) {
            if (nDiv <= i) {
                int coreAmount = currentCore->count / (i / 3);
                int ogSize = ogSizes[nDiv];
                executeCommand(currentCore, coreAmount, command, nDiv, ogSize);
                currentCore->count -= coreAmount;
                break;
            }
        }

        nDiv -= 1;
        printf("Asignado al %s, le quedan %d nucleos. Y quedan %d procesos.\n", currentCore->name, currentCore->count, nDiv);
    }
}
/**
 * Deletes files in a specific directory.
 */
void delete(){
    int i = 1;
    while (1){
        char filename[100];
        snprintf(filename, sizeof(filename), "/home/adri/Desktop/sharedfolder/encrypt%d.txt", i);
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
 * Reads a text file and returns its content as a string.
 *
 * @param txt The path to the text file.
 * @return    Returns the content of the text file as a string.
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
 * Converts a text string into Morse code.
 *
 * @param text The input text to be converted.
 * @return     Returns the Morse code representation of the input text.
 */
char* textToMorse(const char *text) {
    const char morseCode[][5] = {
            ".-", "-...", "-.-.", "-..", ".",
            "..-.", "--.", "....", "..", ".---",
            "-.-", ".-..", "--", "-.", "---",
            ".--.", "--.-", ".-.", "...", "-",
            "..-", "...-", ".--", "-..-", "-.--",
            "--.."
    };
    const char *alpha = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int i, j;
    int resultLength = 0;

    // Calcular la longitud del resultado morse
    for (i = 0; text[i]; i++) {
        if (text[i] == ' ') {
            resultLength++;
        } else {
            for (j = 0; j < strlen(alpha); j++) {
                if (toupper(text[i]) == alpha[j]) {
                    resultLength += strlen(morseCode[j]) + 1; // +1 para el espacio entre letras
                    break;
                }
            }
        }
    }

    // Crear la variable para almacenar el resultado morse
    char *result = (char *)malloc(sizeof(char) * resultLength);
    if (result == NULL) {
        printf("Error al asignar memoria.");
        return NULL;
    }

    // Convertir texto a morse y almacenar en 'result'
    int pos = 0;
    for (i = 0; text[i]; i++) {
        if (text[i] == ' ') {
            result[pos++] = ' ';
        } else {
            for (j = 0; j < strlen(alpha); j++) {
                if (toupper(text[i]) == alpha[j]) {
                    int len = strlen(morseCode[j]);
                    strcpy(result + pos, morseCode[j]);
                    pos += len;
                    result[pos++] = ' '; // Agregar espacio entre letras
                    break;
                }
            }
        }
    }
    result[pos] = '\0'; // Agregar terminador nulo al final

    return result;
}

/**
 * Transforms a string by replacing spaces with 'e', adding 'i' at the start, and 'f' at the end.
 *
 * @param input_str The input string to be transformed.
 */
void transformarString(char input_str[]) {
    int longitud = strlen(input_str);

    // Reemplaza espacios por 'e'
    for (int i = 0; i < longitud; i++) {
        if (input_str[i] == ' ') {
            input_str[i] = 'e';
        }
    }

    // Desplaza los caracteres para hacer espacio para 'i' al inicio y 'f' al final
    for (int i = longitud; i >= 0; i--) {
        input_str[i + 1] = input_str[i];
    }

    // Agrega 'i' al inicio y 'f' al final
    input_str[0] = 'i';
    input_str[longitud + 1] = 'f';
}