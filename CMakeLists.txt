# We are using the integrated version of GoogleTest with our builds and this is only supported in CMake 3.10.0 or greater
cmake_minimum_required(VERSION 3.10.0)
project("Data Loader"
    VERSION 0.9.1 # Update the examples/CMakeLists.txt file
    DESCRIPTION "Template Based Data Loader Class"
    HOMEPAGE_URL "https://github.com/ccorsi/learning/tree/dataloader"
    LANGUAGES C CXX)

include(CTest)
# This is required to be able to have cmake generate the required test build files
enable_testing()

# setup the minimum C++ requirements
set(CXX_STANDARD 20)
set(CXX_STANDARD_REQUIRED true)

# Set the default library build to static instead of shared
option(BUILD_SHARED_LIBS "Build using shared libraries" OFF)

# Required to download the sources to GoogleTest that will be used by this project
include(FetchContent)

# To be able to use google test framework we need to fetch the source code that will be used to build
# and run this projects tests using google test framework.
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG main # Always use the latest version of GoogleTest as per the GoogleTest Team
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Fetch the contents from the GoogleTest project on github.com
FetchContent_MakeAvailable(googletest)

# add the current projects includes directory
include_directories(includes)

# do I need to this include to be able to use GoogleTest?
include(GoogleTest)

# create a TESTS property that contains a list of the different test files that will be used to test this project
# data loader implementation
set(TESTS checkerstests dataloadertests)

foreach(name ${TESTS})
    message(STATUS "Setting up test: ${name}")
    # create the different test executables
    add_executable(${name} ${name}.cpp)
    # link in the googletest library for each googletest test
    target_link_libraries(${name} PUBLIC gtest_main gmock_main)
    # set compiler C++
    target_compile_features(${name} PUBLIC cxx_std_20)
    # request that we discover all googletest tests for the given test executable
    gtest_discover_tests(${name} WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
endforeach()

# add examples directory to the build process
add_subdirectory(examples)

# I need to create a package of the current include files that can be downloaded by groups that
# don't use CMake's FetchContent tool or other build tools similar features.
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
