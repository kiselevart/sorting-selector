from collections import Counter
import math
import sorters

def find_features(arr):
    """
    Returns [freq, avg_dup_pos, avg_dup_distinct, entropy] for the input iterable arr.
    """
    freq = Counter(arr)
    n = len(arr)
    d = len(freq)

    sum_sq = sum(count * count for count in freq.values())
    avg_dup_pos = (sum_sq / n) - 1 if n else 0
    avg_dup_distinct = ((n - d) / d) if d else 0
    entropy = -sum((count / n) * math.log2(count / n) for count in freq.values()) if n else 0

    return [freq, avg_dup_pos, avg_dup_distinct, entropy]
