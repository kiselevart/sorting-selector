#include <Python.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "benchmark.h" 

namespace py = pybind11;

PYBIND11_MODULE(sorters, m) {
    m.doc() = "C++ sorting algorithm benchmarks"; // Module docstring

    // Bind BenchmarkResult for quick_sorter
    py::class_<BenchmarkResult<cppsort::quick_sorter>>(m, "QuickSortBenchmarkResult")
        .def_readwrite("total_time_ms", &BenchmarkResult<cppsort::quick_sorter>::total_time_ms)
        .def_readwrite("times_by_size", &BenchmarkResult<cppsort::quick_sorter>::times_by_size);

    // Bind BenchmarkResult for merge_sorter
    py::class_<BenchmarkResult<cppsort::merge_sorter>>(m, "MergeSortBenchmarkResult")
        .def_readwrite("total_time_ms", &BenchmarkResult<cppsort::merge_sorter>::total_time_ms)
        .def_readwrite("times_by_size", &BenchmarkResult<cppsort::merge_sorter>::times_by_size);

    // Bind BenchmarkResult for insertion_sorter
    py::class_<BenchmarkResult<cppsort::insertion_sorter>>(m, "InsertionSortBenchmarkResult")
        .def_readwrite("total_time_ms", &BenchmarkResult<cppsort::insertion_sorter>::total_time_ms)
        .def_readwrite("times_by_size", &BenchmarkResult<cppsort::insertion_sorter>::times_by_size);

    // Bind generate_test_arrays function
    m.def("generate_test_arrays", &generate_test_arrays, "Generate test arrays for benchmarking");

    // Bind benchmark_sorter for quick_sorter
    m.def("benchmark_quick_sort", 
        [](const std::vector<std::vector<int>>& test_arrays) {
            cppsort::quick_sorter sorter;
            return benchmark_sorter(sorter, test_arrays);
        },
        "Benchmark quick sort algorithm");

    // Bind benchmark_sorter for merge_sorter
    m.def("benchmark_merge_sort",
        [](const std::vector<std::vector<int>>& test_arrays) {
            cppsort::merge_sorter sorter;
            return benchmark_sorter(sorter, test_arrays);
        },
        "Benchmark merge sort algorithm");

    // Bind benchmark_sorter for insertion_sorter
    m.def("benchmark_insertion_sort",
        [](const std::vector<std::vector<int>>& test_arrays) {
            cppsort::insertion_sorter sorter;
            return benchmark_sorter(sorter, test_arrays);
        },
        "Benchmark insertion sort algorithm");
}
