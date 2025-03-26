from collections import Counter
import math
import probes

def find_features(arr):
    """
    Returns [avg_dup_pos, avg_dup_distinct, entropy] for the input iterable arr.
    """
    freq = Counter(arr)
    n = len(arr)
    d = len(freq)

    # non-presortedness metrics
    sum_sq = sum(count * count for count in freq.values())
    avg_dup_pos = (sum_sq / n) - 1 if n else 0
    avg_dup_distinct = ((n - d) / d) if d else 0
    entropy = -sum((count / n) * math.log2(count / n) for count in freq.values()) if n else 0

    # presortedness metrics
    dis = probes.measure("dis", arr)
    mono = probes.measure("mono", arr)
    runs = probes.measure("runs", arr)

    return [
        avg_dup_pos, 
        avg_dup_distinct, 
        entropy,
        dis, 
        mono,
        runs
     ]
