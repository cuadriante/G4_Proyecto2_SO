#ifndef SERVIDOR_SERVERINIT_H
#define SERVIDOR_SERVERINIT_H
/*standard symbols */
#include <unistd.h>

/* sockets */
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>

/* strings / errors*/
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUF_SIZE        100
#define BACKLOG         5

struct Core {
    char name[3];  // Nombre del nodo (por ejemplo, "M0", "S1", "S2")
    int count;     // Cantidad de nodos
};

char* concat(char const *str1, char const *str2, size_t const l1, size_t const l2);
int serverOn(int SERV_PORT, char* SERV_HOST_ADDR, int S3, int S1, int S2);
void assignNodes(struct Core *cores, int totalCores, int nDiv, char* command, int *ogSizes);
void executeCommand(struct Core *currentCore, int coreAmount, char* command, int nDiv, int ogSize);
void delete();
char *read_txt(const char *txt);
char* textToMorse(const char *text);
void transformarString(char input_str[]);

#endif //SERVIDOR_SERVERINIT_H
