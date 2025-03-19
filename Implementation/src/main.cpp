#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <algorithm>
#include <cpp-sort/sorters.h>
#include <cpp-sort/sorters/quick_sorter.h>
#include <cpp-sort/sorters/merge_sorter.h>
#include <cpp-sort/sorters/insertion_sorter.h>
#include "benchmark.h"

int main() {
    // Define test array sizes
    std::vector<size_t> sizes = {100, 1000, 10000, 100000};
    auto test_arrays = generate_test_arrays(sizes);
    
    // Create different sorters
    cppsort::quick_sorter quick_sort;
    cppsort::merge_sorter merge_sort;
    cppsort::insertion_sorter insertion_sort;
    
    // Run benchmarks
    std::cout << "Running benchmarks...\n\n";
    
    // Quick Sort benchmark
    auto quick_results = benchmark_sorter(quick_sort, test_arrays);
    std::cout << "Quick Sort Results:\n";
    std::cout << "Total time: " << quick_results.total_time_ms << "ms\n";
    std::cout << "Times by array size:\n";
    for (const auto& [size, time] : quick_results.times_by_size) {
        std::cout << "Size " << size << ": " << time << "ms\n";
    }
    std::cout << "\n";
    
    // Merge Sort benchmark
    auto merge_results = benchmark_sorter(merge_sort, test_arrays);
    std::cout << "Merge Sort Results:\n";
    std::cout << "Total time: " << merge_results.total_time_ms << "ms\n";
    std::cout << "Times by array size:\n";
    for (const auto& [size, time] : merge_results.times_by_size) {
        std::cout << "Size " << size << ": " << time << "ms\n";
    }
    std::cout << "\n";
    
    // Insertion Sort benchmark
    auto insertion_results = benchmark_sorter(insertion_sort, test_arrays);
    std::cout << "Insertion Sort Results:\n";
    std::cout << "Total time: " << insertion_results.total_time_ms << "ms\n";
    std::cout << "Times by array size:\n";
    for (const auto& [size, time] : insertion_results.times_by_size) {
        std::cout << "Size " << size << ": " << time << "ms\n";
    }
    
    return 0;
}