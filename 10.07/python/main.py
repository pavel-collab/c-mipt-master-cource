import argparse
import seaborn as sns
import matplotlib.pyplot as plt
import pandas as pd
from pathlib import Path
import re 
import os

#TODO: make all of the files from txt to csv and use dataframes directly 

parser = argparse.ArgumentParser()

parser.add_argument('-f', '--file_path', help='set path to the files with data')
parser.add_argument('-d', '--distribution', help='plot distribution bars', action='store_true')
parser.add_argument('-H', '--hashes', help='plot hash functios comparision bars', action='store_true')

args = parser.parse_args()

collision_pattern = re.compile('collisions_[0-9]+.txt')
hash_pattern = re.compile('[a-z,A-Z,0-9]+_[0-9]+_distribution.txt')

def find_all_collision_file_data(data_path: str):
    collision_data_file_list = [f for f in os.listdir(data_path) if collision_pattern.match(f)]
    collision_files = {}
    for file in collision_data_file_list:
        string_len = int(file[len('collisions_'):].removesuffix('.txt'))
        collision_files[file] = string_len
    return collision_files

def extract_hash_name(file_name: str):
    string_len = int(re.findall('_[0-9]+_', file_name)[0][1:].removesuffix('_'))
    hash_name = file_name.removesuffix(f"_{string_len}_distribution.txt")
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

def plot_hash_comparision(hash_collisions: dict, string_len: int):
    #? may be we can do it by some interface function?
    df = pd.DataFrame(
        {
            'Hashes' : hash_collisions.keys(),
            'collisions' : hash_collisions.values()
        }
    )
    
    fig = plt.figure()
    plt.title(f"Hash functions collisions on {string_len} string len")

    sns.barplot(x='Hashes', y='collisions', data=df)

    plt.xlabel('hash function name')
    plt.ylabel('collision number')

    save_file_name = f"./images/collisions_{string_len}.png"
    fig.savefig(save_file_name)

def plot_hash_distribution(hash_name: str, string_len: int, dataframe):
    fig = plt.figure()
    plt.title(f"Distribution for hash {hash_name}")

    sns.barplot(x='values', y='hits', data=dataframe)
    plt.ylabel('hit humber')

    save_file_name = f"./images/distribution_{hash_name}_{string_len}.png"
    fig.savefig(save_file_name)

def main():
    if args.file_path is None or args.file_path == "":
        print(f"[err] path to files with data is not set")
        return
    
    data_path = Path(args.file_path)
    if not data_path.exists() or not data_path.is_dir():
        print(f"[err] there are problems with {data_path.absolute()} (may be it's not exists)")

    collision_files = find_all_hf_data_files(data_path=data_path.absolute())
    print(collision_files)

if __name__ == '__main__':
    main()