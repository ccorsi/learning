cmake_minimum_required(VERSION 3.5.0)
project(registry VERSION 0.1.0 LANGUAGES C CXX)

# setup the minimum C++ requirements
set(CXX_STANDARD 17)
set(CXX_STANDARD_REQUIRED true)

include_directories(winreg/WinReg)

add_executable(registry main.cpp)
target_compile_features(registry PUBLIC cxx_std_17)

include(CTest)
enable_testing()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
