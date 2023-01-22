/**
 * @file max_continuous_sequencetests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief
 * @version 0.1
 * @date 2023-01-21
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include <iostream>

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "max_continuous_sequence.h"

using namespace valhalla::arrays::maximum_continuous_sequence;

// Test Fixture Data Class
class MaximumContinuousSequenceData {
    int m_expected;
    std::vector<int> m_nums;
public:
    MaximumContinuousSequenceData() = default;
    MaximumContinuousSequenceData(int expected, std::vector<int> nums) : m_expected(expected), m_nums(nums) {}

    int get_expected() { return m_expected; }
    std::vector<int> get_input() { return m_nums; }

    std::ostream& operator<<(std::ostream& out) {
        out << "MaximumContinuousSequenceData [ expected=" << m_expected << ", input= [";

        for(int value : m_nums) {
            out << " " << value;
        }

        out << " ] ]";

        return out;
    }

    friend std::ostream& operator<<(std::ostream&, const MaximumContinuousSequenceData&);
};

std::ostream& operator<<(std::ostream& out, const MaximumContinuousSequenceData &data) {
    out << "MaximumContinuousSequenceData [ expected=" << data.m_expected << ", input=[";
    for(int value : data.m_nums) {
        out << " " << value;
    }
    out << " ] ]";

    return out;
}

// Test Fixture Class
class MaximumContinuousSequenceFixture :
    public testing::TestWithParam<MaximumContinuousSequenceData> {
};

TEST_P(MaximumContinuousSequenceFixture, MaximumContinuousSequenceTests) {
    MaximumContinuousSequenceData data = GetParam();

    Solution solution;

    int actual = solution.findIndexOfZero(data.get_input());

    ASSERT_EQ(data.get_expected(), actual);
}

INSTANTIATE_TEST_SUITE_P(MaximumContinuousSequenceTests, MaximumContinuousSequenceFixture, testing::Values(
    MaximumContinuousSequenceData(-1, {}),
    MaximumContinuousSequenceData(-1, {1, 1}),
    MaximumContinuousSequenceData(0, {0, 1, 1, 0, 0}),
    MaximumContinuousSequenceData(7, {0, 0, 1, 0, 1, 1, 1, 0, 1, 1})
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
