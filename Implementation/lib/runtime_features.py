import sys
import os
import pandas as pd
import numpy as np
from tqdm import tqdm
from collections import Counter

# Add the build directory to Python path
build_dir = os.path.abspath('/Users/kisel/uni/apal/Algorithm-Selector/Implementation/lib')
sys.path.insert(0, build_dir)

# Add the data directory to Python path
data_dir = os.path.abspath('/Users/kisel/uni/apal/Algorithm-Selector/Implementation/data')
sys.path.insert(0, data_dir)

import sorters
import probes
import time

import list_generators as lg

def find_range(arr) -> int:
    return max(arr) - min(arr)

def find_entropy(arr) -> int:
    return find_range(arr)/len(arr)

def find_frequency(arr) -> int:
    return Counter(arr)

def find_avg_dup_pos(arr):
    freq = Counter(arr) 
    n = len(arr)  
    
    sum_sq = sum(f * f for f in freq.values())
    
    if n > 0:
        return (sum_sq / n) - 1
    else:
        return  0  

def find_avg_dup_distinct(arr):
    freq = Counter(arr) 
    n = len(arr)  
    d = len(freq) 
    
    sum_sq = sum(f * f for f in freq.values())

    if d > 0:
        return  (n - d) / d
    else:
        return 0  