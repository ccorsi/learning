/**
 * @file repeated_subsequencetests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief
 * @version 0.1
 * @date 2023-02-13
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include <iostream>

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "repeated_subsequence.h"

using namespace valhalla::strings::repeated_subsequence;

// Test Fixture Data Class
class RepeatedSubsequenceData {
    std::string m_input;
    bool m_expected;

public:
    RepeatedSubsequenceData() = default;
    RepeatedSubsequenceData(std::string input, bool expected) : m_input(input), m_expected(expected) {}

    std::string const & get_input() { return m_input; }
    bool get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const RepeatedSubsequenceData&);
};

std::ostream& operator<<(std::ostream& out, const RepeatedSubsequenceData &data) {
    out << "RepeatedSubsequenceData [ input=\"" << data.m_input << "\" expected=" << data.m_expected << " ]";

    return out;
}

// Test Fixture Class
class RepeatedSubsequenceFixture :
    public testing::TestWithParam<RepeatedSubsequenceData> {
};

// Parameterized Test Definition
TEST_P(RepeatedSubsequenceFixture, RepeatedSubsequenceTests) {
    RepeatedSubsequenceData data = GetParam();

    Solution solution;

    bool actual = solution.hasRepeatedSubsequence(data.get_input());

    ASSERT_EQ(actual, data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(RepeatedSubsequenceTests, RepeatedSubsequenceFixture, testing::Values(
    RepeatedSubsequenceData("", false),
    RepeatedSubsequenceData("XYBAXB", true),
    RepeatedSubsequenceData("XBXAXB", true),
    RepeatedSubsequenceData("XYBYAXBY", true),
    RepeatedSubsequenceData("ABCA", false),
    RepeatedSubsequenceData("YYY", true)
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
