#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/functional.h>
#include <cpp-sort/sorters.h>
#include <cpp-sort/sorter_traits.h>
#include <chrono>
#include <functional>
#include <vector>
#include <string>

namespace py = pybind11;

double benchmark_sorting_function(const std::function<void(std::vector<double>&)>& sort_func,
                                  std::vector<double> array) {
    auto start = std::chrono::high_resolution_clock::now();
    sort_func(array);
    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration<double, std::milli>(end - start).count();
}

template<typename Sorter>
std::function<void(std::vector<double>&)> create_sorter_func() {
    return [](std::vector<double>& arr) {
        Sorter sorter;
        sorter(arr);
    };
}

std::function<void(std::vector<double>&)> get_sorter_by_name(const std::string& name) {
    //if (name == "counting_sort")      return create_sorter_func<cppsort::counting_sorter>();
    //if (name == "heap_sort")          return create_sorter_func<cppsort::heap_sorter>();
    if (name == "insertion_sort")     return create_sorter_func<cppsort::insertion_sorter>();
    if (name == "merge_sort")         return create_sorter_func<cppsort::merge_sorter>();
    if (name == "quick_sort")         return create_sorter_func<cppsort::quick_sorter>();
    //if (name == "quick_merge_sort")   return create_sorter_func<cppsort::quick_merge_sorter>();
    //if (name == "ska_sort")           return create_sorter_func<cppsort::ska_sorter>();
    if (name == "spin_sort")          return create_sorter_func<cppsort::spin_sorter>();
    //if (name == "spread_sort")        return create_sorter_func<cppsort::spread_sorter>();
    if (name == "std_sort")           return create_sorter_func<cppsort::std_sorter>();
    if (name == "tim_sort")           return create_sorter_func<cppsort::tim_sorter>();
    throw std::invalid_argument("Unknown sorter: " + name);
}

PYBIND11_MODULE(sorters, m) {
    m.doc() = "Module for cpp-sort algorithms (double) with benchmarking";

    m.def("sort",
          [](const std::string& sorter_name, std::vector<double> array) {
              auto sort_func = get_sorter_by_name(sorter_name);
              sort_func(array);
              return array;
          },
          py::arg("sorter_name"), py::arg("array"),
          "Sort the array using the specified sorter and return the sorted array");

    m.def("benchmark_sorter",
          [](const std::string& sorter_name, const std::vector<double>& array) {
              auto sort_func = get_sorter_by_name(sorter_name);
              return benchmark_sorting_function(sort_func, array);
          },
          py::arg("sorter_name"), py::arg("array"),
          "Benchmark the specified sorter on an array (in ms)");

    m.def("list_sorters", []() {
        return std::vector<std::string>{ // counting_sort removed
            "insertion_sort", "merge_sort",
            "quick_sort", "spin_sort",
            "std_sort", "tim_sort"
            // "counting_sort", "ska_sort", "spread_sort"
        };
    }, "Return a list of all supported sorter names");
}
