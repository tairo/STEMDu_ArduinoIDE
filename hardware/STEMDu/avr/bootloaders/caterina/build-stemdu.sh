#!/bin/bash

make clean
make VID=0x16D0 PID=0x095D F_CPU=8000000
mv Caterina.hex Caterina-stemdu8.hex
