#include "driver_lib.h"

int main() {
  int fd = serial_open("/dev/ttyACMO0");
  
  set_interface_attribs(fd, B115200, 0); 
  
  char buf[256];
  
  int len = serial_read(fd, buf, 256);
  serial_write(fd, buf, len);
  
  serial_close(fd);
  return 0;
}