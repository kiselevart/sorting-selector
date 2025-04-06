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
    """Shuffle a sorted list."""
    lst = generate_list(n)
    random.shuffle(lst)
    return lst

def generate_reversed_list(n):
    """Return a reversed sorted list."""
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

def create_varied_dataset(total_lists=1000, min_size=1000, max_size=1000000):
    """
    Generate a dataset with `total_lists` lists.
    Each list has a random size between min_size and max_size,
    and a random type chosen from various generation strategies.
    """
    # Define the list types to choose from.
    # For types with parameters (like disorder and duplicates), we encode the parameter in the string.
    list_types = [
        "random", "reversed", 
        "disorder_0.05", "disorder_0.10", "disorder_0.20", 
        "duplicates_0.01", "duplicates_0.1", "duplicates_0.2", 
        "uniform", "normal", "exponential", "zipf", "clustered", "sinewave"
    ]
    rows = []
    
    for _ in tqdm(range(total_lists), desc="Generating varied lists"):
        size = random.randint(min_size, max_size)
        list_type = random.choice(list_types)
        args = list_type.split("_")
        
        # For "disorder" and "duplicates", we need a base list.
        if args[0] == "disorder":
            base_list = generate_list(size)
            result = disorder_list(base_list.copy(), float(args[1]))
        elif args[0] == "duplicates":
            result = generate_duplicates_list_ratio(size, float(args[1]))
        else:
            # For other list types, dynamically find the corresponding function.
            # e.g., for "random", we call generate_random_list.
            func_name = f"generate_{args[0]}_list"
            func = globals().get(func_name)
            if not callable(func):
                raise ValueError(f"No function named {func_name} found")
            result = func(size)
        
        rows.append({
            "list_type": list_type,
            "size": size,
            "data": result
        })
    
    return pd.DataFrame(rows)


# --- Main Execution ---

if __name__ == "__main__":
    df = create_varied_dataset(total_lists=1000, min_size=1000, max_size=1000000)
    df.to_feather("testing_dataset.feather")
    print("Dataset generation complete. Saved to testing_dataset.feather")
