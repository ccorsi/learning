/**
 * @file wildcard_pattern_matching_twotests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This file contains the solution to the problem https://www.techiedelight.com/?problem=WildcardPatternMatchingII
 * @version 0.1
 * @date 2025-02-04
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
#include "wildcard_pattern_matching_two.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::utils;
using namespace valhalla::dynamic_programming::wildcard_pattern_matching_two;

// Test Fixture Data Class
class WildcardPatternMatchingTwoData {
    std::string m_word;
    std::string m_pattern;
    bool m_is_match;
public:
    WildcardPatternMatchingTwoData() = default;

    std::string get_word() { return m_word; }
    std::string get_pattern() { return m_pattern; }
    bool get_expected() { return m_is_match; }

    friend std::ostream& operator<<(std::ostream&, const WildcardPatternMatchingTwoData &);
    friend std::istream& operator>>(std::istream&, WildcardPatternMatchingTwoData &);

};

std::ostream& operator<<(std::ostream& out, const WildcardPatternMatchingTwoData & data) {
    out << "WildcardPatternMatchingTwoData [ word=\"" << data.m_word << "\", pattern=\"";
    out << data.m_pattern << "\", expected=" << (data.m_is_match ? "true" : "false");
    out << " ]";

    return out;
}

std::istream& operator>>(std::istream& in, WildcardPatternMatchingTwoData &data) {
    ::loaders::loader::v6::dataLoader<
        std::string,
        char,
        ::readers::StringReader,
        1,
        ::checkers::is_character<char, '"'>,
        ::checkers::is_character<char, '"'>,
        ::checkers::is_space_or<','>,
        ::checkers::is_space_noop<char>
    > WordLoader(data.m_word);
    in >> WordLoader;

    ::loaders::loader::v6::dataLoader<
        std::string,
        char,
        ::readers::StringReader,
        1,
        ::checkers::is_character<char, '"'>,
        ::checkers::is_character<char, '"'>,
        ::checkers::is_space_or<','>,
        ::checkers::is_space_noop<char>
    > PatternLoader(data.m_pattern);
    in >> PatternLoader;

    ::loaders::loader::v6::dataLoader<bool,char> ExpectedLoader(data.m_is_match);
    in >> ExpectedLoader;

    return in;
}

// Test Fixture Class
class WildcardPatternMatchingTwoFixture :
    public testing::TestWithParam<WildcardPatternMatchingTwoData> {
};

// Parameterized Test Definition
TEST_P(WildcardPatternMatchingTwoFixture, WildcardPatternMatchingTwoTests) {
    WildcardPatternMatchingTwoData data = GetParam();

    Solution solution;

    bool isMatch = solution.isMatch(data.get_word(), data.get_pattern());

    ASSERT_EQ(data.get_expected(), isMatch);
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(WildcardPatternMatchingTwoTests, WildcardPatternMatchingTwoFixture, testing::ValuesIn(
    Loader<WildcardPatternMatchingTwoData>()(find_path("dynamic_programming/data/wildcard_pattern_matching_two.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
