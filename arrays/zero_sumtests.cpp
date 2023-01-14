/**
 * @file zero_sumtests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief 
 * @version 0.1
 * @date 2022-12-26
 * 
 * @copyright Copyright (c) 2022 Claudio Corsi
 * 
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include <vector>

using namespace std;

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "zero_sum.h"

using namespace valhalla::arrays::zero_sum;

TEST(ZeroSumTestSuite, ZeroSumFound) {
    Solution solution;

    vector<int> values = { };

    ASSERT_EQ(false, solution.has_zero_sum(values)) << "No zero sum sub-array exists";
}

TEST(ZeroSumTestSuite, ZeroArrayFound) {
    Solution solution;

    vector<int> values = { 0 };

    ASSERT_EQ(true, solution.has_zero_sum(values)) << "A zero sum sub-array exists";
}

TEST(ZeroSumTestSuite, ZeroSumArrayFound) {
    Solution solution;

    vector<int> values = { 3, 4, -7, 3, 1, 3, 1, -4, -2, -2 };

    ASSERT_EQ(true, solution.has_zero_sum(values)) << "A zero sum sub-array exists";
}

TEST(ZeroSumTestSuite, NoZeroSumArrayFound) {
    Solution solution;

    vector<int> values = { 4, -7, 1, -2, -1 };

    ASSERT_EQ(false, solution.has_zero_sum(values)) << "No zero sum sub-array exists";
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
