CC = mpicc
CFLAGS = -Wall -Wextra

SRCS = slaveExecutable.c chacha20.c
TARGET = slaveExecutable

HOSTFILES = hostfile0 hostfile1 hostfile2 hostfile3

all: $(TARGET) create_hostfiles

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o $@

create_hostfiles:
	echo "127.0.0.1   slots=4    localhost" > hostfile0
	echo "curso@172.18.97.7    slots=6    slave1" > hostfile1
	echo "curso@172.18.61.192    slots=6    slave2" > hostfile2
	echo "curso@172.18.67.245    slots=6    slave3" > hostfile3

clean:
	rm -f $(TARGET) $(HOSTFILES)
