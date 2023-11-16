#include "driver_lib.h"
#include <unistd.h>
#include <string.h>

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

int main() {
    char entrada[] = "--. .- - .. - --- .-.-. ";

    // Asegúrate de que la cadena tenga suficiente espacio para 'i' y 'f' adicionales
    char resultado[50];

    // Copia la cadena original a la nueva cadena
    strcpy(resultado, entrada);

    // Transforma la cadena
    transformarString(resultado);

    // Envia la cadena transformada por el puerto serial
    enviarCaracteresSerial(resultado);

    return 0;
}
