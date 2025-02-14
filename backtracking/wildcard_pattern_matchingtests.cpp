/**
 * @file wildcard_pattern_matchingtests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief  This contains tests for the problem https://www.techiedelight.com/?problem=WildcardPatternMatching
 * @version 0.1
 * @date 2025-02-03
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
#include "wildcard_pattern_matching.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::utils;
using namespace valhalla::backtracking::wildcard_pattern_matching;

// Test Fixture Data Class
class WildcardPatternMatchingData {
    std::string m_pattern;
    std::unordered_set<std::string> m_matches;

public:
    WildcardPatternMatchingData() = default;

    const std::string& get_pattern() { return m_pattern; }
    const std::unordered_set<std::string>& get_expected() { return m_matches; }

    friend std::ostream& operator<<(std::ostream&, const WildcardPatternMatchingData &);
    friend std::istream& operator>>(std::istream&, WildcardPatternMatchingData &);

};

std::ostream& operator<<(std::ostream& out, const WildcardPatternMatchingData & data) {
    out << "WildcardPatternMatchingData [ pattern=\"" << data.m_pattern << "\", expected={";
    for (auto & match : data.m_matches) {
       out << " \"" << match << '"';
    }
    out << " } ]";

    return out;
}

struct StringReader {
    std::basic_istream<char> & operator()(std::basic_istream<char> & in, std::string & str, int state) {
        if (static_cast<char>(in.peek()) != '"') {
            str += static_cast<char>(in.get());
        }

        return in;
    }
};

struct UnorderedSetReader {
    std::basic_istream<char> & operator()(std::basic_istream<char> & in, std::unordered_set<std::string> & sset, int state) {
        std::string str;

        ::loaders::loader::v6::dataLoader<
            std::string,
            char,
            StringReader,
            1,
            ::checkers::is_character<char, '"'>,
            ::checkers::is_character<char, '"'>,
            ::checkers::is_space_or<','>,
            ::checkers::is_space_noop<char>
        > StringLoader(str);
        in >> StringLoader;

        sset.insert(str);

        return in;
    }
};

std::istream& operator>>(std::istream& in, WildcardPatternMatchingData &data) {
    ::loaders::loader::v6::dataLoader<
        std::string,
        char,
        StringReader,
        1,
        ::checkers::is_character<char, '"'>,
        ::checkers::is_character<char, '"'>,
        ::checkers::is_space_or<','>,
        ::checkers::is_space_noop<char>
    > PatternLoader(data.m_pattern);
    in >> PatternLoader;

    ::loaders::loader::v6::dataLoader<
        std::unordered_set<std::string>,
        char,
        UnorderedSetReader,
        1,
        ::checkers::is_character<char, '{'>,
        ::checkers::is_character<char, '}'>,
        ::checkers::is_space_or<','>,
        ::checkers::is_space_noop<char>
    > UnorderedSetLoader(data.m_matches);
    in >> UnorderedSetLoader;

    return in;
}

// Test Fixture Class
class WildcardPatternMatchingFixture :
    public testing::TestWithParam<WildcardPatternMatchingData> {
};

// Parameterized Test Definition
TEST_P(WildcardPatternMatchingFixture, WildcardPatternMatchingTests) {
    WildcardPatternMatchingData data = GetParam();

    Solution solution;

    std::unordered_set<std::string> result = solution.findCombinations(data.get_pattern());

    ASSERT_EQ(data.get_expected(), result);

    // ASSERT_TRUE(data.get_expected() == result);
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(WildcardPatternMatchingTests, WildcardPatternMatchingFixture, testing::ValuesIn(
    Loader<WildcardPatternMatchingData>()(find_path("backtracking/data/wildcard_pattern_matching.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
