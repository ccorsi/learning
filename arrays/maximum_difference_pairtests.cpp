/**
 * @file maximum_difference_pairtests.cpp
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

#include "maximum_difference_pair.h"

using namespace valhalla::arrays::maximum_difference_pair;

// Test Fixture Data Class
class MaximumDifferencePairData {
    std::vector<int> m_input;
    int m_expected;
public:
     MaximumDifferencePairData() = default;
     MaximumDifferencePairData(std::vector<int> input, int expected) : m_input(input), m_expected(expected) {}

     std::vector<int> const & get_input() { return m_input; }
     int get_expected() { return m_expected; }

     friend std::ostream& operator<<(std::ostream&, const MaximumDifferencePairData &);
};

std::ostream& operator<<(std::ostream& out, const MaximumDifferencePairData &value) {
    out << "MaximumDifferencePairData [ input=[";
    for( int v : value.m_input)
        out << " " << v;
    out << " ], expected=" << value.m_expected << " ]";

    return out;
}

// Test Fixture Class
class MaximumDifferencePairFixture :
    public testing::TestWithParam<MaximumDifferencePairData> {
};

// Parameterized Test Definition
TEST_P(MaximumDifferencePairFixture, MaximumDifferencePairTests) {
    MaximumDifferencePairData data = GetParam();

    Solution solution;

    std::vector<int> input = data.get_input();

    int actual = solution.findMaxDiff(input);

    ASSERT_EQ(data.get_expected(), actual);
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(MaximumDifferencePairTests, MaximumDifferencePairFixture, testing::Values(
    MaximumDifferencePairData({2, 7, 9, 5, 1, 3, 5}, 7),
    MaximumDifferencePairData({5, 4, 3, 2, 1}, -1)
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
