# We need at least version 3.10.0 to be able to use the GoogleTest package
cmake_minimum_required(VERSION 3.10.0)
project(search VERSION 0.1.0)

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

# create the different test executables
add_executable(dfstests dfstests.cpp)      # this contains tests associated with the DFS implementation
add_executable(bfstests bfstests.cpp)      # this contains tests associated with the BFS implementation
add_executable(gdfstests gdfstests.cpp)    # this contains tests associated with the DFS implementation
add_executable(dlstests dlstests.cpp)      # this contains tests associated with the DLS implementation
add_executable(idstests idstests.cpp)      # this contains tests associated with the IDS implementation
add_executable(ucstests ucstests.cpp)      # this contains tests associated with the UCS implementation

# link in the googletest library for each googletest tests
target_link_libraries(gdfstests LINK_PUBLIC gtest_main utils)
target_link_libraries(bfstests LINK_PUBLIC gtest_main utils)
target_link_libraries(dlstests LINK_PUBLIC gtest_main utils)
target_link_libraries(idstests LINK_PUBLIC gtest_main utils)
target_link_libraries(ucstests LINK_PUBLIC gtest_main utils)

target_link_libraries(dfstests PUBLIC utils)

# request that we discover all googletest tests for the given test executables
gtest_discover_tests(gdfstests bfstests gdlstests idstests ucstests)

# create a regular ctest test that doesn't use googletest
# add_test(NAME test_bfs COMMAND bfstests)
