cmake_minimum_required(VERSION 3.10.0)
project("Data Loader Point Vector Example"
    LANGUAGES C CXX)

include(CTest)
# This is required to be able to have cmake generate the required test build files
enable_testing()

# setup the minimum C++ requirements
set(CXX_STANDARD 20)
set(CXX_STANDARD_REQUIRED true)

# add the current projects includes directory
include_directories(../../includes)

# set the executable name
set(prog pointvector)

# create the main executable
add_executable(${prog} main.cpp)
# set compiler C++
target_compile_features(${prog} PUBLIC cxx_std_20)

add_test(NAME ${prog} COMMAND ${prog} WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

