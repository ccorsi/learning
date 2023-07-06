/**
 * @file pattern_matchtests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains tests to the problem https://www.techiedelight.com/?problem=PatternMatch
 * @version 0.1
 * @date 2023-07-03
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
#include "pattern_match.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::utils;
using namespace valhalla::strings::pattern_match;

// Test Fixture Data Class
class PatternMatchData {
    std::unordered_set<std::string> m_words, m_expected;
    std::string m_pattern;
public:
    PatternMatchData() = default;

    std::unordered_set<std::string> const & get_words() { return m_words; }
    std::string const & get_pattern() { return m_pattern; }
    std::unordered_set<std::string> const & get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const PatternMatchData &);
    friend std::istream& operator>>(std::istream&, PatternMatchData &);

};

std::ostream& operator<<(std::ostream& out, const PatternMatchData & data) {
    out << "PatternMatchData [ words={";
    for (std::string value : data.m_words) {
        out << " \"" << value << '"';
    } // for
    out << " } pattern=\"" << data.m_pattern << "\" expected={";
    for (std::string value : data.m_expected) {
        out << " \"" << value << '"';
    } // for
    return out << " } ]";
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
    std::basic_istream<char> & operator()(std::basic_istream<char> & in, std::unordered_set<std::string> & uset, int state) {
        std::string entry;

        ::loaders::loader::v5::dataLoader<
            std::string,
            char,
            StringReader,
            1,
            ::checkers::is_character<char,'"'>,
            ::checkers::is_character<char,'"'>,
            ::checkers::is_space_or<','>,
            ::checkers::is_space_noop<int>
        > entryLoader(entry);
        in >> entryLoader;

        uset.insert(entry);

        return in;
    }
};

std::istream& operator>>(std::istream& in, PatternMatchData &data) {
    ::loaders::loader::v5::dataLoader<
        std::unordered_set<std::string>,
        char,
        UnorderedSetReader,
        1,
        ::checkers::is_character<char,'['>,
        ::checkers::is_character<char,']'>,
        ::checkers::is_space_or<','>
    > wordsLoader(data.m_words);
    in >> wordsLoader;

    ::loaders::loader::v5::dataLoader<
        std::string,
        char,
        StringReader,
        1,
        ::checkers::is_character<char,'"'>,
        ::checkers::is_character<char,'"'>,
        ::checkers::is_space_or<','>,
        ::checkers::is_space_noop<int>
    > patternLoader(data.m_pattern);
    in >> patternLoader;

    ::loaders::loader::v5::dataLoader<
        std::unordered_set<std::string>,
        char,
        UnorderedSetReader,
        1,
        ::checkers::is_character<char,'{'>,
        ::checkers::is_character<char,'}'>,
        ::checkers::is_space_or<','>
    > expectedLoader(data.m_expected);
    in >> expectedLoader;

    return in;
}

// Test Fixture Class
class PatternMatchFixture :
    public testing::TestWithParam<PatternMatchData> {
};

// Parameterized Test Definition
TEST_P(PatternMatchFixture, PatternMatchTests) {
    PatternMatchData data = GetParam();

    Solution solution;

    std::unordered_set<std::string> actual = solution.patternMatch(data.get_words(), data.get_pattern());

    ASSERT_EQ(actual, data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(PatternMatchTests, PatternMatchFixture, testing::ValuesIn(
    Loader<PatternMatchData>()(find_path("strings/data/pattern_match.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
