/**
 * @file maximum_sum_circular_subarraytests.cpp
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

#include "maximum_sum_circular_subarray.h"

using namespace valhalla::arrays::maximum_sum_circular_subarray;

// Test Fixture Data Class
class MaximumSumCircularSubarrayData {
    std::vector<int> m_input;
    int m_expected;
public:
     MaximumSumCircularSubarrayData() = default;
     MaximumSumCircularSubarrayData(std::vector<int> input, int expected) : m_input(input), m_expected(expected) {}

     std::vector<int> get_input() { return m_input; }
     int get_expected() { return m_expected; }

     friend std::ostream& operator<<(std::ostream&, const MaximumSumCircularSubarrayData &);
};

std::ostream& operator<<(std::ostream& out, const MaximumSumCircularSubarrayData &data) {
    out << "MaximumSumCircularSubarrayData [ input=[";
    for (int value : data.m_input)
        out << " " << value;
    out << " ], expected=" << data.m_expected << " ]";

    return out;
}

// Test Fixture Class
class MaximumSumCircularSubarrayFixture :
    public testing::TestWithParam<MaximumSumCircularSubarrayData> {
};

// Parameterized Test Definition
TEST_P(MaximumSumCircularSubarrayFixture, MaximumSumCircularSubarrayTests) {
    MaximumSumCircularSubarrayData data = GetParam();

    Solution solution;

    int actual = solution.findMaxSubarray(data.get_input());

    ASSERT_EQ(actual, data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(MaximumSumCircularSubarrayTests, MaximumSumCircularSubarrayFixture, testing::Values(
    MaximumSumCircularSubarrayData({2, 1, -5, 4, -3, 1, -3, 4, -1}, 6),
    MaximumSumCircularSubarrayData({8, -7, -3, 5, 6, -2, 3, -4, 2}, 18),
    MaximumSumCircularSubarrayData({-3, 1, -3, 4, -1, 2, 1, -5, 4}, 6)
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
