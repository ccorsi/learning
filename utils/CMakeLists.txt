# We need at least version 3.10.0 to be able to use the GoogleTest package
cmake_minimum_required(VERSION 3.10.0)
project(search VERSION 0.1.0)

set(CXX_STANDARD 17)
set(CXX_STANDARD_REQUIRED true)

# add the current projects includes directory
include_directories(includes)

# generate a shared utilities library that can be used by the different projects
add_library(utils SHARED debug.cpp)
