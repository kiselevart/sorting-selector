import time
import sys
import os

# Add the build directory to Python path
build_dir = os.path.abspath('../')
sys.path.insert(0, build_dir)

print(build_dir)
import sorters

arrs = [[5, 1, 7, 3], [3,1,4,1,5,9,2]]
time = sorters.benchmark_sorter("insertion_sort", arrs)
print(time)