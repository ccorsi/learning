/**
 * @file pattern_match_twotests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains tests to the problem https://www.techiedelight.com/?problem=PatternMatchII
 * @version 0.1
 * @date 2023-07-04
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
#include "pattern_match_two.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::utils;
using namespace valhalla::strings::pattern_match_two;

// Test Fixture Data Class
class PatternMatchTwoData {
    std::string m_word, m_pattern;
    bool m_expected;
public:
    PatternMatchTwoData() = default;

    std::string const & get_word() { return m_word; }
    std::string const & get_pattern() { return m_pattern; }
    bool get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const PatternMatchTwoData &);
    friend std::istream& operator>>(std::istream&, PatternMatchTwoData &);

};

std::ostream& operator<<(std::ostream& out, const PatternMatchTwoData & data) {
    return out << "PatternMatchTwoData [ word=\"" << data.m_word << "\" pattern=\""
        << data.m_pattern << "\" expected="
        << ((data.m_expected) ? "true" : "false") << " ]";
}

struct StringReader {
    std::basic_istream<char> & operator()(std::basic_istream<char> & in, std::string & str, int state) {
        if (static_cast<char>(in.peek()) != '"') {
            str += static_cast<char>(in.get());
        }

        return in;
    }
};

std::istream& operator>>(std::istream& in, PatternMatchTwoData &data) {
    ::loaders::loader::v5::dataLoader<
        std::string,
        char,
        StringReader,
        1,
        ::checkers::is_character<char,'"'>,
        ::checkers::is_character<char,'"'>,
        ::checkers::is_space_or<','>,
        ::checkers::is_space_noop<int>
    > wordLoader(data.m_word);
    in >> wordLoader;

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
        bool,
        char,
        loader::v5::reader<bool,char>,
        1,
        ::checkers::is_character_noop<char>,
        ::checkers::is_no_character<char>,
        ::checkers::is_space_or<','>
    > expectedLoader(data.m_expected);
    in >> expectedLoader;

    return in;
}

// Test Fixture Class
class PatternMatchTwoFixture :
    public testing::TestWithParam<PatternMatchTwoData> {
};

// Parameterized Test Definition
TEST_P(PatternMatchTwoFixture, PatternMatchTwoTests) {
    PatternMatchTwoData data = GetParam();

    Solution solution;

    bool actual = solution.checkPattern(data.get_word(), data.get_pattern());

    ASSERT_EQ(actual, data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(PatternMatchTwoTests, PatternMatchTwoFixture, testing::ValuesIn(
    Loader<PatternMatchTwoData>()(find_path("strings/data/pattern_match_two.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
