from typing import Callable, Any, Literal

# All supported presortedness probes
# "dis", "enc", "exc", "ham", "inv", "max", "mono", "osc", "rem", "runs", "sus"
ProbeName = Literal[
    "dis", "enc", "exc", "ham", "inv",
    "max", "mono", "osc", "rem", "runs", "sus"
]

def measure(probe_name: ProbeName, array: list[float]) -> int: ...
def list_probes() -> list[ProbeName]: ...
def measure_all(array: list[float]) -> dict[ProbeName, int]: ...
def explain_probe(probe_name: ProbeName) -> str: ...
def benchmark_probe_function(probe_func: Callable[[list[float]], Any], array: list[float]) -> float: ...
def benchmark_probe_by_name(probe_name: ProbeName, array: list[float]) -> float: ...
def max_for_size(probe_name: ProbeName, n: int) -> int: ...

__all__: list[str] = [
    "measure",
    "list_probes",
    "measure_all",
    "explain_probe",
    "benchmark_probe_function",
    "benchmark_probe_by_name",
    "max_for_size",
]
