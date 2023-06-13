# We need at least version 3.10.0 to be able to use the GoogleTest package
cmake_minimum_required(VERSION 3.10.0)
project(utils VERSION 0.1.8)

set(CXX_STANDARD 17)
set(CXX_STANDARD_REQUIRED true)

# add the current projects includes directory
include_directories(includes)

# do I need to this include to be able to use GoogleTest?
include(GoogleTest)

enable_testing()

# use a variable to be able to skip between the creation of a static or shared library
set(SRCS debug.cpp paths.cpp checkers.cpp)

# generate a shared utilities library that can be used by the different projects
# TODO: for the moment I am unable to determine how to link the shared library.
# Until then I will create a static library instead.
# add_library(utils SHARED ${SRCS})
# alas you can't create a static and dynamic library wth the same name even thou
# their suffix are different but this is only the case on windows
# generate a static library
add_library(utils STATIC ${SRCS})

set(TESTS debugtests loadertests vectorloadertests matrixloadertests setloadertests checkerstests primitiveLoadertests
          maploadertests tupleloadertests dataloadertests)

foreach(name ${TESTS})
    message(STATUS "Setting up test: ${name}")
    # create the different test executables
    add_executable(${name} ${name}.cpp)
    # link in the googletest library for each googletest test
    target_link_libraries(${name} PUBLIC gtest_main gmock_main utils)
    # set compiler C++
    target_compile_features(${name} PUBLIC cxx_std_17)
    # request that we discover all googletest tests for the given test executable
    gtest_discover_tests(${name} WORKING_DIRECTORY ${WORKING_DIRECTORY})
endforeach()
