import sys
import os

# Add the build directory to Python path
build_dir = os.path.abspath('../')
sys.path.insert(0, build_dir)

import sorters

# Test arrays
arr1 = [5, 2, 8, 1, 9]
arr2 = [3, 7, 4, 6, 0]
arr3 = [10, 5, 2, 8, 1]

# Test each sorter
print("Original arrays:")
print(f"arr1: {arr1}")
print(f"arr2: {arr2}")
print(f"arr3: {arr3}")

print("\nQuick Sort:")
print(f"arr1: {sorters.quick_sort(arr1)}")

print("\nMerge Sort:")
print(f"arr2: {sorters.merge_sort(arr2)}")

print("\nInsertion Sort:")
print(f"arr3: {sorters.insertion_sort(arr3)}") 
