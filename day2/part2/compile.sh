#!/bin/bash

if [[ $1 == "debug" ]]; then
    echo "Debug mode enabled."
    clang -g -O0 -I../../utils -o solution solution.c ../../utils/utils.c
    echo "Debug compilation success."
else
    clang -I../../utils -o solution solution.c ../../utils/utils.c
    echo "Compilation success. Running program."
    ./solution
fi
