# We are using the integrated version of GoogleTest with our builds and this is only supported in CMake 3.10.0 or greater
cmake_minimum_required(VERSION 3.10.0)
project(strings VERSION 0.2.8)

# setup the minimum C++ requirements
set(CXX_STANDARD 17)
set(CXX_STANDARD_REQUIRED true)

# add the general utilities include directory
include_directories(../utils/includes includes)

# Include GoogleTest for testing the different implementations
include(GoogleTest)

enable_testing()

set(NAMES derive_string rotated_palindrome longest_palindromic_substring repeated_subsequence excel_sheet_column_name check_anagram
    interleaving_string interleaving_string_two isomorphic_strings longest_common_prefix combinations_six combinations_seven combinations_eight
    combinations_nine unattended_customers_count minimum_number_k_swaps check_circular_moves palindromic_substrings group_anagrams
    transform_string transform_string_two transform_string_three balanced_expression longest_palidromic_sum_substring print_string_zig_zag
    run_length_encoding longest_distinct_substring longest_distinct_substring_two palindromic_permutations anagram_substring
    maximum_occurring_word permutations permutations_two next_permutations lexical_minimal_string_rotation balanced_parentheses
    duplicate_parenthesis evaluate_postfix_expression infix_to_postfix palindrome_string minimum_inversions remove_adjacent_duplicates
    remove_adjacent_duplicates_two first_non_repeating_character lexicographic_permutations lexicographic_rank decode_sequence
    k_distinct_substrings pattern_match pattern_match_two)

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
