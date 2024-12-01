#!/bin/bash

clang -I../../utils -o solution solution.c ../utils/utils.c
if [[ $? -eq 0 ]]; then
    echo "Compilation success."
else
    echo "Compilation fail."
fi
