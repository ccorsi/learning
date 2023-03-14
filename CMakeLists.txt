# We are using the integrated version of GoogleTest with our builds and this is only supported in CMake 3.10.0 or greater
cmake_minimum_required(VERSION 3.10.0)
project(tools VERSION 0.3.9
    DESCRIPTION "Data Structure and Algorithm Solutions"
    HOMEPAGE_URL "https://github.com/ccorsi/learning/tree/cpp_data_structs_and_algos"
    LANGUAGES CXX)

# This is required to be able to have cmake generate the required test build files
enable_testing()

# This is required to be able to have cmake generate the required package files
include(CPack)

# setup the minimum C++ requirements
set(CXX_STANDARD 17)
set(CXX_STANDARD_REQUIRED true)

# Set the default library build to static instead of shared
option(BUILD_SHARED_LIBS "Build using shared libraries" OFF)

include(FetchContent)

# To be able to use google test framework we need to fetch the source code that will be used to build
# and run this projects tests using google test framework.
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG release-1.12.1
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

# add the different sub-projects to this build
add_subdirectory(utils)
add_subdirectory(arrays)
add_subdirectory(matrices)
add_subdirectory(strings)
add_subdirectory(dynamic_programming)
