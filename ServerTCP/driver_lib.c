#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include "driver_lib.h"


void enviarCaracteresSerial(const char *caracteres) {
    const char *puerto_serial = "/dev/ttyACM0"; // Cambia esto al puerto COM correcto en sistemas Windows

    // Abre el puerto serial
    int fd = open(puerto_serial, O_RDWR | O_NOCTTY | O_NDELAY);
    if (fd == -1) {
        perror("Error al abrir el puerto serial");
        exit(EXIT_FAILURE);
    }

    // Configura la estructura termios para la comunicación serial
    struct termios config;
    if (tcgetattr(fd, &config) < 0) {
        perror("Error al obtener la configuración del puerto serial");
        close(fd);
        exit(EXIT_FAILURE);
    }

    // Configura la velocidad del puerto serial
    cfsetispeed(&config, B9600);
    cfsetospeed(&config, B9600);

    // Configura los parámetros del puerto serial
    config.c_cflag &= ~PARENB; // Sin paridad
    config.c_cflag &= ~CSTOPB; // 1 bit de parada
    config.c_cflag &= ~CSIZE;
    config.c_cflag |= CS8;     // 8 bits de datos
    config.c_cflag &= ~CRTSCTS; // Desactiva control de flujo

    // Establece la configuración del puerto serial
    if (tcsetattr(fd, TCSANOW, &config) < 0) {
        perror("Error al aplicar la configuración del puerto serial");
        close(fd);
        exit(EXIT_FAILURE);
    }

    // Espera a que la conexión serial se establezca (2 segundos)
    sleep(2);

    // Envía la cadena de caracteres por el puerto serial
    size_t longitud = strlen(caracteres);
    if (write(fd, caracteres, longitud) != longitud) {
        perror("Error al escribir en el puerto serial");
    }

    // Cierra el puerto serial
    close(fd);
}

// Ejemplo de uso
// int main() {
//     enviarCaracteresSerial("-'esi");
//     return 0;
// }
