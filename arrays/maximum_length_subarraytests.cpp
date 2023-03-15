/**
 * @file maximum_length_subarraytests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains tests to the problem https://www.techiedelight.com/?problem=MaximumLengthSubarray
 * @version 0.1
 * @date 2022-12-29
 *
 * @copyright Copyright (c) 2022 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "maximum_length_subarray.h"

using namespace valhalla::arrays::maximum_length_subarray;

TEST(MaximumLengthSubarrayTestSuite, EmptyArray) {
    std::vector<int> values = {};
    std::vector<int> expected = {};
    int target = 10;

    Solution solution;

    std::vector<int> result = solution.find_maximum_subarray(values, target);

    ASSERT_EQ(expected, result) << "No subarray exists";
}

TEST(MaximumLengthSubarrayTestSuite, NonemptyArray) {
    std::vector<int> values = { 5, 6, -5, 5, 3, 5, 3, -2, 0 };
    std::vector<int> expected = { -5, 5, 3, 5 };
    int target = 8;

    Solution solution;

    std::vector<int> result = solution.find_maximum_subarray(values, target);

    ASSERT_EQ(expected, result) << "No subarray exists";
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
