// cppsort_module.cpp
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <cpp-sort/sorters.h>
#include <cpp-sort/sorter_traits.h>

namespace py = pybind11;

// Template function to create Python binding for any sorter
template<typename Sorter>
void bind_sorter(py::module& m, const char* name, const char* doc) {
    m.def(name,
        [](std::vector<int>& arr) {
            Sorter sorter;
            sorter(arr);
            return arr;
        },
        doc);
}

PYBIND11_MODULE(sorters, m) {
    m.doc() = "C++ sorting algorithms from cpp-sort"; // Module docstring

    bind_sorter<cppsort::adaptive_shivers_sorter>(m, "adaptive_shivers_sort", "Sort array using Adaptive Shivers Sort");
    bind_sorter<cppsort::cartesian_tree_sorter>(m, "cartesian_tree_sort", "Sort array using Cartesian Tree Sort");
    bind_sorter<cppsort::counting_sorter>(m, "counting_sort", "Sort array using Counting Sort");
    bind_sorter<cppsort::drop_merge_sorter>(m, "drop_merge_sort", "Sort array using Drop Merge Sort");
    bind_sorter<cppsort::heap_sorter>(m, "heap_sort", "Sort array using Heap Sort");
    bind_sorter<cppsort::insertion_sorter>(m, "insertion_sort", "Sort array using Insertion Sort");
    bind_sorter<cppsort::mel_sorter>(m, "mel_sort", "Sort array using MEL Sort");
    bind_sorter<cppsort::merge_insertion_sorter>(m, "merge_insertion_sort", "Sort array using Merge Insertion Sort");
    bind_sorter<cppsort::merge_sorter>(m, "merge_sort", "Sort array using Merge Sort");
    bind_sorter<cppsort::poplar_sorter>(m, "poplar_sort", "Sort array using Poplar Sort");
    bind_sorter<cppsort::quick_sorter>(m, "quick_sort", "Sort array using Quick Sort");
    bind_sorter<cppsort::quick_merge_sorter>(m, "quick_merge_sort", "Sort array using Quick Merge Sort");
    bind_sorter<cppsort::selection_sorter>(m, "selection_sort", "Sort array using Selection Sort");
    bind_sorter<cppsort::ska_sorter>(m, "ska_sort", "Sort array using Ska Sort");
    bind_sorter<cppsort::slab_sorter>(m, "slab_sort", "Sort array using Slab Sort");
    bind_sorter<cppsort::smooth_sorter>(m, "smooth_sort", "Sort array using Smooth Sort");
    bind_sorter<cppsort::spin_sorter>(m, "spin_sort", "Sort array using Spin Sort");
    bind_sorter<cppsort::splay_sorter>(m, "splay_sort", "Sort array using Splay Sort");
    bind_sorter<cppsort::spread_sorter>(m, "spread_sort", "Sort array using Spread Sort");
    bind_sorter<cppsort::split_sorter>(m, "split_sort", "Sort array using Split Sort");
    bind_sorter<cppsort::std_sorter>(m, "std_sort", "Sort array using std::sort");
    bind_sorter<cppsort::tim_sorter>(m, "tim_sort", "Sort array using Tim Sort");
    bind_sorter<cppsort::verge_sorter>(m, "verge_sort", "Sort array using Verge Sort");
}