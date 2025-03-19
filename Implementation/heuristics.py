import math
from collections import Counter

def shannon_entropy(lst):
    # Calculate frequencies of each unique element
    counts = Counter(lst)
    total = len(lst)
    entropy = 0.0
    # Compute the entropy using log base 2
    for count in counts.values():
        p = count / total
        entropy -= p * math.log2(p)
    return entropy

def normalized_shannon_entropy(lst):
    # Calculate the Shannon entropy
    entropy = shannon_entropy(lst)
    # Get the number of unique elements
    unique_elements = len(set(lst))
    maximum_entropy = math.log2(unique_elements)
    # To avoid division by zero, return 0 if there's only one unique element
    if unique_elements > 1:
        return entropy / maximum_entropy
    else:
        return 0.0

def runs(seq):
    """
    Return a normalized measure (0 to 1) of the number of runs in the sequence.
    A run is a maximal strictly monotonic segment.
    
    For a sequence of length n (n >= 3):
      - A monotonic sequence (one run) returns 0.
      - A perfectly alternating sequence (maximum runs: n-1) returns 1.
      
    For n < 3, the function returns 0.
    
    Parameters:
        seq (list): A list of numbers.
    
    Returns:
        A float between 0 and 1.
    """
    n = len(seq)
    if n < 2:
        return 0  # With 0 or 1 element, no variability.
    
    # Count the runs.
    run_count = 1
    # Determine initial direction based on the first two elements.
    current_dir = 1 if seq[1] > seq[0] else -1
    
    for i in range(1, n):
        new_dir = 1 if seq[i] > seq[i - 1] else -1
        if new_dir != current_dir:
            run_count += 1
            current_dir = new_dir
    
    # For sequences of length 2, normalized value is 0.
    if n < 3:
        return 0
    
    # Maximum possible runs in a sequence of length n is n - 1.
    # We subtract 1 from run_count so that a monotonic sequence gives 0,
    # and divide by (n - 2) so that an alternating sequence gives 1.
    normalized = (run_count - 1) / (n - 2)
    return normalized

def full_heuristic(lst):
    norm_shan_entropy = normalized_shannon_entropy(lst)
    norm_runs = runs(lst)
    length = len(lst)
    return norm_shan_entropy, norm_runs, length