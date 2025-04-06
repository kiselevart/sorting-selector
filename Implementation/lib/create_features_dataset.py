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

def create_features_dataset(df):
    data = df
    data['data'] = data['data'].apply(lambda arr: arr.tolist())

    tqdm.pandas(desc="Extracting features")
    data['features'] = data['data'].progress_apply(rf.extract_features)

    tqdm.pandas(desc="Benchmarking sorters")
    data['best_sort'] = data['data'].progress_apply(find_best_sorter)

    return data