/**
 * @file maximum_continuous_sequence_twotests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief
 * @version 0.1
 * @date 2023-01-22
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include <iostream>

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "maximum_continuous_sequence_two.h"

using namespace valhalla::arrays::maximum_continuous_sequence_two;

// Test Fixture Data Class
class MaximumContinuousSequenceTwoData {
    std::pair<int,int> m_expected;
    std::vector<int>  m_input;
    int m_k;

public:
    MaximumContinuousSequenceTwoData() = default;
    MaximumContinuousSequenceTwoData(std::pair<int,int> expected, std::vector<int> input, int k) : m_expected(expected), m_input(input), m_k(k) {}

    std::pair<int,int> getExpected() { return m_expected; }
    std::vector<int> const & getInput() { return m_input; }
    int getK() { return m_k; }

    friend std::ostream& operator<<(std::ostream&, const MaximumContinuousSequenceTwoData &);
};

std::ostream& operator<<(std::ostream& out, const MaximumContinuousSequenceTwoData &value) {
    out << "MaximumContinuousSequenceTwoData [ expected=[";
    out << value.m_expected.first << "," << value.m_expected.second << "]";
    out << ", k=" << value.m_k << ", input=[";
    for(int v : value.m_input) {
        out << " " << v;
    }
    out << " ] ]";

    return out;
}

// Test Fixture Class
class MaximumContinuousSequenceTwoFixture :
    public testing::TestWithParam<MaximumContinuousSequenceTwoData> {
};

TEST_P(MaximumContinuousSequenceTwoFixture, MaximumContinuousSequenceTwoTests) {
    MaximumContinuousSequenceTwoData data = GetParam();

    Solution solution;

    std::pair<int,int> actual = solution.findLongestSequence(data.getInput(), data.getK());

    ASSERT_EQ(data.getExpected(), actual);
}

INSTANTIATE_TEST_SUITE_P(MaximumContinuousSequenceTwoTests, MaximumContinuousSequenceTwoFixture, testing::Values(
    MaximumContinuousSequenceTwoData({-1,-1}, {}, 0),
    MaximumContinuousSequenceTwoData({-1,-1}, {1}, 1),
    MaximumContinuousSequenceTwoData({0,0}, {0}, 1),
    MaximumContinuousSequenceTwoData({0, 4}, {1, 1, 1, 1, 1}, 1),
    MaximumContinuousSequenceTwoData({0, 3}, {1, 0, 1, 1, 0, 0, 1, 1, 0, 1}, 1),
    MaximumContinuousSequenceTwoData({3, 9}, {1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 0}, 1),
    MaximumContinuousSequenceTwoData({0, 9}, {1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 0}, 2),
    MaximumContinuousSequenceTwoData({0, 11}, {1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 0}, 5),
    MaximumContinuousSequenceTwoData({6, 9}, {1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 0}, 0)
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
