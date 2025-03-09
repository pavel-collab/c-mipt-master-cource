#!/bin/bash

string_pool_size=100000

echo "CLEAN OLD DATA"
./clean_data.sh
./clean_images.sh

echo "RUN C++ PROGRAM, COLLECT EXPERIMENT DATA"
for string_len in {30000..50000..5000}; do
    ./a.out $string_pool_size $string_len
done

echo "PLOT HASH COLLISION COMPARISION CHARTS"
./plot_collision.sh

echo "PLOT HASH DISTRIOBUTION CHARTS"
./plot_distribution.sh