# We are using the integrated version of GoogleTest with our builds and this is only supported in CMake 3.10.0 or greater
cmake_minimum_required(VERSION 3.10.0)
project(arrays VERSION 0.1.9)

# setup the minimum C++ requirements
set(CXX_STANDARD 17)
set(CXX_STANDARD_REQUIRED true)

# add the general utilities include directory
include_directories(includes ../utils/includes)

# Include GoogleTest for testing the different implementations
include(GoogleTest)

enable_testing()

set(NAMES two_sum zero_sum zero_sum_arrays sort_binary_array_inline maximum_length_subarray largest_subarray maximum_product_pair merge_arrays merge_arrays_two
    dutch_national_flag max_continuous_sequence maximum_continuous_sequence_two equilibrium_index largest_consecutive_subarray majority_element
    move_zeroes_to_end replace_array_elements longest_bitonic_subarray maximum_difference_pair maximum_sum_subarray maximum_sum_subarray_two
    maximum_sum_circular_subarray rearrange_array rearrange_array_two rearrange_array_three rearrange_array_four sorted_merge_arrays sorted_merge_arrays_two
    search_sorted_array unbounded_search_sorted_array rotation_count search_circular_array first_and_last_occurrence count_occurrences smallest_missing_number
    smallest_missing_number_two floor_and_ceil search_nearly_sorted_array count_ones peak_element k_closest_elements)

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
