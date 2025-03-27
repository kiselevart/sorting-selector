import sys
import os
from pprint import pprint
import argparse

import pandas as pd
from tqdm import tqdm

import sorters
import runtime_features as rf

def find_best_sorter(arr):
    best_name, best_time = None, float("inf")
    for sorter in sorters.list_sorters():
        elapsed = sorters.benchmark_sorter(sorter, arr)
        if elapsed < best_time:
            best_time, best_name = elapsed, sorter
    return best_name


def main(input_path: str, output_path: str):
    data = pd.read_feather(input_path)

    data['data'] = data['data'].apply(lambda arr: arr.tolist())

    tqdm.pandas(desc="Extracting features")
    data['features'] = data['data'].progress_apply(rf.extract_features)

    for idx, row in data.iterrows():
        print(f"Row {idx}:")
        pprint(row['features'])
        print('-' * 50)

    tqdm.pandas(desc="Benchmarking sorters")
    data['best_sort'] = data['data'].progress_apply(find_best_sorter)

    data.to_feather(output_path)
    print(f"Results saved to {output_path}")


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description="Feature extraction and sorting benchmark script.")
    parser.add_argument('input', help="Path to the input Feather file.")
    parser.add_argument('output', help="Path for the output Feather file.")
    args = parser.parse_args()

    main(args.input, args.output)
