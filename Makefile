# Makefile for the ch341 driver

# obj-m += driver.o
obj-m += test_driver.o

# Set the desired compiler
CC := /usr/bin/x86_64-linux-gnu-gcc-13

KDIR := /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)

driver_lib_src = driver_lib.c
driver_lib_obj = driver_lib.o

default:
	$(MAKE) -C $(KDIR) M=$(PWD) modules EXTRA_CFLAGS=-w CC=$(CC)
	gcc -c -o $(driver_lib_obj) $(driver_lib_src)
	ar rcs libdriver_lib.a $(driver_lib_obj)

clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean
	rm -f $(driver_lib_obj) libdriver_lib.a
