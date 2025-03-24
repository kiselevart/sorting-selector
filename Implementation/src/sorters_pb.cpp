#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/functional.h>
#include <cpp-sort/sorters.h>
#include <cpp-sort/sorter_traits.h>
#include <chrono>
#include <functional>
#include <utility>
#include <vector>
#include <string>

namespace py = pybind11;

double benchmark_sorting_function(const std::function<void(std::vector<int>&)>& sort_func, 
                                  std::vector<int> array) { // Pass by value
    // Start timing
    auto start = std::chrono::high_resolution_clock::now();
    
    // Sorting the copy of the array
    sort_func(array);
    
    // End timing
    auto end = std::chrono::high_resolution_clock::now();
    
    // Calculate and return the duration in milliseconds
    std::chrono::duration<double, std::milli> duration = end - start;
    return duration.count();
}

// Function to create lambda wrappers for different sorters
template<typename Sorter>
std::function<void(std::vector<int>&)> create_sorter_func() {
    return [](std::vector<int>& arr) {
        Sorter sorter;
        sorter(arr);
    };
}

PYBIND11_MODULE(sorters, m) {
    m.doc() = "Benchmarking module for cpp-sort algorithms";
    
    // Function that takes a sorter name and array to benchmark
    m.def("benchmark_sorter", [](const std::string& sorter_name, const std::vector<int>& array) {
        std::function<void(std::vector<int>&)> sort_func;
        
        // Map sorter name to the corresponding function
        if (sorter_name == "adaptive_shivers_sort") {
            sort_func = create_sorter_func<cppsort::adaptive_shivers_sorter>();
        }
        else if (sorter_name == "cartesian_tree_sort") {
            sort_func = create_sorter_func<cppsort::cartesian_tree_sorter>();
        }
        else if (sorter_name == "counting_sort") {
            sort_func = create_sorter_func<cppsort::counting_sorter>();
        }
        else if (sorter_name == "heap_sort") {
            sort_func = create_sorter_func<cppsort::heap_sorter>();
        }
        else if (sorter_name == "insertion_sort") {
            sort_func = create_sorter_func<cppsort::insertion_sorter>();
        }
        else if (sorter_name == "mel_sort") {
            sort_func = create_sorter_func<cppsort::mel_sorter>();
        }
        else if (sorter_name == "merge_sort") {
            sort_func = create_sorter_func<cppsort::merge_sorter>();
        }
        else if (sorter_name == "poplar_sort") {
            sort_func = create_sorter_func<cppsort::poplar_sorter>();
        }
        else if (sorter_name == "quick_sort") {
            sort_func = create_sorter_func<cppsort::quick_sorter>();
        }
        else if (sorter_name == "quick_merge_sort") {
            sort_func = create_sorter_func<cppsort::quick_merge_sorter>();
        }
        else if (sorter_name == "ska_sort") {
            sort_func = create_sorter_func<cppsort::ska_sorter>();
        }
        else if (sorter_name == "slab_sort") {
            sort_func = create_sorter_func<cppsort::slab_sorter>();
        }
        else if (sorter_name == "smooth_sort") {
            sort_func = create_sorter_func<cppsort::smooth_sorter>();
        }
        else if (sorter_name == "spin_sort") {
            sort_func = create_sorter_func<cppsort::spin_sorter>();
        }
        else if (sorter_name == "splay_sort") {
            sort_func = create_sorter_func<cppsort::splay_sorter>();
        }
        else if (sorter_name == "spread_sort") {
            sort_func = create_sorter_func<cppsort::spread_sorter>();
        }
        else if (sorter_name == "std_sort") {
            sort_func = create_sorter_func<cppsort::std_sorter>();
        }
        else if (sorter_name == "tim_sort") {
            sort_func = create_sorter_func<cppsort::tim_sorter>();
        }
        else {
            throw std::invalid_argument("Unknown sorter: " + sorter_name);
        }
        
        // Run the benchmark and return the time
        return benchmark_sorting_function(sort_func, array);
    }, py::arg("sorter_name"), py::arg("array"),
       "Benchmark the specified sorter on an array, returning time in milliseconds");

    // Function to return a list of all available sorter names
    m.def("list_sorters", []() -> std::vector<std::string> {
        return {
            "adaptive_shivers_sort",
            "cartesian_tree_sort",
            "counting_sort",
            "heap_sort",
            "insertion_sort",
            "mel_sort",
            "merge_sort",
            "poplar_sort",
            "quick_sort",
            "quick_merge_sort",
            "ska_sort",
            "slab_sort",
            "smooth_sort",
            "spin_sort",
            "splay_sort",
            "spread_sort",
            "std_sort",
            "tim_sort"
        };
    }, "Return a list of all supported sorter names");
}
