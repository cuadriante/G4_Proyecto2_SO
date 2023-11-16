//
// Created by usuario on 8/24/23.
//

#include "serverInit.h"

/**
 * Inicia el servidor con los parámetros proporcionados y acepta conexiones entrantes.
 *
 * @param SERV_PORT Puerto en el que se inicia el servidor.
 * @param SERV_HOST_ADDR Dirección IP en la que se inicia el servidor.
 * @param histoPath Ruta al directorio para el histograma.
 * @param colorPath Ruta al directorio para los colores.
 * @param logPath Ruta al archivo de registro.
 * @return 0 si la operación se realiza con éxito, -1 en caso de error.
 */
int serverOn(int SERV_PORT, char* SERV_HOST_ADDR, int S3, int S1, int S2){
    int sockfd, connfd ;  /* listening socket and connection socket file descriptors */
    unsigned int len;     /* length of client address */
    struct sockaddr_in servaddr, client;

    int len_rx, len_tx = 0;                     /* received and sent length, in bytes */
    char buff_tx[BUF_SIZE] = "Hello client, I am the server";
    char buff_rx[BUF_SIZE];   /* buffers for reception  */


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
                    snprintf(filename, sizeof(filename), "/home/curso/Desktop/sharedfolder/encrypt%d.txt", i);
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
                command = malloc(1000);

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

void executeCommand(struct Core *currentCore, int coreAmount, char* command, int nDiv, int ogSize) {
    if (strcmp(currentCore->name, "S3") == 0) {
        /*Mandar mensaje de ejecutar con la cantidad de nodos en coreAmount al server master
          y con el numero de txt que le toca decifrar
        */
        printf("Realizar comando en %s con %d nucleos.\n", currentCore->name, coreAmount);
        char restCommand[200];
        snprintf(restCommand, sizeof (restCommand),
                 "--cpu-set %d-%d --bind-to core -n %d --hostfile /home/curso/Desktop/sharedfolder/hostfile3 -np 1 /home/curso/Desktop/sharedfolder/slaveExecutable %d %d : ",
                 (currentCore->count - coreAmount), (currentCore->count - 1), coreAmount, nDiv, ogSize);

        strcat(command, restCommand);



    } else if (strcmp(currentCore->name, "S1") == 0) {
        /*Mandar mensaje de ejecutar con la cantidad de nodos en coreAmount al server slave1
          y con el numero de txt que le toca decifrar
        */
        printf("Realizar comando en %s con %d nucleos.\n", currentCore->name, coreAmount);
        char restCommand[200];
        snprintf(restCommand, sizeof(restCommand),
                 "--cpu-set %d-%d --bind-to core -n %d --hostfile /home/curso/Desktop/sharedfolder/hostfile1 -np 1 /home/curso/Desktop/sharedfolder/slaveExecutable %d %d : ",
                 (currentCore->count - coreAmount), (currentCore->count - 1), coreAmount, nDiv, ogSize);

        strcat(command, restCommand);

    } else if (strcmp(currentCore->name, "S2") == 0) {
        /*Mandar mensaje de ejecutar con la cantidad de nodos en coreAmount al server slave2
          y con el numero de txt que le toca decifrar
        */
        printf("Realizar comando en %s con %d nucleos.\n", currentCore->name, coreAmount);
        char restCommand[200];
        snprintf(restCommand, sizeof (restCommand),
                 "--cpu-set %d-%d --bind-to core -n %d --hostfile /home/curso/Desktop/sharedfolder/hostfile2 -np 1 /home/curso/Desktop/sharedfolder/slaveExecutable %d %d : ",
                 (currentCore->count - coreAmount), (currentCore->count - 1), coreAmount, nDiv, ogSize);

        strcat(command, restCommand);
    }
}

// Función para asignar nodos a los cores
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

void delete(){
    int i = 1;
    while (1){
        char filename[100];
        snprintf(filename, sizeof(filename), "/home/curso/Desktop/sharedfolder/encrypt%d.txt", i);
        if (remove(filename) == 0){
            printf("File %s deleted succesfully. \n", filename);
        }
        else{
            break;
        }
        i++;
    }
}