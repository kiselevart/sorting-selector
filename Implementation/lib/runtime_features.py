from collections import Counter
import math
import os
import sys
import time

import numpy as np
import pandas as pd

import probes

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
    """
    Returns the Shannon entropy of the given array
    """
    n = len(arr)
    if n == 0:
        return 0.0  

    freq = Counter(arr) 

    entropy = 0.0
    for count in freq.values():
        p = count / n
        entropy -= p * math.log2(p)

    return entropy

def find_dis(arr):
    return probes.measure('dis', arr)

def find_mono(arr):
    return probes.measure('mono', arr)

def find_runs(arr):
    return probes.measure('runs', arr)

def find_skewness(arr):
    a = np.asarray(arr, dtype=float)
    m = a.mean()
    s = a - m
    m2 = np.mean(s**2)
    m3 = np.mean(s**3)
    return float(m3 / (m2**1.5)) if m2 else 0.0

def find_kurtosis(arr):
    a = np.asarray(arr, dtype=float)
    m = a.mean()
    s = a - m
    m2 = np.mean(s**2)
    m4 = np.mean(s**4)
    return float(m4 / (m2*m2) - 3) if m2 else 0.0

def categorical_skew(arr: list) -> float:
    """
    Compute the skewness of the frequency-distribution of a categorical array.
    """
    counts = list(Counter(arr).values())
    skew = find_skewness(counts)
    return skew

def categorical_kurtosis(arr: list) -> float:
    """
    Compute the excess kurtosis of the frequency-distribution of a categorical array.
    """
    counts = list(Counter(arr).values())
    kurt = find_kurtosis(counts)
    return kurt

def extract_features(arr):
    """
    Compute a variety of features from an array for ML-based sort selection.
    
    Features computed:
      - size: total number of elements in arr
      - range: max(arr) - min(arr) (if numeric, else None)
      - avg_dup_pos: average duplicate position of elements
      - avg_dup_distinct: average duplicates per distinct element
      - entropy: Shannon entropy of the element distribution
      - dis: presortedness probe 'dis'
      - mono: presortedness probe 'mono'
      - runs: presortedness probe 'runs'
      - skewness: skewness of the array values
      - kurtosis: excess kurtosis of the array values
      - categorical_skew: skewness of the frequency-distribution (for non-numeric insights)
      - categorical_kurtosis: excess kurtosis of the frequency-distribution
    """
    features = {}
    n = len(arr)
    features['size'] = n

    # Compute range if possible (if the array is numeric)
    try:
        features['range'] = float(max(arr)) - float(min(arr))
    except Exception:
        features['range'] = None

    features['avg_dup_pos'] = find_avg_dup_pos(arr)
    features['avg_dup_distinct'] = find_avg_dup_distinct(arr)
    features['entropy'] = find_entropy(arr)
    features['dis'] = find_dis(arr)
    features['mono'] = find_mono(arr)
    features['runs'] = find_runs(arr)
    features['skewness'] = find_skewness(arr)
    features['kurtosis'] = find_kurtosis(arr)
    #features['categorical_skew'] = categorical_skew(arr)
    #features['categorical_kurtosis'] = categorical_kurtosis(arr)
    
    return features