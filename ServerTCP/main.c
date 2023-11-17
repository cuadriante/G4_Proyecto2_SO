#include "serverInit.h"
/**
 * Función principal del programa. Lee la configuración desde consola,
 * y luego inicia el servidor utilizando la
 * información de configuración proporcionada.
 *
 * @param argc Cantidad de argumentos de la línea de comandos (no utilizado).
 * @param argv Vector de argumentos de la línea de comandos (no utilizado).
 * @return 0 si la operación se realiza con éxito.
 **/
int main(int argc, char* argv[])          /* input arguments are not used */
{
    int S3, S1, S2;
    char S3Str[100];
    char S1Str[100];
    char S2Str[100];
    char *endptr;

    while(1){
        printf("Ingrese la cantidad de nucleos del server Slave 1: ");
        scanf("%s", S3Str);
        S3 = strtol(S3Str, &endptr, 10);
        if(endptr == S3Str){
            printf("Número con el formato incorrecto, por favor ingreselo nuevamente\n");
        }
        else{
            break;
        }
    }

    while(1){
        printf("Ingrese la cantidad de nucleos del server Slave 2: ");
        scanf("%s", S1Str);
        S1 = strtol(S1Str, &endptr, 10);
        if(endptr == S1Str){
            printf("Número con el formato incorrecto, por favor ingreselo nuevamente\n");
        }
        else{
            break;
        }
    }

    while(1){
        printf("Ingrese la cantidad de nucleos del server Slave 3: ");
        scanf("%s", S2Str);
        S2 = strtol(S2Str, &endptr, 10);
        if(endptr == S2Str){
            printf("Número con el formato incorrecto, por favor ingreselo nuevamente\n");
        }
        else{
            break;
        }
    }

    char* address = "0.0.0.0";
    serverOn(8888, address, S3, S1, S2);
    return 0;
}
