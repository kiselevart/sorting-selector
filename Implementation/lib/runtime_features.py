from collections import Counter
import math
import os
import sys
import time

import numpy as np
import pandas as pd
from tqdm import tqdm

def find_frequency(arr):
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

    if d > 0:
        return  (n - d) / d
    else:
        return 0  

def find_entropy(arr):
    n = len(arr)
    if n == 0:
        return 0.0  

    freq = Counter(arr) 

    entropy = 0.0
    for count in freq.values():
        p = count / n
        entropy -= p * math.log2(p)

    return entropy
