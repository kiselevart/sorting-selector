#pragma once

#include <vector>
#include <cpp-sort/sorters.h>

// Benchmark function that takes a sorter and a vector of test arrays
template<typename Sorter>
struct BenchmarkResult {
    double total_time_ms;
    std::vector<std::pair<size_t, double>> times_by_size;
};

// Forward declarations
template<typename Sorter>
BenchmarkResult<Sorter> benchmark_sorter(Sorter& sorter, const std::vector<std::vector<int>>& test_arrays);

std::vector<std::vector<int>> generate_test_arrays(const std::vector<size_t>& sizes); 