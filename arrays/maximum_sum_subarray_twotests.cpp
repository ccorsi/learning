/**
 * @file maximum_sum_subarray_twotests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief
 * @version 0.1
 * @date 2023-02-05
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include <iostream>

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "maximum_sum_subarray_two.h"

using namespace valhalla::arrays::maximum_sum_subarray_two;
using testing::AnyOfArray;

// Test Fixture Data Class
class MaximumSumSubarrayTwoData {
    std::vector<int> m_input;
    std::vector<std::vector<int>> m_expected;
public:
     MaximumSumSubarrayTwoData() = default;
     MaximumSumSubarrayTwoData(std::vector<int> input, std::vector<std::vector<int>> expected) : m_input(input), m_expected(expected) {}

     std::vector<int> const get_input() { return m_input; }
     std::vector<std::vector<int>> const get_expected() { return m_expected; }

     friend std::ostream& operator<<(std::ostream&, const MaximumSumSubarrayTwoData &);
};

std::ostream& operator<<(std::ostream& out, const MaximumSumSubarrayTwoData &data) {
    out << "MaximumSumSubarrayTwoData [ input=[";
    for (int value : data.m_input)
        out << " " << value;
    out << " ], expected=[";
    for (std::vector<int> values : data.m_expected) {
        out << " [";
        for (int value : values)
            out << " " << value;
        out << " ]";
    } // for
    out << " ] ]";

    return out;
}


// Test Fixture Class
class MaximumSumSubarrayTwoFixture :
    public testing::TestWithParam<MaximumSumSubarrayTwoData> {
};

// Parameterized Test Definition
TEST_P(MaximumSumSubarrayTwoFixture, MaximumSumSubarrayTwoTests) {
    MaximumSumSubarrayTwoData data = GetParam();

    Solution solution;

    std::vector<int> input = data.get_input();

    std::vector<int> actual = solution.findMaxSumSubarray(input);

    std::vector<std::vector<int>> const expected = data.get_expected();

    ASSERT_THAT(actual, AnyOfArray(expected.begin(), expected.end()));
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(MaximumSumSubarrayTwoTests, MaximumSumSubarrayTwoFixture, testing::Values(
    MaximumSumSubarrayTwoData({-2, 1, -3, 4, -1, 2, 1, -5, 4}, {{4, -1, 2, 1}}),
    MaximumSumSubarrayTwoData({-7, -3, -2, -4}, {{-2}}),
    MaximumSumSubarrayTwoData({-2, 2, -1, 2, 1, 6, -10, 6, 4, -8}, {{2, -1, 2, 1, 6}, {6, 4}, {2, -1, 2, 1, 6, -10, 6, 4}})
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
