import sys
import os

# Add the build directory to Python path
build_dir = os.path.abspath('build')
print(f"Adding to Python path: {build_dir}")
sys.path.insert(0, build_dir)
print(f"Python path: {sys.path}")

try:
    import sorters
    print("Module imported successfully!")
except ImportError as e:
    print(f"Import error: {e}")
    print(f"Current directory: {os.getcwd()}")
    print(f"Files in build directory: {os.listdir(build_dir)}")

# Test with small arrays
sizes = [10, 100, 1000, 10000]
test_arrays = sorters.generate_test_arrays(sizes)
print(f"Generated {len(test_arrays)} test arrays")

# Run benchmarks
print("\nRunning benchmarks...")
quick_results = sorters.benchmark_quick_sort(test_arrays)
print("\nQuick Sort Results:")
print(f"Total time: {quick_results.total_time_ms:.2f}ms")
for size, time in quick_results.times_by_size:
    print(f"Size {size}: {time:.2f}ms") 