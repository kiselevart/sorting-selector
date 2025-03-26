import random
import math
import numpy as np
import pandas as pd
from tqdm import tqdm

def generate_list(n):
    """Create a sorted list of n elements (0 to n-1)."""
    return list(range(int(n)))

def generate_duplicates_list(n, unique_count):
    n = int(n)
    if unique_count > n:
        raise ValueError("unique_count cannot exceed total length n")
    base = list(range(unique_count))
    base += [random.choice(base) for _ in range(n - unique_count)]
    return sorted(base)

def generate_duplicates_list_ratio(n, duplicate_ratio):
    n = int(n)
    if not 0 <= duplicate_ratio <= 1:
        raise ValueError("duplicate_ratio must be between 0 and 1")
    if n <= 0:
        return []
    unique_count = max(1, round(n * (1 - duplicate_ratio)))
    unique_count = min(unique_count, n)
    return generate_duplicates_list(n, unique_count)

def randomize_list(lst):
    new_lst = lst.copy()
    random.shuffle(new_lst)
    return new_lst

def reverse_list(lst):
    return lst[::-1]

def disorder_list(lst, disorder_ratio=0.05):
    if not lst: return []
    new_lst = lst.copy()
    n = len(new_lst)
    num_swaps = max(1, int(disorder_ratio * n))
    for _ in range(num_swaps):
        i, j = random.sample(range(n), 2)
        new_lst[i], new_lst[j] = new_lst[j], new_lst[i]
    return new_lst

def generate_uniform_list(n, low=0, high=100):
    return [random.uniform(low, high) for _ in range(n)]

def generate_normal_list(n, mean=0, std=1):
    return [random.gauss(mean, std) for _ in range(n)]

def generate_exponential_list(n, scale=1.0):
    return [random.expovariate(1/scale) for _ in range(n)]

def generate_zipf_list(n, a=2):
    return np.random.zipf(a, n).tolist()

def generate_clustered_list(n, clusters=3, spread=5):
    centers = [random.uniform(0, 100) for _ in range(clusters)]
    return [random.gauss(random.choice(centers), spread) for _ in range(n)]

def generate_geometric_list(n, start=1, ratio=2):
    return [start * (ratio ** i) for i in range(n)]

def generate_sine_wave_list(n, amplitude=1, frequency=1.0, noise=0.1):
    return [amplitude * math.sin(frequency * i) + random.uniform(-noise, noise) for i in range(n)]

def main():
    sizes = [10, 100, 1000, int(1e4), int(1e5), int(1e6), int(2e6)]
    dataset = {}

    for n in tqdm(sizes, desc="Generating Datasets", position=0):
        base_list = generate_list(n)
        list_types = [
            "sorted", "random", "reversed", 
            "disorder_0.05", "disorder_0.10", "disorder_0.20", 
            "duplicates_5_unique", "uniform", "normal", 
            "exponential", "zipf", "clustered", 
            "geometric", "sine_wave"
        ]
        dataset[str(n)] = {}
        for list_type in tqdm(list_types, desc=f"Processing size {n}", position=1, leave=False):
            if list_type == "random":
                dataset[str(n)][list_type] = randomize_list(base_list)
            elif list_type == "reversed":
                dataset[str(n)][list_type] = reverse_list(base_list)
            elif list_type == "disorder_0.05":
                dataset[str(n)][list_type] = disorder_list(base_list, disorder_ratio=0.05)
            elif list_type == "disorder_0.10":
                dataset[str(n)][list_type] = disorder_list(base_list, disorder_ratio=0.10)
            elif list_type == "disorder_0.20":
                dataset[str(n)][list_type] = disorder_list(base_list, disorder_ratio=0.20)
            elif list_type == "duplicates_5_unique":
                dataset[str(n)][list_type] = sorted([random.choice(range(5)) for _ in range(n)])
            elif list_type == "uniform":
                dataset[str(n)][list_type] = generate_uniform_list(n, low=0, high=100)
            elif list_type == "normal":
                dataset[str(n)][list_type] = generate_normal_list(n, mean=50, std=10)
            elif list_type == "exponential":
                dataset[str(n)][list_type] = generate_exponential_list(n, scale=1.0)
            elif list_type == "zipf":
                dataset[str(n)][list_type] = generate_zipf_list(n, a=2)
            elif list_type == "clustered":
                dataset[str(n)][list_type] = generate_clustered_list(n, clusters=3, spread=5)
            elif list_type == "sine_wave":
                dataset[str(n)][list_type] = generate_sine_wave_list(n, amplitude=10, frequency=0.1, noise=0.5)

    # Build a DataFrame with one row per (size, list_type) pair and the full list as a column.
    rows = []
    for size, lists in tqdm(dataset.items(), desc="Creating DataFrame", position=0):
        for list_type, lst in tqdm(lists.items(), desc=f"Processing size {size}", position=1, leave=False):
            rows.append({
                "list_type": list_type,
                "list": lst
            })

    df = pd.DataFrame(rows)
    df.to_feather('varied_dataset.feather')
    print("Dataset generation complete. Saved to varied_dataset.feather")

if __name__ == "__main__":
    main()
