/**
 * @file sort_binary_array_inlinetests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief 
 * @version 0.1
 * @date 2022-12-29
 * 
 * @copyright Copyright (c) 2022 Claudio Corsi
 * 
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "sort_binary_array_inline.h"

using namespace valhalla::arrays::sort_binary_array_inline;

TEST(SortBinaryArrayInlineTestSuite, EmptyArray) {
    Solution solution;

    std::vector<int> values;
    std::vector<int> expected;

    solution.sort_array(values);

    ASSERT_EQ(values, expected) << "Nothing to sort";
}

TEST(SortBinaryArrayInlineTestSuite, SortedArray) {
    Solution solution;

    std::vector<int> values = { 0, 0, 1, 1 };
    std::vector<int> expected = { 0, 0, 1, 1 };

    solution.sort_array(values);

    ASSERT_EQ(values, expected) << "Nothing to sort";
}

TEST(SortBinaryArrayInlineTestSuite, UnSortedArrayAtEnd) {
    Solution solution;

    std::vector<int> values = { 1, 0, 1, 0 };
    std::vector<int> expected = { 0, 0, 1, 1 };

    solution.sort_array(values);

    ASSERT_EQ(values, expected) << "Array needed to be sorted";
}

TEST(SortBinaryArrayInlineTestSuite, UnSortedArrayRandom) {
    Solution solution;

    std::vector<int> values = { 1, 0, 1, 0, 1, 0, 0, 1 };
    std::vector<int> expected = { 0, 0, 0, 0, 1, 1, 1, 1 };

    solution.sort_array(values);

    ASSERT_EQ(values, expected) << "Array needed to be sorted";
}

TEST(SortBinaryArrayInlineTestSuite, SortedArrayAllZeros) {
    Solution solution;

    std::vector<int> values = { 0, 0 };
    std::vector<int> expected = { 0, 0 };

    solution.sort_array(values);

    ASSERT_EQ(values, expected) << "Nothing to sort";
}

TEST(SortBinaryArrayInlineTestSuite, SortedArrayAllOnes) {
    Solution solution;

    std::vector<int> values = { 1, 1 };
    std::vector<int> expected = { 1, 1 };

    solution.sort_array(values);

    ASSERT_EQ(values, expected) << "Nothing to sort";
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
