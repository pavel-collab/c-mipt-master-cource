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
    fig = plt.figure()
    plt.title(f"Hash functions collisions on {string_len} string len")

    sns.barplot(x='hashes', y='collisions', data=hash_collisions)

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

    if args.distribution:
        ...

    if args.hashes:
        collision_files = find_all_collision_file_data(data_path=data_path.absolute())

        for data_file, str_len in collision_files.items():
            file_path = Path(f"{data_path}/{data_file}")
            
            print(f"[DEBUG] {file_path.absolute()}")
            assert(file_path.exists())

            df = pd.read_csv(file_path.absolute())
            plot_hash_comparision(df, str_len)

if __name__ == '__main__':
    main()