import random

def generate_random_list(n):
    return [random.randint(0, n) for _ in range(n)]

def generate_sorted_list(n):
    return list(range(n))

def generate_reversed_list(n):
    return list(range(n, 0, -1))

def generate_nearly_sorted_list(n, disorder_ratio=0.05):
    # Start with a sorted list, then perform a few random swaps.
    lst = list(range(n))
    num_swaps = max(1, int(disorder_ratio * n))
    for _ in range(num_swaps):
        i, j = random.sample(range(n), 2)
        lst[i], lst[j] = lst[j], lst[i]
    return lst

def generate_duplicates_list(n, unique_count=5):
    # Generate a list with many duplicates.
    return [random.randint(0, unique_count - 1) for _ in range(n)]

# Define the sizes you want to test
sizes = [10, 100, 1000, 10000, 100000]

# Create a dataset dictionary that maps each size to different cases
dataset = {}
for n in sizes:
    dataset[n] = {
        "random": generate_random_list(n),
        "sorted": generate_sorted_list(n),
        "reversed": generate_reversed_list(n),
        "nearly_sorted": generate_nearly_sorted_list(n),
        "duplicates (unique 5)": generate_duplicates_list(n, 5),
        "duplicates (unique 10)": generate_duplicates_list(n, 10),
        "duplicates (half unique)": generate_duplicates_list(n, int(n/2))
    }

# Example: print out the first 10 elements of each case for n=1000
n = 1000
for case, lst in dataset[n].items():
    print(f"{case} (first 10 elements): {lst[:10]}")
