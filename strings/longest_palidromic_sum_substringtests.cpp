/**
 * @file longest_palidromic_sum_substringtests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains tests to the problem https://www.techiedelight.com/?problem=LongestPalidromicSumSubstring
 * @version 0.1
 * @date 2023-06-23
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include <iostream>

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "paths.h"
#include "loaders.h"
#include "longest_palidromic_sum_substring.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::utils;
using namespace valhalla::strings::longest_palidromic_sum_substring;

// Test Fixture Data Class
class LongestPalidromicSumSubstringData {
    std::string m_s;
    int m_expected;
public:
    LongestPalidromicSumSubstringData() = default;

    std::string const & get_s() { return m_s; }
    int get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const LongestPalidromicSumSubstringData &);
    friend std::istream& operator>>(std::istream&, LongestPalidromicSumSubstringData &);

};

std::ostream& operator<<(std::ostream& out, const LongestPalidromicSumSubstringData & data) {
    return out << "LongestPalidromicSumSubstringData [ s=\"" << data.m_s << "\" expected="
        << data.m_expected << " ]";
}

std::istream& operator>>(std::istream& in, LongestPalidromicSumSubstringData &data) {
    ::loaders::loader::v4::dataLoader<
        std::string,
        char,
        loader::v4::reader<std::string,char>,
        1,
        ::checkers::is_character_noop<char>,
        ::checkers::is_no_character<char>,
        ::checkers::is_space_or<','>
    > sLoader(data.m_s);
    in >> sLoader;

    ::loaders::loader::v4::dataLoader<
        int,
        char,
        loader::v4::reader<int,char>,
        1,
        ::checkers::is_character_noop<char>,
        ::checkers::is_no_character<char>,
        ::checkers::is_space_or<','>
    > expectedLoader(data.m_expected);
    in >> expectedLoader;

    return in;
}

// Test Fixture Class
class LongestPalidromicSumSubstringFixture :
    public testing::TestWithParam<LongestPalidromicSumSubstringData> {
};

// Parameterized Test Definition
TEST_P(LongestPalidromicSumSubstringFixture, LongestPalidromicSumSubstringTests) {
    LongestPalidromicSumSubstringData data = GetParam();

    Solution solution;

    int actual = solution.findLongestPalindrome(data.get_s());

    ASSERT_EQ(actual, data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(LongestPalidromicSumSubstringTests, LongestPalidromicSumSubstringFixture, testing::ValuesIn(
    Loader<LongestPalidromicSumSubstringData>()(find_path("strings/data/longest_palidromic_sum_substring.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
