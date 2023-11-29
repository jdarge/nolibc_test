#!/bin/sh
gcc -nostdlib -Wno-builtin-declaration-mismatch main.c -o nlc && ./nlc
