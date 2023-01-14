/**
 * @file shift_matrixtests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief 
 * @version 0.1
 * @date 2023-01-01
 * 
 * @copyright Copyright (c) 2023 Claudio Corsi
 * 
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "shift_matrix.h"

using namespace valhalla::matrices::shift_matrix;

TEST(ShiftMatrixTestSuite, EmptyMatrix) {
    Solution solution;

    std::vector<std::vector<int>> matrix;
    std::vector<std::vector<int>> expected;

    solution.shift_matrix(matrix);

    ASSERT_EQ(expected, matrix) << "empty matrix required no changes";
}

TEST(ShiftMatrixTestSuite, SingleEntryMatrix) {
    Solution solution;

    std::vector<std::vector<int>> matrix = { { 1 } };
    std::vector<std::vector<int>> expected = { { 1 } };

    solution.shift_matrix(matrix);

    ASSERT_EQ(expected, matrix) << "single entry matrix required no changes";
}

TEST(ShiftMatrixTestSuite, TwoByTwoMatrix) {
    Solution solution;

    std::vector<std::vector<int>> matrix = {
        { 1, 2 },
        { 4, 3 }
    };
    std::vector<std::vector<int>> expected = {
        { 4, 1 },
        { 3, 2 }
    };

    solution.shift_matrix(matrix);

    ASSERT_EQ(expected, matrix) << "2x2 matrix required was not shifted";
}

TEST(ShiftMatrixTestSuite, ThreeByThreeMatrix) {
    Solution solution;

    std::vector<std::vector<int>> matrix = {
        { 1, 2, 3 },
        { 8, 9, 4 },
        { 7, 6, 5 }
    };
    std::vector<std::vector<int>> expected = {
        { 9, 1, 2 },
        { 7, 8, 3 },
        { 6, 5, 4 }
    };

    solution.shift_matrix(matrix);

    ASSERT_EQ(expected, matrix) << "3x3 matrix required was not shifted";
}

TEST(ShiftMatrixTestSuite, FourByFourMatrix) {
    Solution solution;

    std::vector<std::vector<int>> matrix = {
        {  1,  2,  3, 4 },
        { 12, 13, 14, 5 },
        { 11, 16, 15, 6 },
        { 10,  9,  8, 7 }
    };
    std::vector<std::vector<int>> expected = {
        { 16,  1,  2, 3 },
        { 11, 12, 13, 4 },
        { 10, 15, 14, 5 },
        {  9,  8,  7, 6}
    };

    solution.shift_matrix(matrix);

    ASSERT_EQ(expected, matrix) << "4x4 matrix required was not shifted";
}

TEST(ShiftMatrixTestSuite, FiveByFiveMatrix) {
    Solution solution;

    std::vector<std::vector<int>> matrix = {
        {  1,  2,  3,  4,  5 },
        { 16, 17, 18, 19,  6 },
        { 15, 24, 25, 20,  7 },
        { 14, 23, 22, 21,  8 },
        { 13, 12, 11, 10,  9 }
    };
    std::vector<std::vector<int>> expected = {
        { 25,  1,  2,  3,  4 },
        { 15, 16, 17, 18,  5 },
        { 14, 23, 24, 19,  6 },
        { 13, 22, 21, 20,  7 },
        { 12, 11, 10,  9,  8 }
    };

    solution.shift_matrix(matrix);

    ASSERT_EQ(expected, matrix) << "5x5 matrix required was not shifted";
}

TEST(ShiftMatrixTestSuite, ThreeByFiveMatrix) {
    Solution solution;

    std::vector<std::vector<int>> matrix = {
        {  1,  2,  3,  4,  5 },
        { 12, 13, 14, 15,  6 },
        { 11, 10,  9,  8,  7 }
    };
    std::vector<std::vector<int>> expected = {
        { 15,  1,  2,  3,  4 },
        { 11, 12, 13, 14,  5 },
        { 10,  9,  8,  7,  6 }
    };

    solution.shift_matrix(matrix);

    ASSERT_EQ(expected, matrix) << "3x5 matrix required was not shifted";
}

TEST(ShiftMatrixTestSuite, FiveByThreeMatrix) {
    Solution solution;

    std::vector<std::vector<int>> matrix = {
        {  1,  2,  3 },
        { 12, 13,  4 },
        { 11, 14,  5 },
        { 10, 15,  6 },
        {  9,  8,  7 }
    };
    std::vector<std::vector<int>> expected = {
        { 15,  1,  2 },
        { 11, 12,  3 },
        { 10, 13,  4 },
        {  9, 14,  5 },
        {  8,  7,  6 }
    };

    solution.shift_matrix(matrix);

    ASSERT_EQ(expected, matrix) << "5x3 matrix required was not shifted";
}

TEST(ShiftMatrixTestSuite, FourByFiveMatrix) {
    Solution solution;

    std::vector<std::vector<int>> matrix = {
        {  1,  2,  3,  4,  5 },
        { 14, 15, 16, 17,  6 },
        { 13, 20, 19, 18,  7 },
        { 12, 11, 10,  9,  8 }
    };
    std::vector<std::vector<int>> expected = {
        { 20,  1,  2,  3,  4 },
        { 13, 14, 15, 16,  5 },
        { 12, 19, 18, 17,  6 },
        { 11, 10,  9,  8,  7 }
    };

    solution.shift_matrix(matrix);

    ASSERT_EQ(expected, matrix) << "3x3 matrix required was not shifted";
}

TEST(ShiftMatrixTestSuite, FiveByFourMatrix) {
    Solution solution;

    std::vector<std::vector<int>> matrix = {
        {  1,  2,  3,  4 },
        { 14, 15, 16,  5 },
        { 13, 20, 17,  6 },
        { 12, 19, 18,  7 },
        { 11, 10,  9,  8 }
    };
    std::vector<std::vector<int>> expected = {
        { 20,  1,  2,  3 },
        { 13, 14, 15,  4 },
        { 12, 19, 16,  5 },
        { 11, 18, 17,  6 },
        { 10,  9,  8,  7 }
    };

    solution.shift_matrix(matrix);

    ASSERT_EQ(expected, matrix) << "3x3 matrix required was not shifted";
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
