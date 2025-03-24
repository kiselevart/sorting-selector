#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <cpp-sort/probes.h>
#include <vector>
#include <string>
#include <functional>
#include <chrono>
#include <map>

namespace py = pybind11;

double benchmark_probe_function(const std::function<void(std::vector<int>&)>& probe_func, 
                                  std::vector<int> array) { // Pass by value
    // Start timing
    auto start = std::chrono::high_resolution_clock::now();
    
    probe_func(array); 

    // End timing
    auto end = std::chrono::high_resolution_clock::now();
    
    // Calculate and return the duration in milliseconds
    std::chrono::duration<double, std::milli> duration = end - start;
    return duration.count();
}

// Apply probe directly by name
std::size_t apply_probe_by_name(const std::string& probe_name, const std::vector<int>& arr) {
    if (probe_name == "dis") {
        return cppsort::probe::dis(arr);
    }
    else if (probe_name == "enc") {
        return cppsort::probe::enc(arr);
    }
    else if (probe_name == "exc") {
        return cppsort::probe::exc(arr);
    }
    else if (probe_name == "ham") {
        return cppsort::probe::ham(arr);
    }
    else if (probe_name == "inv") {
        return cppsort::probe::inv(arr);
    }
    else if (probe_name == "max") {
        return cppsort::probe::max(arr);
    }
    else if (probe_name == "mono") {
        return cppsort::probe::mono(arr);
    }
    else if (probe_name == "osc") {
        return cppsort::probe::osc(arr);
    }
    else if (probe_name == "rem") {
        return cppsort::probe::rem(arr);
    }
    else if (probe_name == "runs") {
        return cppsort::probe::runs(arr);
    }
    else if (probe_name == "sus") {
        return cppsort::probe::sus(arr);
    }
    else {
        throw std::invalid_argument("Unknown probe: " + probe_name);
    }
}

// Get list of all available probes
std::vector<std::string> get_all_probe_names() {
    return {
        "dis",  // Displacement
        "enc",  // Entropy
        "exc",  // Exchanges
        "ham",  // Hamming distance
        "inv",  // Inversions
        "max",  // Max
        "mono", // Monotonicity
        "osc",  // Oscillation
        "rem",  // Rem
        "runs", // Runs
        "sus"   // Suspension
    };
}

// Get explanation for a probe
std::string get_probe_explanation(const std::string& probe_name) {
    static const std::map<std::string, std::string> explanations = {
        {"dis", "Displacement: Sum of distances each element must move to reach its sorted position"},
        {"enc", "Entropy: Measure of disorder in the sequence based on information theory"},
        {"exc", "Exchanges: Minimum number of exchanges needed to sort the sequence"},
        {"ham", "Hamming distance: Number of elements that are not in their sorted position"},
        {"inv", "Inversions: Number of pairs of elements that are in the wrong order"},
        {"max", "Max: Maximum distance an element must move to reach its sorted position"},
        {"mono", "Monotonicity: Number of adjacent elements that are not in order"},
        {"osc", "Oscillation: Measures how elements are oscillating around their final positions"},
        {"rem", "Rem: Minimum number of elements to remove to obtain a sorted sequence"},
        {"runs", "Runs: Number of monotonically increasing subsequences"},
        {"sus", "Suspension: Measure of how suspended elements are from their sorted positions"}
    };
    
    auto it = explanations.find(probe_name);
    if (it != explanations.end()) {
        return it->second;
    } else {
        throw std::invalid_argument("Unknown probe: " + probe_name);
    }
}

PYBIND11_MODULE(probes, m) {
    m.doc() = "Module for cpp-sort presortedness probes";

    // Function to measure presortedness with a specified probe
    m.def("measure", [](const std::string& probe_name, const std::vector<int>& array) {
        return apply_probe_by_name(probe_name, array);
    }, py::arg("probe_name"), py::arg("array"),
       "Measure the presortedness of the array using the specified probe");

    // Function to return a list of all available probe names
    m.def("list_probes", []() {
        return get_all_probe_names();
    }, "Return a list of all supported presortedness probes");

    // Function to measure with all probes and return a dictionary
    m.def("measure_all", [](const std::vector<int>& array) {
        py::dict results;
        for (const auto& name : get_all_probe_names()) {
            results[py::str(name)] = apply_probe_by_name(name, array);
        }
        return results;
    }, py::arg("array"),
       "Measure the presortedness of the array using all available probes");

    // Function to explain the meaning of a probe
    m.def("explain_probe", [](const std::string& probe_name) {
        return get_probe_explanation(probe_name);
    }, py::arg("probe_name"),
       "Explain the meaning of the specified presortedness probe");

    m.def("benchmark_probe_function", 
          [](py::function probe_func, std::vector<int> array) -> double {
              // Wrap the Python function into a lambda matching std::function<void(std::vector<int>&)>
              auto func_wrapper = [probe_func](std::vector<int>& arr) {
                  probe_func(arr);
              };
              return benchmark_probe_function(func_wrapper, array);
          },
          py::arg("probe_func"), py::arg("array"),
          "Benchmark a probe function by measuring the execution time (in milliseconds) it takes to run on a copy of the provided array");

    m.def("benchmark_probe_by_name", 
        [](const std::string& probe_name, const std::vector<int>& array) -> double {
            // Create a lambda that wraps our apply_probe_by_name call.
            // We ignore the return value since benchmark_probe_function just measures time.
            auto func = [probe_name](std::vector<int>& arr) {
                (void) apply_probe_by_name(probe_name, arr);
            };
            return benchmark_probe_function(func, array);
        },
        py::arg("probe_name"), py::arg("array"),
        "Benchmark a probe function given its name by measuring the execution time.");
}