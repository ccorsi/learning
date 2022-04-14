# We need at least version 3.10.0 to be able to use the GoogleTest package
cmake_minimum_required(VERSION 3.10.0)
project(search VERSION 0.1.0)

# set the minimum version of C++ that is required to build and execute these search algorithms
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

# NOTE: This did not fix the issue with linking a shared library
# State that utils default is a shared library
# set_target_properties(utils PROPERTIES
#     POSITION_INDEPENDENT_CODE ${BUILD_SHARED_LIBS}
# )

# setup a property that contains the names of the different test executables
set(EXECS dfstests bfstests gdfstests dlstests idstests ucstests gbfstests)

# foreach(exec dfstests bfstests gdfstests dlstests idstests ucstests gbfstests)
foreach(exec ${EXECS})
    message(STATUS "Setting up executable: ${exec}")
    # create the different test executables
    add_executable(${exec} ${exec}.cpp)
    # link in the googletest library for each googletest test
    target_link_libraries(${exec} PUBLIC gtest_main utils)
    # request that we discover all googletest tests for the given test executable
    gtest_discover_tests(${exec} WORKING_DIRECTORY ${WORKING_DIRECTORY})
endforeach()
