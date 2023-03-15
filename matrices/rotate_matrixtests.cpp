/**
 * @file rotate_matrixtests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains tests for the problem https://www.techiedelight.com/?problem=RotateMatrix
 * @version 0.1
 * @date 2023-01-02
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "rotate_matrix.h"

using namespace valhalla::matrices::rotate_matrix;

TEST(RotateMatrixTestSuite, EmptyMatrix) {
    Solution solution;

    std::vector<std::vector<int>> actual = {};
    std::vector<std::vector<int>> expected = {};

    solution.rotate(actual);

    ASSERT_EQ(expected, actual) << "empty matrix should not have any rotations";    
}

TEST(RotateMatrixTestSuite, SingleEntryMatrix) {
    Solution solution;

    std::vector<std::vector<int>> actual = { { 1 } };
    std::vector<std::vector<int>> expected = { { 1 } };

    solution.rotate(actual);

    ASSERT_EQ(expected, actual) << "single entry matrix should not have any rotations";    
}

TEST(RotateMatrixTestSuite, TwoByTwoMatrix) {
    Solution solution;

    std::vector<std::vector<int>> actual = {
        { 1, 2 },
        { 4, 3 }
    };
    std::vector<std::vector<int>> expected = {
        { 4, 1 },
        { 3, 2 }
    };

    solution.rotate(actual);

    ASSERT_EQ(expected, actual) << "two by two matrix should have been rotated";    
}

TEST(RotateMatrixTestSuite, ThreeByThreeMatrix) {
    Solution solution;

    std::vector<std::vector<int>> actual = {
        { 1, 2, 3 },
        { 4, 5, 6 },
        { 7, 8, 9 }
    };
    std::vector<std::vector<int>> expected = {
        { 7, 4, 1 },
        { 8, 5, 2 },
        { 9, 6, 3 }
    };

    solution.rotate(actual);

    ASSERT_EQ(expected, actual) << "three by three matrix should have been rotated";    
}

TEST(RotateMatrixTestSuite, FourByFourMatrix) {
    Solution solution;

    std::vector<std::vector<int>> actual = {
        {  1,  2,  3,  4 },
        {  5,  6,  7,  8 },
        {  9, 10, 11, 12 },
        { 13, 14, 15, 16 }
    };
    std::vector<std::vector<int>> expected = {
        { 13,  9,  5,  1 },
        { 14, 10,  6,  2 },
        { 15, 11,  7,  3 },
        { 16, 12,  8,  4 }
    };

    solution.rotate(actual);

    ASSERT_EQ(expected, actual) << "four by four matrix should have been rotated";    
}

TEST(RotateMatrixTestSuite, FiveByFiveMatrix) {
    Solution solution;

    std::vector<std::vector<int>> actual = {
        {  1,  2,  3,  4,  5 },
        {  6,  7,  8,  9, 10 },
        { 11, 12, 13, 14, 15 },
        { 16, 17, 18, 19, 20 },
        { 21, 22, 23, 24, 25 }
    };
    std::vector<std::vector<int>> expected = {
        { 21, 16, 11,  6,  1 },
        { 22, 17, 12,  7,  2 },
        { 23, 18, 13,  8,  3 },
        { 24, 19, 14,  9,  4 },
        { 25, 20, 15, 10,  5 }
    };

    solution.rotate(actual);

    ASSERT_EQ(expected, actual) << "five by five matrix should have been rotated";    
}

TEST(RotateMatrixTestSuite, SixByFSxMatrix) {
    Solution solution;

    std::vector<std::vector<int>> actual = {
        {  1,  2,  3,  4,  5,  6 },
        {  7,  8,  9, 10, 11, 12 },
        { 13, 14, 15, 16, 17, 18 },
        { 19, 20, 21, 22, 23, 24 },
        { 25, 26, 27, 28, 29, 30 },
        { 31, 32, 33, 34, 35, 36 }
    };
    std::vector<std::vector<int>> expected = {
        { 31, 25, 19, 13,  7,  1 },
        { 32, 26, 20, 14,  8,  2 },
        { 33, 27, 21, 15,  9,  3 },
        { 34, 28, 22, 16, 10,  4 },
        { 35, 29, 23, 17, 11,  5 },
        { 36, 30, 24, 18, 12,  6 }
    };

    solution.rotate(actual);

    ASSERT_EQ(expected, actual) << "six by six matrix should have been rotated";    
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}