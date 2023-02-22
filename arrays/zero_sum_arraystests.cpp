/**
 * @file zero_sum_arraystests.cpp
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
#include <set>

using namespace std;

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "zero_sum_arrays.h"

using namespace valhalla::arrays::zero_sum_arrays;

TEST(ZeroSumSubArrayTestSuite, NoZeroSumSubArrayFoundUsingEmptyList) {
    Solution solution;

    vector<int> values = {};

    set<vector<int>> expected;

    set<vector<int>> result = solution.find_zero_subarrays(values);

    ASSERT_EQ(0, result.size()) << "No sub-arrays exist";
}

TEST(ZeroSumSubArrayTestSuite, ZeroSumSubArrayFound) {
    Solution solution;

    vector<int> values = { 4, 2, -3, -1, 0, 4 };
    set<vector<int>> expected = { { -3, -1, 0, 4 }, { 0 } };

    set<vector<int>> results = solution.find_zero_subarrays(values);

    ASSERT_EQ(2, results.size()) << "Two zero sum sub-array exists";

    ASSERT_EQ(expected, results); // << "The zero sum sub-array are [ -3, -1, 0, 4 ] and [ 0 ]";
}

TEST(ZeroSumSubArrayTestSuite, ZeroSumSubArrayFoundUsingZeros) {
    Solution solution;

    vector<int> values = { 0, 0 };
    set<vector<int>> expected = { { 0, 0 }, { 0 } };

    set<vector<int>> results = solution.find_zero_subarrays(values);

    ASSERT_EQ(2, results.size()) << "Two zero sum sub-array exists";

    ASSERT_EQ(expected, results); // << "The zero sum sub-array are [ 0, 0 ] and [ 0 ]";
}

TEST(ZeroSumSubArrayTestSuite, ZeroSumSubArraySixFound) {
    Solution solution;

    vector<int> values = { 3, 4, -7, 3, 1, 3, 1, -4, -2, -2 };
    set<vector<int>> expected = { { 3, 4, -7 }, { 4, -7, 3 }, { -7, 3, 1, 3 }, { 3, 1, -4 }, { 3, 1, 3, 1, -4, -2, -2 }, { 3, 4, -7, 3, 1, 3, 1, -4, -2, -2 } };

    set<vector<int>> results = solution.find_zero_subarrays(values);

    ASSERT_EQ(expected.size(), results.size()) << expected.size() << " zero sum sub-array expected";

    ASSERT_EQ(expected, results); // << "The zero sum sub-array expected are " << expected;
}

TEST(ZeroSumSubArrayTestSuite, ZeroSumSubArrayWithZeroArrays) {
    Solution solution;

    vector<int> values = { 0, 1, 0, 0, -1, 0 };
    set<vector<int>> expected = { { 0 }, { 0, 0 }, { 0, 1, 0, 0, -1 }, { 1, 0, 0, -1 } };

    set<vector<int>> results = solution.find_zero_subarrays(values);

    ASSERT_EQ(expected.size(), results.size()) << expected.size() << " zero sum sub-array expected";

    ASSERT_EQ(expected, results); // << "The zero sum sub-array expected are " << expected;
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
