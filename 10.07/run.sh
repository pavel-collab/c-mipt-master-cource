#!/bin/bash

string_pool_size=100000

./clean_data.sh

# for string_len in {100000..2000000..100000}; do
#     ./a.out $string_pool_size $string_len
# done

for string_len in {10000..20000..5000}; do
    ./a.out $string_pool_size $string_len
done