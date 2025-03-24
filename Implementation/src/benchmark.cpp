#include "benchmark.h"
#include <chrono>
#include <random>
#include <algorithm>

template<typename Sorter>
BenchmarkResult<Sorter> benchmark_sorter(Sorter& sorter, const std::vector<std::vector<int>>& test_arrays) {
    BenchmarkResult<Sorter> result;
    result.total_time_ms = 0.0;
    
    auto start = std::chrono::high_resolution_clock::now();
    
    for (const auto& arr : test_arrays) {
        std::vector<int> arr_copy = arr;  

        auto array_start = std::chrono::high_resolution_clock::now();
        sorter(arr_copy);
        auto array_end = std::chrono::high_resolution_clock::now();
        
        double array_time = std::chrono::duration<double, std::milli>(array_end - array_start).count();
        result.times_by_size.push_back({arr.size(), array_time});
        result.total_time_ms += array_time;
    }
    
    auto end = std::chrono::high_resolution_clock::now();
    result.total_time_ms = std::chrono::duration<double, std::milli>(end - start).count();
    
    return result;
}

std::vector<std::vector<int>> generate_test_arrays(const std::vector<size_t>& sizes) {
    std::vector<std::vector<int>> test_arrays;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 1000);
    
    for (size_t size : sizes) {
        std::vector<int> arr(size);
        std::generate(arr.begin(), arr.end(), [&]() { return dis(gen); });
        test_arrays.push_back(arr);
    }
    
    return test_arrays;
}

// Explicit template instantiations for the sorters we're using
template BenchmarkResult<cppsort::quick_sorter> benchmark_sorter(cppsort::quick_sorter&, const std::vector<std::vector<int>>&);
template BenchmarkResult<cppsort::merge_sorter> benchmark_sorter(cppsort::merge_sorter&, const std::vector<std::vector<int>>&);
template BenchmarkResult<cppsort::insertion_sorter> benchmark_sorter(cppsort::insertion_sorter&, const std::vector<std::vector<int>>&); 