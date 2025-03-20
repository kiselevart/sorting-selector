import time
import sys
import os

# Add the build directory to Python path
build_dir = os.path.abspath('../')
sys.path.insert(0, build_dir)

import sorters

def benchmark_sorter(sorter_name, arr, num_runs=100):
    """
    Benchmarks the specified sorter function from the sorters module.
    Parameters:
        sorter_name (str): The name of the sorter function (e.g., 'quick_sort', 'merge_sort', 'insertion_sort').
        arr (list): The list of values to sort.
        num_runs (int): Number of times to run the sorting function to get an average runtime.
    Returns:
        float: The average execution time in seconds.
    """
    # Retrieve the sorter function from the module
    sorter_func = getattr(sorters, sorter_name, None)
    if sorter_func is None:
        raise ValueError(f"Sorter '{sorter_name}' is not available in the sorters module.")

    total_time = 0.0
    for _ in range(num_runs):
        # Use a copy of the array to ensure each run sorts the unsorted data
        arr_copy = list(arr)
        start = time.perf_counter()
        # Call the sorter (assuming it sorts in-place or returns a new sorted list)
        sorter_func(arr_copy)
        end = time.perf_counter()
        total_time += (end - start)
    avg_time = total_time / num_runs
    return avg_time

if __name__ == "__main__":
    # Example test arrays
    arr1 = [5, 2, 8, 1, 9]
    arr2 = [3, 7, 4, 6, 0]
    arr3 = [10, 5, 2, 8, 1]

    print("Original arrays:")
    print(f"arr1: {arr1}")
    print(f"arr2: {arr2}")
    print(f"arr3: {arr3}")

    # Benchmark each sorter
    quick_time = benchmark_sorter("quick_sort", arr1)
    merge_time = benchmark_sorter("merge_sort", arr2)
    insertion_time = benchmark_sorter("insertion_sort", arr3)

    print("\nBenchmark Results:")
    print(f"Quick Sort (arr1): {quick_time:.6f} seconds on average")
    print(f"Merge Sort (arr2): {merge_time:.6f} seconds on average")
    print(f"Insertion Sort (arr3): {insertion_time:.6f} seconds on average")
