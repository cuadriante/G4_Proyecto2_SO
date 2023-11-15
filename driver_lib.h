#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>

int serial_open(const char *dev);
void serial_close(int fd);
int serial_read(int fd, char *buf, int len);
int serial_write(int fd, char *buf, int len);