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
project(cpp_sort_extensions)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Python3 COMPONENTS Interpreter Development REQUIRED)
find_package(pybind11 REQUIRED)

# Add cpp-sort as a subdirectory
add_subdirectory(cpp-sort)

# Create source directory if it doesn't exist
file(MAKE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/src)

# Add the sorters Python module
pybind11_add_module(sorters 
    src/sorters_pb.cpp
)

# Add the probes Python module
pybind11_add_module(probes
    src/probes_pb.cpp
)

# Include directories for both modules
target_include_directories(sorters PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${Python3_INCLUDE_DIRS}
    ${pybind11_INCLUDE_DIRS}
)

target_include_directories(probes PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${Python3_INCLUDE_DIRS}
    ${pybind11_INCLUDE_DIRS}
)

# Link against cpp-sort for both modules
target_link_libraries(sorters PRIVATE cpp-sort::cpp-sort)
target_link_libraries(probes PRIVATE cpp-sort::cpp-sort)

# Set output directory for both modules
set_target_properties(sorters PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/lib
)

set_target_properties(probes PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/lib
)

# Install targets
install(TARGETS sorters probes
    LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/python${Python3_VERSION_MAJOR}.${Python3_VERSION_MINOR}/site-packages
)

# If no build type is set, default to Release
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build." FORCE)
endif()

# Optionally force specific flags for Release mode:
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG" CACHE STRING "Release flags" FORCE)
