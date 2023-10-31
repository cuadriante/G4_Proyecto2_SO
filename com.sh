#!/bin/bash

# Compile the kernel module (if needed)
make clean

make

# Load the kernel module
sudo insmod driver.ko

# Check kernel logs for module output
sudo dmesg

sudo rmmod driver.ko

make clean
