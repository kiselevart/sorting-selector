import random
import json

def generate_list(n):
    """Create a sorted list of n elements (0 to n-1)."""
    return list(range(n))

def generate_duplicates_list(n, unique_count):
    """Return a sorted list of length n containing exactly unique_count distinct values."""
    if unique_count > n:
        raise ValueError("unique_count cannot exceed total length n")
    base = list(range(unique_count))
    # fill the remainder with random picks from those unique values
    base += [random.choice(base) for _ in range(n - unique_count)]
    return sorted(base)

def generate_duplicates_list_ratio(n, duplicate_ratio):
    """
    Return a sorted list of length n where duplicate_ratio ∈ [0,1].
      • 0.0 ⇒ all elements unique
      • 1.0 ⇒ all elements identical
    """
    if not 0 <= duplicate_ratio <= 1:
        raise ValueError("duplicate_ratio must be between 0 and 1")
    # Compute how many unique values we need
    unique_count = max(1, int(round(n * (1 - duplicate_ratio))))
    return generate_duplicates_list(n, unique_count)

def randomize_list(lst):
    """Return a shuffled copy of the provided list."""
    new_lst = lst.copy()
    random.shuffle(new_lst)
    return new_lst

def reverse_list(lst):
    """Return a reversed copy of the provided list."""
    return lst[::-1]

def disorder_list(lst, disorder_ratio=0.05):
    """
    Return a copy of the provided list with a number of random swaps.
    disorder_ratio indicates the fraction of elements to swap (at least one).
    """
    new_lst = lst.copy()
    n = len(new_lst)
    num_swaps = max(1, int(disorder_ratio * n))
    for _ in range(num_swaps):
        i, j = random.sample(range(n), 2)
        new_lst[i], new_lst[j] = new_lst[j], new_lst[i]
    return new_lst

# Define the sizes you want to test.
sizes = [10, 100, 1000, 10000, 100000]

# Create a dataset dictionary that maps each size to different cases.
dataset = {}
for n in sizes:
    base_list = generate_list(n)  # This is our sorted base list.
    dataset[n] = {
        "random": randomize_list(base_list),
        "sorted": base_list,
        "reversed": reverse_list(base_list),
        "disorder 0.05": disorder_list(base_list),
        "disorder 0.10": disorder_list(base_list),
        "disorder 0.50": disorder_list(base_list),
        "duplicates 5 unique": generate_duplicates_list(n, 5),
        "duplicates 10 unique": generate_duplicates_list(n, 10),
        "duplicates n/2 unique": generate_duplicates_list(n, int(n/2))
    }

# Write the dataset to a JSON file.
with open('/Users/kisel/uni/apal/Algorithm-Selector/Implementation/dataset.json', 'w') as f:
    json.dump(dataset, f, indent=4)
