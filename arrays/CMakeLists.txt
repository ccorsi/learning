# We are using the integrated version of GoogleTest with our builds and this is only supported in CMake 3.10.0 or greater
cmake_minimum_required(VERSION 3.10.0)
project(arrays VERSION 0.4.2)

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
    smallest_missing_number_two floor_and_ceil search_nearly_sorted_array count_ones peak_element k_closest_elements combinations combinations_two
    combinations_three combinations_four combinations_five subset_sum minimum_sum_subarray maximum_product_subarray k_sum_subarray k_sum_subarray_two
    smallest_subarray smallest_window_to_sort_array maximum_path_sum buy_n_sell_shares trapping_rain_water minimum_platforms decode_array
    sort_array_single_swap three_sum three_sum_two three_sum_three longest_continuous_sequence reverse_consecutive_elements maximum_product_subset two_diff
    four_sum arithmetic_triplets geometric_triplets buy_and_sell_stock buy_and_sell_stock_two buy_and_sell_stock_three group_elements
    minimum_absolute_difference minimum_absolute_difference_two symmetric_pairs closest_pair partition_array_equal_sum distinct_elements_count
    maximum_sum_number largest_distinct_subarrays maximum_product_triplet repeating_element_index minimum_absolute_sum_pair consecutive_numbers
    non_overlapping_pairs add_arrays minimum_product_triplet distinct_absolute_count break_point_index frequency_map frequency_map_two sorted_triplet
    shuffle_array shuffle_array_two shuffle_array_three strictly_increasing_subarrays duplicates_in_range_k minimum_range minimum_range_two
    longest_consecutive_subsequence determine_index minimum_moves_to_convert_array left_rotate_array right_rotate_array activity_selection_problem
    k_divisible_pairs minimum_removals two_sum_two greater_elements sort_array counting_sort inversion_count inversion_count_two sort_by_frequency_and_index
    sort_with_duplicates largest_number surpasser_count three_partition_problem three_partition_problem_two k_partition_problem minimum_merge_operations
    coin_change_problem coin_change_problem_two next_greater_element next_greater_element_two previous_smaller_element longest_increasing_subsequence
    longest_increasing_subsequence_two merging_overlapping_intervals maximum_overlapping_intervals)

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
