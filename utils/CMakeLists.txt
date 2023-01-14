# We need at least version 3.10.0 to be able to use the GoogleTest package
cmake_minimum_required(VERSION 3.10.0)
project(techiedelight VERSION 0.1.0)

set(CXX_STANDARD 17)
set(CXX_STANDARD_REQUIRED true)

# add the current projects includes directory
include_directories(includes)

# do I need to this include to be able to use GoogleTest?
include(GoogleTest)

enable_testing()

# generate a shared utilities library that can be used by the different projects
# add_library(utils SHARED debug.cpp)
# TODO: for the moment I am unable to determine how to link the shared library.
# Until then I will create a static library instead.
add_library(utils debug.cpp)

set(TESTS debugtests)

foreach(name ${TESTS})
    message(STATUS "Setting up test: ${name}")
    # create the different test executables
    add_executable(${name} ${name}.cpp)
    # link in the googletest library for each googletest test
    target_link_libraries(${name} PUBLIC gtest_main gmock_main utils)
    # request that we discover all googletest tests for the given test executable
    gtest_discover_tests(${name} WORKING_DIRECTORY ${WORKING_DIRECTORY})
endforeach()
