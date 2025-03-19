########## MACROS ###########################################################################
#############################################################################################

# Requires CMake > 3.15
if(${CMAKE_VERSION} VERSION_LESS "3.15")
    message(FATAL_ERROR "The 'CMakeDeps' generator only works with CMake >= 3.15")
endif()

if(cpp-sort_FIND_QUIETLY)
    set(cpp-sort_MESSAGE_MODE VERBOSE)
else()
    set(cpp-sort_MESSAGE_MODE STATUS)
endif()

include(${CMAKE_CURRENT_LIST_DIR}/cmakedeps_macros.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/cpp-sortTargets.cmake)
include(CMakeFindDependencyMacro)

check_build_type_defined()

foreach(_DEPENDENCY ${cpp-sort_FIND_DEPENDENCY_NAMES} )
    # Check that we have not already called a find_package with the transitive dependency
    if(NOT ${_DEPENDENCY}_FOUND)
        find_dependency(${_DEPENDENCY} REQUIRED ${${_DEPENDENCY}_FIND_MODE})
    endif()
endforeach()

set(cpp-sort_VERSION_STRING "1.16.0")
set(cpp-sort_INCLUDE_DIRS ${cpp-sort_INCLUDE_DIRS_RELEASE} )
set(cpp-sort_INCLUDE_DIR ${cpp-sort_INCLUDE_DIRS_RELEASE} )
set(cpp-sort_LIBRARIES ${cpp-sort_LIBRARIES_RELEASE} )
set(cpp-sort_DEFINITIONS ${cpp-sort_DEFINITIONS_RELEASE} )


# Only the last installed configuration BUILD_MODULES are included to avoid the collision
foreach(_BUILD_MODULE ${cpp-sort_BUILD_MODULES_PATHS_RELEASE} )
    message(${cpp-sort_MESSAGE_MODE} "Conan: Including build module from '${_BUILD_MODULE}'")
    include(${_BUILD_MODULE})
endforeach()


