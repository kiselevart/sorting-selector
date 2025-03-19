########### AGGREGATED COMPONENTS AND DEPENDENCIES FOR THE MULTI CONFIG #####################
#############################################################################################

set(cpp-sort_COMPONENT_NAMES "")
if(DEFINED cpp-sort_FIND_DEPENDENCY_NAMES)
  list(APPEND cpp-sort_FIND_DEPENDENCY_NAMES )
  list(REMOVE_DUPLICATES cpp-sort_FIND_DEPENDENCY_NAMES)
else()
  set(cpp-sort_FIND_DEPENDENCY_NAMES )
endif()

########### VARIABLES #######################################################################
#############################################################################################
set(cpp-sort_PACKAGE_FOLDER_RELEASE "/Users/kisel/.conan2/p/cpp-s9ade0216431e1/p")
set(cpp-sort_BUILD_MODULES_PATHS_RELEASE )


set(cpp-sort_INCLUDE_DIRS_RELEASE "${cpp-sort_PACKAGE_FOLDER_RELEASE}/include")
set(cpp-sort_RES_DIRS_RELEASE )
set(cpp-sort_DEFINITIONS_RELEASE )
set(cpp-sort_SHARED_LINK_FLAGS_RELEASE )
set(cpp-sort_EXE_LINK_FLAGS_RELEASE )
set(cpp-sort_OBJECTS_RELEASE )
set(cpp-sort_COMPILE_DEFINITIONS_RELEASE )
set(cpp-sort_COMPILE_OPTIONS_C_RELEASE )
set(cpp-sort_COMPILE_OPTIONS_CXX_RELEASE )
set(cpp-sort_LIB_DIRS_RELEASE )
set(cpp-sort_BIN_DIRS_RELEASE )
set(cpp-sort_LIBRARY_TYPE_RELEASE UNKNOWN)
set(cpp-sort_IS_HOST_WINDOWS_RELEASE 0)
set(cpp-sort_LIBS_RELEASE )
set(cpp-sort_SYSTEM_LIBS_RELEASE )
set(cpp-sort_FRAMEWORK_DIRS_RELEASE )
set(cpp-sort_FRAMEWORKS_RELEASE )
set(cpp-sort_BUILD_DIRS_RELEASE )
set(cpp-sort_NO_SONAME_MODE_RELEASE FALSE)


# COMPOUND VARIABLES
set(cpp-sort_COMPILE_OPTIONS_RELEASE
    "$<$<COMPILE_LANGUAGE:CXX>:${cpp-sort_COMPILE_OPTIONS_CXX_RELEASE}>"
    "$<$<COMPILE_LANGUAGE:C>:${cpp-sort_COMPILE_OPTIONS_C_RELEASE}>")
set(cpp-sort_LINKER_FLAGS_RELEASE
    "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,SHARED_LIBRARY>:${cpp-sort_SHARED_LINK_FLAGS_RELEASE}>"
    "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,MODULE_LIBRARY>:${cpp-sort_SHARED_LINK_FLAGS_RELEASE}>"
    "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,EXECUTABLE>:${cpp-sort_EXE_LINK_FLAGS_RELEASE}>")


set(cpp-sort_COMPONENTS_RELEASE )