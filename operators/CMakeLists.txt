# We are using the integrated version of GoogleTest with our builds and this is only supported in CMake 3.10.0 or greater
cmake_minimum_required(VERSION 3.10.0)
project(tools VERSION 0.1.0)

# setup the minimum C++ requirements
set(CXX_STANDARD 17)
set(CXX_STANDARD_REQUIRED true)

# To be able to use google test framework we need to fetch the source code that will be used to build
# and run this projects tests using google test framework.
include(FetchContent)
FetchContent_Declare(
    googletest 
    URL https://github.com/google/googletest/archive/refs/tags/release-1.11.0.zip
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# do I need to this include to be able to use GoogleTest?
include(ctest)
include(GoogleTest)

enable_testing()

add_executable(testme test.cpp)

add_test(testme test)

# link in the googletest library for each googletest tests
target_link_libraries(testme gtest_main)

# request that we discover all googletest tests for the given test executables
gtest_discover_tests(testme)
