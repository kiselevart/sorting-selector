#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <cpp-sort/probes.h>
#include <vector>
#include <string>
#include <functional>
#include <chrono>
#include <map>

namespace py = pybind11;

double benchmark_probe_function(const std::function<void(std::vector<double>&)>& probe_func,
                                std::vector<double> array) {
    auto start = std::chrono::high_resolution_clock::now();
    probe_func(array);
    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration<double, std::milli>(end - start).count();
}

std::size_t apply_probe_by_name(const std::string& probe_name, const std::vector<double>& arr) {
    if (probe_name == "dis")    return cppsort::probe::dis(arr);
    if (probe_name == "enc")    return cppsort::probe::enc(arr);
    if (probe_name == "exc")    return cppsort::probe::exc(arr);
    if (probe_name == "ham")    return cppsort::probe::ham(arr);
    if (probe_name == "inv")    return cppsort::probe::inv(arr);
    if (probe_name == "max")    return cppsort::probe::max(arr);
    if (probe_name == "mono")   return cppsort::probe::mono(arr);
    if (probe_name == "osc")    return cppsort::probe::osc(arr);
    if (probe_name == "rem")    return cppsort::probe::rem(arr);
    if (probe_name == "runs")   return cppsort::probe::runs(arr);
    if (probe_name == "sus")    return cppsort::probe::sus(arr);
    throw std::invalid_argument("Unknown probe: " + probe_name);
}

std::vector<std::string> get_all_probe_names() {
    return {"dis","enc","exc","ham","inv","max","mono","osc","rem","runs","sus"};
}

std::string get_probe_explanation(const std::string& probe_name) {
    static const std::map<std::string,std::string> explanations = {
        {"dis","Displacement: Sum of distances each element must move to reach its sorted position"},
        {"enc","Encroachment: Computes the number of encroaching lists that can be extracted from X minus one"},
        {"exc","Exchanges: Minimum number of exchanges needed to sort the sequence"},
        {"ham","Hamming distance: Number of elements that are not in their sorted position"},
        {"inv","Inversions: Number of pairs of elements that are in the wrong order"},
        {"max","Max: Maximum distance an element must move to reach its sorted position"},
        {"mono","Monotonicity: Number of adjacent elements that are not in order"},
        {"osc","Oscillation: Measures how elements are oscillating around their final positions"},
        {"rem","Rem: Minimum number of elements to remove to obtain a sorted sequence"},
        {"runs","Runs: Number of monotonically increasing subsequences"},
        {"sus","Suspension: Measure of how suspended elements are from their sorted positions"}
    };
    auto it = explanations.find(probe_name);
    if (it != explanations.end()) return it->second;
    throw std::invalid_argument("Unknown probe: " + probe_name);
}

PYBIND11_MODULE(probes, m) {
    m.doc() = "Module for cpp-sort presortedness probes (double)";

    m.def("measure",
          [](const std::string& probe_name, const std::vector<double>& array) {
              return apply_probe_by_name(probe_name, array);
          },
          py::arg("probe_name"), py::arg("array"),
          "Measure presortedness with the specified probe");

    m.def("list_probes", []() { return get_all_probe_names(); },
          "Return list of supported presortedness probes");

    m.def("measure_all",
          [](const std::vector<double>& array) {
              py::dict results;
              for (auto const& name : get_all_probe_names()) {
                  results[py::str(name)] = apply_probe_by_name(name, array);
              }
              return results;
          },
          py::arg("array"),
          "Measure presortedness using all probes");

    m.def("explain_probe",
          [](const std::string& probe_name) { return get_probe_explanation(probe_name); },
          py::arg("probe_name"),
          "Explain a presortedness probe");

    m.def("benchmark_probe_function",
          [](py::function probe_func, std::vector<double> array) {
              auto wrapper = [probe_func](std::vector<double>& arr) { probe_func(arr); };
              return benchmark_probe_function(wrapper, array);
          },
          py::arg("probe_func"), py::arg("array"),
          "Benchmark a custom probe function");

    m.def("benchmark_probe_by_name",
          [](const std::string& probe_name, const std::vector<double>& array) {
              auto func = [probe_name](std::vector<double>& arr) { (void)apply_probe_by_name(probe_name, arr); };
              return benchmark_probe_function(func, array);
          },
          py::arg("probe_name"), py::arg("array"),
          "Benchmark a named probe");

    m.def("max_for_size",
          [](const std::string& probe_name, int n) {
              if      (probe_name == "dis")  return cppsort::probe::dis.max_for_size(n);
              if      (probe_name == "enc")  return cppsort::probe::enc.max_for_size(n);
              if      (probe_name == "exc")  return cppsort::probe::exc.max_for_size(n);
              if      (probe_name == "ham")  return cppsort::probe::ham.max_for_size(n);
              if      (probe_name == "inv")  return cppsort::probe::inv.max_for_size(n);
              if      (probe_name == "max")  return cppsort::probe::max.max_for_size(n);
              if      (probe_name == "mono") return cppsort::probe::mono.max_for_size(n);
              if      (probe_name == "osc")  return cppsort::probe::osc.max_for_size(n);
              if      (probe_name == "rem")  return cppsort::probe::rem.max_for_size(n);
              if      (probe_name == "runs") return cppsort::probe::runs.max_for_size(n);
              if      (probe_name == "sus")  return cppsort::probe::sus.max_for_size(n);
              throw std::invalid_argument("Unknown probe: " + probe_name);
          },
          py::arg("probe_name"), py::arg("n"),
          "Maximum possible probe value for array length n");
}
