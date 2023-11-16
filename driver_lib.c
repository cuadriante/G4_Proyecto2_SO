// ftdi_serial_lib.c

#include "driver_lib.h"

int serial_open(const char *dev) {
  return open(dev, O_RDWR | O_NOCTTY); 
}

void serial_close(int fd) {
  close(fd);
}

struct termios set_interface_attribs(int fd, speed_t speed, int parity) {
  struct termios tty;
  memset(&tty, 0, sizeof tty);
  if (tcgetattr(fd, &tty) != 0) {
    return tty;
  }

  // Set baud rate
  cfsetospeed(&tty, speed);
  cfsetispeed(&tty, speed);

  // Enable the receiver and set local mode
  tty.c_cflag |= (CLOCAL | CREAD);

  // Set parity
  if (parity)
    tty.c_cflag |= PARENB;
  else 
    tty.c_cflag &= ~PARENB;

  // Set other options
  tty.c_cflag &= ~CSTOPB;
  tty.c_cflag &= ~CSIZE;
  tty.c_cflag |= CS8;
  tty.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
  tty.c_iflag &= ~(IXON | IXOFF | IXANY);

  tty.c_cc[VMIN] = 0;
  tty.c_cc[VTIME] = 5;
  
  if (tcsetattr(fd, TCSANOW, &tty) != 0) {
    return tty;
  }
  return tty;
}

int serial_read(int fd, char *buf, int len) {
  return read(fd, buf, len);
}

int serial_write(int fd, char *buf, int len) {  
  return write(fd, buf, len);
}

