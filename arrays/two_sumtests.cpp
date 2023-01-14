/**
 * @file two_sumtests.cpp
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

#include "two_sum.h"

using namespace valhalla::arrays::two_sum;

#include "gtest/gtest.h"
#include "gmock/gmock.h"

TEST(TwoSumTestSuite, EmptyValues) {
    vector<int> values = { };

    Solution solution;

    pair<int,int> result = solution.find_pair(values, 10);

    ASSERT_EQ(-1, result.first) << "First entry should be -1";
    ASSERT_EQ(-1, result.second) << "Second entry should be -1";
}

TEST(TwoSumTestSuite, TargetNotFound) {
    vector<int> values = { 5, 2, 6, 8, 1, 9 };

    Solution solution;

    pair<int,int> result = solution.find_pair(values, 12);

    ASSERT_EQ(-1, result.first) << "First entry should be -1";
    ASSERT_EQ(-1, result.second) << "Second entry should be -1";
}

TEST(TwoSumTestSuite, TargetFound) {
    vector<int> values = { 8, 7, 2, 5, 3, 1 };

    Solution solution;

    pair<int,int> result = solution.find_pair(values, 10);

    const pair<int,int> expected(8, 2);

    ASSERT_EQ(expected, result) << "The pair (8,2) should of returned";
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
