/**
 * @file longest_palindromic_substringtests.cpp
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

#include "longest_palindromic_substring.h"

using namespace valhalla::strings::longest_palindromic_substring;
using ::testing::AnyOfArray;

// Test Fixture Data Class
class LongestPalindromicSubstringData {
    std::string m_input;
    std::vector<std::string> m_expected;

public:
     LongestPalindromicSubstringData() = default;
     LongestPalindromicSubstringData(std::string input, std::vector<std::string> expected) : m_input(input), m_expected(expected) {}

     std::string get_input() { return m_input; }
     std::vector<std::string> const & get_expected() { return m_expected; }

     friend std::ostream& operator<<(std::ostream&, const LongestPalindromicSubstringData &);
};

std::ostream& operator<<(std::ostream& out, const LongestPalindromicSubstringData &data) {
    out << "LongestPalindromicSubstringData [ input=\"";
    out << data.m_input << "\" expected=[";
    for (std::string s : data.m_expected)
        out << " \"" << s << "\"";
    out << " ] ]";

    return out;
}

// Test Fixture Class
class LongestPalindromicSubstringFixture :
    public testing::TestWithParam<LongestPalindromicSubstringData> {
};

// Parameterized Test Definition
TEST_P(LongestPalindromicSubstringFixture, LongestPalindromicSubstringTests) {
    LongestPalindromicSubstringData data = GetParam();

    Solution solution;

    std::string actual = solution.longestPalindromicSubstring(data.get_input());

    std::vector<std::string> const & expected = data.get_expected();

    ASSERT_THAT(actual, AnyOfArray(expected.begin(), expected.end()));
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(LongestPalindromicSubstringTests, LongestPalindromicSubstringFixture, testing::Values(
    LongestPalindromicSubstringData("bananas", {"anana"}),
    LongestPalindromicSubstringData("abdcbcdbdcbbc", {"bdcbcdb", "bcdbdcb"}),
    LongestPalindromicSubstringData("abracadabra", {"aca"}),
    LongestPalindromicSubstringData("dcabc", {"a", "b", "c", "d"})
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

