// cppsort_module.cpp
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <cpp-sort/sorters.h>
#include <cpp-sort/sorters/quick_sorter.h>
#include <cpp-sort/sorters/merge_sorter.h>
#include <cpp-sort/sorters/insertion_sorter.h>

namespace py = pybind11;

PYBIND11_MODULE(sorters, m) {
    m.doc() = "C++ sorting algorithms from cpp-sort"; // Module docstring

    // Quick Sort
    m.def("quick_sort", 
        [](std::vector<int>& arr) {
            cppsort::quick_sorter sorter;
            sorter(arr);
            return arr;
        },
        "Sort array using Quick Sort");

    // Merge Sort
    m.def("merge_sort",
        [](std::vector<int>& arr) {
            cppsort::merge_sorter sorter;
            sorter(arr);
            return arr;
        },
        "Sort array using Merge Sort");

    // Insertion Sort
    m.def("insertion_sort",
        [](std::vector<int>& arr) {
            cppsort::insertion_sorter sorter;
            sorter(arr);
            return arr;
        },
        "Sort array using Insertion Sort");
}
