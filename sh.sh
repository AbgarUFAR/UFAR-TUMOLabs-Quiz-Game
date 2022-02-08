#! /bin/sh
gcc -c main.c ./helper/*.c ./services/*.c ./comparators/*.c && gcc -o launch *.o
gcc -o launch *.o
