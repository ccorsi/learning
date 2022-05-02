# We are using the integrated version of GoogleTest with our builds and this is only supported in CMake 3.10.0 or greater
cmake_minimum_required(VERSION 3.10.0)
project(lists VERSION 0.1.0)

# setup the minimum C++ requirements
set(CXX_STANDARD 17)
set(CXX_STANDARD_REQUIRED true)

# add the general utilities include directory
include_directories(../utils/includes)

# add the current projects includes directory
include_directories(includes)

# do I need to this include to be able to use GoogleTest?
include(CTest)
include(GoogleTest)

enable_testing()

# setup a property that contains the names of the different test executables
set(EXECS linkedlisttests heaptests)

foreach(exec ${EXECS})
    message(STATUS "Setting up executable: ${exec}")
    # create the different test executables
    add_executable(${exec} ${exec}.cpp)
    # link in the googletest library for each googletest test
    target_link_libraries(${exec} PUBLIC gtest_main utils)
    # request that we discover all googletest tests for the given test executable
    gtest_discover_tests(${exec})
endforeach()
