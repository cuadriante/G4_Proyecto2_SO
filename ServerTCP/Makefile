CC = gcc
CFLAGS = -Wall -Wextra

SRCS = main.c serverInit.c driver_lib.c
TARGET = serverTCP

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o $@

clean:
	rm -f $(TARGET)