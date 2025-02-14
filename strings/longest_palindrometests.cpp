/**
 * @file longest_palindrometests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This file contains the tests for the problem https://www.techiedelight.com/?problem=LongestPalindrome
 * @version 0.1
 * @date 2025-02-07
 *
 * @copyright Copyright (c) 2025 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include <iostream>

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "paths.h"
#include "loaders.h"
#include "readers.h"
#include "longest_palindrome.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::utils::readers;
using namespace valhalla::utils;
using namespace valhalla::strings::longest_palindrome;

// Test Fixture Data Class
class LongestPalindromeData {
    std::string m_input;
    int m_expected;
public:
    LongestPalindromeData() = default;

    std::string const & get_input() { return m_input; }
    int get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const LongestPalindromeData &);
    friend std::istream& operator>>(std::istream&, LongestPalindromeData &);

};

std::ostream& operator<<(std::ostream& out, const LongestPalindromeData & data) {
    out << "LongestPalindromeData [ input=\"" << data.m_input << "\", expected=";
    out << data.m_expected << " ]";

    return out;
}

std::istream& operator>>(std::istream& in, LongestPalindromeData &data) {

    ::loaders::loader::v6::dataLoader<
        std::string,
        char,
        StringReader,
        1,
        ::checkers::is_character<char, '"'>,
        ::checkers::is_character<char, '"'>,
        ::checkers::is_space_or<','>,
        ::checkers::is_space_or<','>
    > InputLoader(data.m_input);
    in >> InputLoader;

    ::loaders::loader::v6::dataLoader<int,char> ExpectedLoader(data.m_expected);
    in >> ExpectedLoader;

    return in;
}

// Test Fixture Class
class LongestPalindromeFixture :
    public testing::TestWithParam<LongestPalindromeData> {
};

// Parameterized Test Definition
TEST_P(LongestPalindromeFixture, LongestPalindromeTests) {
    LongestPalindromeData data = GetParam();

    Solution solution;

    int longest = solution.findLongestPalindrome(data.get_input());

    ASSERT_EQ(data.get_expected(), longest);
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(LongestPalindromeTests, LongestPalindromeFixture, testing::ValuesIn(
    Loader<LongestPalindromeData>()(find_path("strings/data/longest_palindrome.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
