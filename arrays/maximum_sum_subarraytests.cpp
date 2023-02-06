/**
 * @file maximum_sum_subarraytests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief
 * @version 0.1
 * @date 2023-02-04
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include <iostream>

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "maximum_sum_subarray.h"

using namespace valhalla::arrays::maximum_sum_subarray;

// Test Fixture Data Class
class MaximumSumSubarrayData {
    std::vector<int> m_input;
    int m_expected;
public:
     MaximumSumSubarrayData() = default;
     MaximumSumSubarrayData(std::vector<int> input, int expected) : m_input(input), m_expected(expected) {}

     std::vector<int> get_input() { return m_input; }
     int get_expected() { return m_expected; }

     friend std::ostream& operator<<(std::ostream &, const MaximumSumSubarrayData &);
};

std::ostream& operator<<(std::ostream& out, const MaximumSumSubarrayData &data) {
    out << "MaximumSumSubarrayData [ input=[";
    for (int value : data.m_input)
        out << " " << value;
    out << " ], expected=" << data.m_expected << " ]";

    return out;
}

// Test Fixture Class
class MaximumSumSubarrayFixture :
    public testing::TestWithParam<MaximumSumSubarrayData> {
};

// Parameterized Test Definition
TEST_P(MaximumSumSubarrayFixture, MaximumSumSubarrayTests) {
    MaximumSumSubarrayData data = GetParam();

    Solution solution;

    std::vector<int> input = data.get_input();

    int actual = solution.findMaxSubarraySum(input);

    ASSERT_EQ(data.get_expected(), actual);
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(MaximumSumSubarrayTests, MaximumSumSubarrayFixture, testing::Values(
    MaximumSumSubarrayData({-2, 1, -3, 4, -1, 2, 1, -5, 4}, 6),
    MaximumSumSubarrayData({-7, -3, -2, -4}, -2),
    MaximumSumSubarrayData({-2, 2, -1, 2, 1, 6, -10, 6, 4, -8}, 10)
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
