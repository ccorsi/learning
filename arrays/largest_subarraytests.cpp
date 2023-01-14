/**
 * @file largest_subarraytests.cpp
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

#include "largest_subarray.h"

using namespace valhalla::arrays::largest_subarray;

TEST(LargestSubarrayTestSuite, NoneExist) {
    Solution solution;

    std::vector<int> values = { 0, 0, 0, 0 };
    std::vector<int> expected = {};

    std::vector<int> actual = solution.find(values);

    ASSERT_EQ(expected, actual) << "An empty should of been returned";
}

TEST(LargestSubarrayTestSuite, EmptyArray) {
    Solution solution;

    std::vector<int> values = {};
    std::vector<int> expected = {};

    std::vector<int> actual = solution.find(values);

    ASSERT_EQ(expected, actual) << "An empty should of been returned";
}

#include <set>

#include <iostream>

std::ostream& operator<<(std::ostream& out, const std::vector<int> &value) {
    out << "[";

    for(int v : value) {
        out << " " << v;
    }

    if (value.empty()) {
        out << "]";
    } else {
        out << " ]";
    }

    return out;
}

TEST(LargestSubarrayTestSuite, LargestHasFour) {
    Solution solution;

    std::vector<int> values = { 0, 0, 1, 0, 1, 0, 0 };
    std::set<std::vector<int>> set = { { 0, 1, 0, 1 }, { 1, 0, 1, 0 } }; 
    std::vector<int> expected = { 0, 1, 0, 1 };

    std::vector<int> actual = solution.find(values);

    std::cout << "Result: " << actual << std::endl;

    ASSERT_EQ(expected.size(), actual.size()) << "Largest has 4 elements";
    ASSERT_TRUE(set.find(actual) != set.end()) << "Returned vector is not one of the expected solutions";
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
