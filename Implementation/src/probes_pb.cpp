#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/functional.h>
#include <cpp-sort/probes.h>
#include <functional>
#include <vector>
#include <string>

namespace py = pybind11;

// Template function to create probe function wrappers
template<typename Probe>
std::function<std::size_t(const std::vector<int>&)> create_probe_func() {
    return [](const std::vector<int>& arr) {
        Probe probe;
        return probe(arr);
    };
}

// Get probe function by name
std::function<std::size_t(const std::vector<int>&)> get_probe_by_name(const std::string& probe_name) {
    if (probe_name == "dis") {
        return create_probe_func<cppsort::probe::dis>();
    }
    else if (probe_name == "enc") {
        return create_probe_func<cppsort::probe::enc>();
    }
    else if (probe_name == "exc") {
        return create_probe_func<cppsort::probe::exc>();
    }
    else if (probe_name == "ham") {
        return create_probe_func<cppsort::probe::ham>();
    }
    else if (probe_name == "inv") {
        return create_probe_func<cppsort::probe::inv>();
    }
    else if (probe_name == "max") {
        return create_probe_func<cppsort::probe::max>();
    }
    else if (probe_name == "mono") {
        return create_probe_func<cppsort::probe::mono>();
    }
    else if (probe_name == "osc") {
        return create_probe_func<cppsort::probe::osc>();
    }
    else if (probe_name == "par") {
        return create_probe_func<cppsort::probe::par>();
    }
    else if (probe_name == "rem") {
        return create_probe_func<cppsort::probe::rem>();
    }
    else if (probe_name == "runs") {
        return create_probe_func<cppsort::probe::runs>();
    }
    else if (probe_name == "sus") {
        return create_probe_func<cppsort::probe::sus>();
    }
    else {
        throw std::invalid_argument("Unknown probe: " + probe_name);
    }
}

PYBIND11_MODULE(probes, m) {
    m.doc() = "Module for cpp-sort presortedness probes";

    // Function to measure presortedness with a specified probe
    m.def("measure", [](const std::string& probe_name, const std::vector<int>& array) {
        auto probe_func = get_probe_by_name(probe_name);
        return probe_func(array);
    }, py::arg("probe_name"), py::arg("array"),
       "Measure the presortedness of the array using the specified probe");

    // Function to return a list of all available probe names
    m.def("list_probes", []() -> std::vector<std::string> {
        return {
            "dis",  // Displacement
            "enc",  // Entropy
            "exc",  // Exchanges
            "ham",  // Hamming distance
            "inv",  // Inversions
            "max",  // Max
            "mono", // Monotonicity
            "osc",  // Oscillation
            "par",  // Par
            "rem",  // Rem
            "runs", // Runs
            "sus"   // Suspension
        };
    }, "Return a list of all supported presortedness probes");

    // Function to measure with all probes and return a dictionary
    m.def("measure_all", [](const std::vector<int>& array) {
        py::dict results;
        std::vector<std::string> probe_names = {
            "dis", "enc", "exc", "ham", "inv", "max", 
            "mono", "osc", "par", "rem", "runs", "sus"
        };
        
        for (const auto& name : probe_names) {
            auto probe_func = get_probe_by_name(name);
            results[py::str(name)] = probe_func(array);
        }
        
        return results;
    }, py::arg("array"),
       "Measure the presortedness of the array using all available probes");

    // Function to explain the meaning of a probe
    m.def("explain_probe", [](const std::string& probe_name) -> std::string {
        std::map<std::string, std::string> explanations = {
            {"dis", "Displacement: Sum of distances each element must move to reach its sorted position"},
            {"enc", "Entropy: Measure of disorder in the sequence based on information theory"},
            {"exc", "Exchanges: Minimum number of exchanges needed to sort the sequence"},
            {"ham", "Hamming distance: Number of elements that are not in their sorted position"},
            {"inv", "Inversions: Number of pairs of elements that are in the wrong order"},
            {"max", "Max: Maximum distance an element must move to reach its sorted position"},
            {"mono", "Monotonicity: Number of adjacent elements that are not in order"},
            {"osc", "Oscillation: Measures how elements are oscillating around their final positions"},
            {"par", "Par: Number of misplaced elements relative to a partition of the sequence"},
            {"rem", "Rem: Minimum number of elements to remove to obtain a sorted sequence"},
            {"runs", "Runs: Number of monotonically increasing subsequences"},
            {"sus", "Suspension: Measure of how suspended elements are from their sorted positions"}
        };
        
        if (explanations.find(probe_name) != explanations.end()) {
            return explanations[probe_name];
        } else {
            throw std::invalid_argument("Unknown probe: " + probe_name);
        }
    }, py::arg("probe_name"),
       "Explain the meaning of the specified presortedness probe");
}