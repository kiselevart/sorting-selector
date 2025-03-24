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
project(sorters)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Python3 COMPONENTS Interpreter Development REQUIRED)
find_package(pybind11 REQUIRED)

# Add cpp-sort as a subdirectory
add_subdirectory(cpp-sort)

# Add the Python module
pybind11_add_module(sorters 
    src/sorters_pb.cpp
)

# Include directories
target_include_directories(sorters PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${Python3_INCLUDE_DIRS}
    ${pybind11_INCLUDE_DIRS}
)

# Link against cpp-sort
target_link_libraries(sorters PRIVATE cpp-sort::cpp-sort)