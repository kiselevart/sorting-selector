# Get the path to the Python executable using the system's 'which' command
execute_process(
    COMMAND which python
    OUTPUT_VARIABLE PYTHON_PATH
    OUTPUT_STRIP_TRAILING_WHITESPACE
)
message(STATUS "Using Python: ${PYTHON_PATH}")

# Set the Python3 executable to the one we just found
set(Python3_EXECUTABLE "${PYTHON_PATH}")

# Now continue with your configuration
cmake_minimum_required(VERSION 3.10)
project(sorters LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# set(Python3_ROOT_DIR "/Users/kisel/miniconda3/envs/your_env")
# set(CMAKE_PREFIX_PATH "/Users/kisel/miniconda3/envs/your_env")

# Find Python3 (with a minimum version if necessary) and pybind11
find_package(Python3 3.13 COMPONENTS Interpreter Development REQUIRED)
find_package(pybind11 REQUIRED)

# Add cpp-sort as a subdirectory
add_subdirectory(cpp-sort)

# Create the Python module using pybind11_add_module
pybind11_add_module(sorters 
    src/bindings.cpp
    src/benchmark.cpp
)

# Add the src directory to the include path
target_include_directories(sorters PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)

# Link against cpp-sort and Python3
target_link_libraries(sorters PRIVATE 
    cpp-sort::cpp-sort
    Python3::Python
)
