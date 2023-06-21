# We are using the integrated version of GoogleTest with our builds and this is only supported in CMake 3.10.0 or greater
cmake_minimum_required(VERSION 3.10.0)
project(matrices VERSION 0.2.8)

# setup the minimum C++ requirements
set(CXX_STANDARD 17)
set(CXX_STANDARD_REQUIRED true)

# add the general utilities include directory
include_directories(../utils/includes includes)

# Include GoogleTest for testing the different implementations
include(GoogleTest)

enable_testing()

set(NAMES shift_matrix rotate_matrix rotate_matrix_two spiral_matrix spiral_matrix_two spiral_matrix_three convert_matrix
        convert_matrix_two diagonal_matrix_traversal replace_matrix replace_matrix_two negative_numbers_count toeplitz_matrix
        fill_matrix common_elements maximum_ones_row n_queen_problem knight_tour_problem chess_knight_problem shortest_path
        longest_path search_matrix search_matrix_two largest_square_submatrix largest_square_submatrix_two
        largest_rectangle_area maximum_difference_pair_two shortest_path_two shortest_path_three matrix_path matrix_path_two
        matrix_path_three matrix_path_four matrix_path_five matrix_path_six matrix_path_seven minimum_cost_path
        minimum_cost_path_two longest_continuous_sequence_two longest_continuous_sequence_three collect_maximum_points
        tiles_problem largest_plus collect_coins duplicate_rows boggle_search submatrix_sum maximum_sub_submatrix
        maximum_sub_submatrix_two alive_probability maximum_length_snake_sequence flood_fill_algorithm count_islands
        construct_young_tableau extract_min_in_young_tableau)

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
