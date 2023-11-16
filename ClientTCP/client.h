#ifndef CLIENTE_CLIENT_H
#define CLIENTE_CLIENT_H
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <ctype.h>
#include <malloc.h>
#include "chacha20.h"


int clientMessage(char *SERVER_ADDRESS, int PORT, char *buf_tx,  char *nDiv);
char *read_txt(const char *txt);
void countWordsAndFindCuts(const char *text, int *wordCount, int cutIndices[], int n);
void save(int cuts, int *cutIndices, const char *plaintext, uint8_t *key, uint32_t counter,  uint8_t *nonce,int *ogSizes);
void save_crypto(const char *txt, unsigned char *crypto, unsigned long txt_len);
void delete();
char *read_hex_file(const char *filename);
#endif //CLIENTE_CLIENT_H
