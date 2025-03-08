import os
import re

collision_pattern = re.compile('collisions_[0-9]+.csv')
hash_pattern = re.compile('[a-z,A-Z,0-9]+_[0-9]+_distribution.csv')

def find_all_collision_file_data(data_path: str):
    collision_data_file_list = [f for f in os.listdir(data_path) if collision_pattern.match(f)]
    collision_files = {}
    for file in collision_data_file_list:
        string_len = int(file[len('collisions_'):].removesuffix('.csv'))
        collision_files[file] = string_len
    return collision_files

def extract_hash_name(file_name: str):
    string_len = int(re.findall('_[0-9]+_', file_name)[0][1:].removesuffix('_'))
    hash_name = file_name.removesuffix(f"_{string_len}_distribution.csv")
    return hash_name

def find_all_hf_data_files(data_path: str):
    hash_data_files = [f for f in os.listdir(data_path) if hash_pattern.match(f)]
    hash_files_by_string_len = {}

    for file in hash_data_files:
        string_len = int(re.findall('_[0-9]+_', file)[0][1:].removesuffix('_'))

        if string_len in hash_files_by_string_len.keys():
            hash_files_by_string_len[string_len].append(file)
        else:
            hash_files_by_string_len[string_len] = [file]
    
    return hash_files_by_string_len
