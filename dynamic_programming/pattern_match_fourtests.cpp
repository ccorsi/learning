/**
 * @file pattern_match_fourtests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains tests to the problem https://www.techiedelight.com/?problem=PatternMatchIV
 * @version 0.1
 * @date 2023-07-05
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
#include "pattern_match_four.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::utils;
using namespace valhalla::dynamic_programming::pattern_match_four;

// Test Fixture Data Class
class PatternMatchFourData {
    std::string m_word, m_pattern;
    int m_expected;
public:
    PatternMatchFourData() = default;

    std::string const & get_word() { return m_word; }
    std::string const & get_pattern() { return m_pattern; }
    int get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const PatternMatchFourData &);
    friend std::istream& operator>>(std::istream&, PatternMatchFourData &);

};

std::ostream& operator<<(std::ostream& out, const PatternMatchFourData & data) {
    return out << "PatternMatchFourData [ word=\"" << data.m_word << "\" pattern=\""
        << data.m_pattern << "\" expected=" << data.m_expected << " ]";
}

struct StringReader {
    std::basic_istream<char> & operator()(std::basic_istream<char> & in, std::string & str, int state) {
        if (static_cast<char>(in.peek()) != '"') {
            str += static_cast<char>(in.get());
        }

        return in;
    }
};

std::istream& operator>>(std::istream& in, PatternMatchFourData &data) {
    ::loaders::loader::v5::dataLoader<
        std::string,
        char,
        StringReader,
        1,
        ::checkers::is_character<char,'\''>,
        ::checkers::is_character<char,'\''>,
        ::checkers::is_space_or<','>,
        ::checkers::is_space_noop<int>
    > wordLoader(data.m_word);
    in >> wordLoader;

    ::loaders::loader::v5::dataLoader<
        std::string,
        char,
        StringReader,
        1,
        ::checkers::is_character<char,'\''>,
        ::checkers::is_character<char,'\''>,
        ::checkers::is_space_or<','>,
        ::checkers::is_space_noop<int>
    > patternLoader(data.m_pattern);
    in >> patternLoader;

    ::loaders::loader::v5::dataLoader<
        int,
        char,
        ::loaders::loader::v5::reader<int,char>,
        1,
        ::checkers::is_character_noop<char>,
        ::checkers::is_no_character<char>,
        ::checkers::is_space_or<','>
    > expectedLoader(data.m_expected);
    in >> expectedLoader;

    return in;
}

// Test Fixture Class
class PatternMatchFourFixture :
    public testing::TestWithParam<PatternMatchFourData> {
};

// Parameterized Test Definition
TEST_P(PatternMatchFourFixture, PatternMatchFourTests) {
    PatternMatchFourData data = GetParam();

    Solution solution;

    int actual = solution.count(data.get_word(), data.get_pattern());

    ASSERT_EQ(actual, data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(PatternMatchFourTests, PatternMatchFourFixture, testing::ValuesIn(
    Loader<PatternMatchFourData>()(find_path("dynamic_programming/data/pattern_match_four.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
