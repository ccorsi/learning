# We are using the integrated version of GoogleTest with our builds and this is only supported in CMake 3.10.0 or greater
cmake_minimum_required(VERSION 3.10.0)
project(bit_manipulation VERSION 0.0.6)

# setup the minimum C++ requirements
set(CXX_STANDARD 17)
set(CXX_STANDARD_REQUIRED true)

# add the general utilities include directory
include_directories(../utils/includes includes)

# Include GoogleTest for testing the different implementations
include(GoogleTest)

enable_testing()

set(NAMES turn_off_kth_bit turn_on_kth_bit is_kth_bit_set toggle_kth_bit unset_rightmost_set_bit
    position_of_rightmost_set_bit count_set_bits count_flipped_bits next_power_of_two
    previous_power_of_two parity_of_number swap_bits swap_bits_two power_of_four power_of_eight
    reverse_bits swap_adjacent_bits adjacent_set_bits decimal_to_binary add_binary circular_shift
    xor_without_xoring missing_number missing_number_two missing_number_three odd_occurring_element
    odd_occurring_element_two)

# build the different implementations and its tests
foreach(name IN LISTS NAMES)
    # mention which executable we are building
    message("Building executable ${name}tests")
    # create the different test executables
    add_executable(${name}tests ${name}tests.cpp ${name}.cpp )
    # link in the googletest library for each googletest test
    target_link_libraries(${name}tests PUBLIC gtest_main gmock_main utils)
    # set compiler C++
    target_compile_features(${name}tests PUBLIC cxx_std_17)
    # request that we discover all googletest tests for the given test executable
    gtest_discover_tests(${name}tests)
    # mention that we've completed the building of the executable
    message("Built executable ${name}tests")
endforeach()
