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

def generate_random_list(n):
    lst = generate_list(n)
    random.shuffle(lst)
    return lst

def generate_reversed_list(n):
    return reverse_list(generate_list(n))

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

def generate_sinewave_list(n, amplitude=1, frequency=1.0, noise=0.1):
    return [amplitude * math.sin(frequency * i) + random.uniform(-noise, noise) for i in range(n)]

def main():
    sizes = [10, 100, 1000, 10000]
    #sizes.append(int(1e5))
    #sizes.append(int(1e6))
    #sizes.append(int(2e6))
    dataset = {}

    list_types = [
        "random", "reversed", 
        "disorder_0.05", "disorder_0.10", "disorder_0.20", 
        "duplicates_0.01", "duplicates_0.1", "duplicates_0.2", "uniform", "normal", 
        "exponential", "zipf", "clustered", "sinewave"
    ]

    rows = []

    for size in tqdm(sizes, desc="Generating lists"):
        base_list = generate_list(size)

        for list_type in tqdm(list_types, desc=f"Processing size {size}", leave=False):
            args = list_type.split("_")

            for _ in range(1000):
                if args[0] == "disorder":
                    result = disorder_list(base_list.copy(), float(args[1]))

                elif args[0] == "duplicates":
                    result = generate_duplicates_list_ratio(size, float(args[1]))

                else:
                    func = globals().get(f"generate_{args[0]}_list")
                    if not callable(func):
                        raise ValueError(f"No function named generate_{args[0]}_list")
                    result = func(size)

                rows.append({
                    "list_type": list_type,
                    "data": result
                })

    df = pd.DataFrame(rows)
    df.to_feather("varied_dataset.feather")
    print("Dataset generation complete. Saved to varied_dataset.feather")

if __name__ == "__main__":
    main()
