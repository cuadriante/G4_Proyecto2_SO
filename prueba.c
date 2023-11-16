#include "driver_lib.h"
#include <unistd.h>

int main() {
  // Execute command "e"
  Execute("e");

  // Sleep for 5 seconds
  sleep(5);

  return 0;
}
