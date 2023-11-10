#!/bin/bash

for py in $(ls ./python/*.py); do
    echo "========================================"
    INPUT="./input/`basename ${py} .py`.in"
    echo "python3 ${py} < ${INPUT}"
    time python3 ${py} < ${INPUT}
done