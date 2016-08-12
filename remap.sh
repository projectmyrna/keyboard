#!/bin/bash

# Compile and run parse utility
gcc parse.c && \
	./a.out $1 && \

# Write new firmware to device
./launcher -cdigispark --timeout 60 -Uflash:w:./keyboard.cpp.hex:i
