#!/bin/bash

data_directory="./data"
file_pattern="*_distribution.csv"

for file in $data_directory/$file_pattern; do
    if [[ -f "$file" ]]; then
        python3 ./python/main.py -d $file
    else
        echo "file $file is not found"
    fi
done