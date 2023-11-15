# Makefile for the ch341 driver

# obj-m += driver.o
obj-m += test_driver.o

# Set the desired compiler
CC := /usr/bin/x86_64-linux-gnu-gcc-13

KDIR := /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)

default:
	$(MAKE) -C $(KDIR) M=$(PWD) modules EXTRA_CFLAGS=-w CC=$(CC)

clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean
