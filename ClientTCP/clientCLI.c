//
// Created by usuario on 8/26/23.
//

#include "clientCLI.h"
#include "client.h"
/**
 * Muestra un menú interactivo en consola para que el usuario ingrese información necesaria
 * y luego envía un mensaje al servidor utilizando la función clientMessage.
 *
 * @return 0 si la operación se realiza con éxito.
 */
int clientMenu() {
    char exitStr[100];
    while (1){
        char portStr[100];
        char address[100];
        char txt[100];
        char nDivStr[100];
        char *endptr;
        long int port;
        long int nDiv;

        printf("Ingrese la ip del servidor: ");
        scanf("%s", address);

        while(1){
            printf("Ingrese el port en el que desea escribir: ");
            scanf("%s", portStr);
            port = strtol(portStr, &endptr, 10);
            if(endptr == portStr){
                printf("Número con el formato incorrecto, por favor ingreselo nuevamente\n");
            }
            else{
                break;
            }
        }

        printf("Ingrese el nombre del txt que desea encriptar: ");
        scanf("%s", txt);

        while(1){
            printf("Elige en cuantas partes desea dividir el txt: ");
            scanf("%s", nDivStr);
            nDiv = strtol(nDivStr, &endptr, 10);
            if(endptr == nDivStr || nDiv < 0){
                printf("Número con el formato incorrecto, por favor ingreselo nuevamente\n");
            }
            else{
                break;
            }
        }

        clientMessage(address, port, txt, nDivStr);

        printf("Escriba \"Exit\" si desea salir: ");
        scanf("%s", exitStr);
        if (!(strcmp("Exit", exitStr))){
            break;
        }
    }
    return 0;
}
