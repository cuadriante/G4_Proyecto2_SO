CC = gcc
CFLAGS = -Wall -Wextra

SRCS = main.c client.c clientCLI.c chacha20.c
TARGET = clientTCP

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o $@

clean:
	rm -f $(TARGET)
