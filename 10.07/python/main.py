from utils import *

import argparse
import seaborn as sns
import matplotlib.pyplot as plt
import pandas as pd
from pathlib import Path

parser = argparse.ArgumentParser()

parser.add_argument('-f', '--file_path', help='set path to the files with data')
parser.add_argument('-d', '--distribution', help='plot distribution bars', action='store_true')
parser.add_argument('-H', '--hashes', help='plot hash functios comparision bars', action='store_true')

args = parser.parse_args()

def plot_hash_comparision(hash_collisions, string_len: int):
    fig = plt.figure(figsize=(16, 9))
    plt.title(f"Hash functions collisions on {string_len} string len")

    sns.barplot(x='hashes', y='collisions', data=hash_collisions)

    plt.xlabel('hash function name')
    plt.ylabel('collision number')
    plt.xticks(rotation=45, ha='right')

    save_file_name = f"./images/collisions_{string_len}.png"
    fig.savefig(save_file_name)

def plot_hash_distribution(hash_name: str, string_len: int, dataframe):
    fig = plt.figure()
    plt.title(f"Distribution for hash {hash_name}")

    #? may be use here smth except of barplot
    sns.barplot(x='values', y='hits', data=dataframe)
    plt.ylabel('hit humber')
    plt.xticks([]) 

    save_file_name = f"./images/distribution_{hash_name}_{string_len}.png"
    fig.savefig(save_file_name)

def main():
    if args.file_path is None or args.file_path == "":
        print(f"[err] path to files with data is not set")
        return
    
    data_path = Path(args.file_path)

    if not data_path.exists() or not data_path.is_dir():
        print(f"[err] there are problems with {data_path.absolute()} (may be it's not exists)")

    if args.distribution:
        print("[DEBUG] enter to the distribution")
        hash_function_files = find_all_hf_data_files(data_path=data_path.absolute())

        print("[DEBUG] get all of the data file names")
        for str_len, files_list in hash_function_files.items():
            print(f"[DEBUG] process all of the files with len {str_len}")
            for file in files_list:
                print(f"[DEBUG] proces the file {file}")
                hash_name = extract_hash_name(file)

                file_path = Path(f"{data_path}/{file}")
                assert(file_path.exists())

                df = pd.read_csv(file_path.absolute())    
                df = filter_dataset(df, n=20)
                plot_hash_distribution(hash_name, str_len, df)
                clear_mem()

    if args.hashes:
        collision_files = find_all_collision_file_data(data_path=data_path.absolute())

        for data_file, str_len in collision_files.items():
            file_path = Path(f"{data_path}/{data_file}")            
            assert(file_path.exists())

            df = pd.read_csv(file_path.absolute())
            plot_hash_comparision(df, str_len)

if __name__ == '__main__':
    main()