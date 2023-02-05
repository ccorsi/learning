/**
 * @file largest_consecutive_subarraytests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief
 * @version 0.1
 * @date 2023-01-25
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include <iostream>

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "largest_consecutive_subarray.h"
#include "contains_one_of.h"

using namespace valhalla::arrays::largest_consecutive_subarray;
using namespace valhalla::utils::testing;

using ::testing::AnyOfArray;

// Test Fixture Data Class
class LargestConsecutiveSubarrayData {
    std::vector<int> m_input;
    std::vector<std::vector<int>> m_expected;
public:
    LargestConsecutiveSubarrayData() = default;
    LargestConsecutiveSubarrayData(std::vector<int> input, std::vector<std::vector<int>> expected) : m_input(input), m_expected(expected) {}

    std::vector<int>& get_input() { return m_input; }
    std::vector<std::vector<int>>& get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const LargestConsecutiveSubarrayData &);
};

std::ostream& operator<<(std::ostream& out, const LargestConsecutiveSubarrayData &value) {
    out << "LargestConsecutiveSubarrayData [ input=[";
    for(int v : value.m_input)
        out << " " << v;
    out << " ], expected=[";
    for(std::vector<int> values : value.m_expected) {
        out << " [";
        for(int v : values)
            out << " " << v;
        out << " ]";
    }
    out << " ] ]";

    return out;
}

// Test Fixture Class
class LargestConsecutiveSubarrayFixture :
    public testing::TestWithParam<LargestConsecutiveSubarrayData> {
};

TEST_P(LargestConsecutiveSubarrayFixture, LargestConsecutiveSubArrayTests) {
    LargestConsecutiveSubarrayData data = GetParam();

    Solution solution;

    std::vector<int> actual = solution.findLargestSubarray(data.get_input());

    std::vector<std::vector<int>> expected(data.get_expected());

    ASSERT_TRUE(ContainsOneOf<int>(data.get_expected())(actual));
    // ASSERT_EQ(actual, AnyOfArray(expected.begin(), expected.end()));
}

INSTANTIATE_TEST_SUITE_P(LargestConsecutiveSubArrayTests, LargestConsecutiveSubarrayFixture, testing::Values(
    LargestConsecutiveSubarrayData({}, {{}}),
    LargestConsecutiveSubarrayData({2, 0, 2, 1, 4, 3, 1, 0}, {{0, 2, 1, 4, 3}}),
    LargestConsecutiveSubarrayData({-5, -1, 0, 2, 1, 6, 5, 8, 7}, {{-1, 0, 2, 1}, {6, 5, 8, 7}}),
    LargestConsecutiveSubarrayData({1, 2, 3, 4, 5}, {{1, 2, 3, 4, 5}}),
    LargestConsecutiveSubarrayData({2, -3, -4, -2, 7, 1}, {{-3, -4, -2}})
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
