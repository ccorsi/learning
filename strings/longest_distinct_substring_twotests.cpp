/**
 * @file longest_distinct_substring_twotests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains tests to the problem https://www.techiedelight.com/?problem=LongestDistinctSubstringII
 * @version 0.1
 * @date 2023-06-24
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
#include "longest_distinct_substring_two.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::utils;
using namespace valhalla::strings::longest_distinct_substring_two;

// Test Fixture Data Class
class LongestDistinctSubstringTwoData {
    std::string m_s, m_expected;
public:
    LongestDistinctSubstringTwoData() = default;

    std::string const & get_s() { return m_s; }
    std::string const & get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const LongestDistinctSubstringTwoData &);
    friend std::istream& operator>>(std::istream&, LongestDistinctSubstringTwoData &);

};

std::ostream& operator<<(std::ostream& out, const LongestDistinctSubstringTwoData & data) {
    return out << "LongestDistinctSubstringTwoData [ s=\"" << data.m_s << "\" expected=\""
        << data.m_expected << "\" ]";
}

struct StringReader {
    std::basic_istream<char> & operator()(std::basic_istream<char> & in, std::string & str, int state) {

        if (static_cast<char>(in.peek()) != '"') {
            str += static_cast<char>(in.get());
        }

        return in;
    }
};

std::istream& operator>>(std::istream& in, LongestDistinctSubstringTwoData &data) {
    checkers::skip_spaces<char,checkers::is_space_or<','>> skipSpace;

    skipSpace(in);

    ::loaders::loader::v4::dataLoader<
        std::string,
        char,
        StringReader,
        1,
        ::checkers::is_character<char,'"'>,
        ::checkers::is_character<char,'"'>,
        ::checkers::is_space_noop<int>
    > sLoader(data.m_s);
    in >> sLoader;

    skipSpace(in);

    ::loaders::loader::v4::dataLoader<
        std::string,
        char,
        StringReader,
        1,
        ::checkers::is_character<char,'"'>,
        ::checkers::is_character<char,'"'>,
        ::checkers::is_space_noop<int>
    > expectedLoader(data.m_expected);
    in >> expectedLoader;

    skipSpace(in);

    return in;
}

// Test Fixture Class
class LongestDistinctSubstringTwoFixture :
    public testing::TestWithParam<LongestDistinctSubstringTwoData> {
};

// Parameterized Test Definition
TEST_P(LongestDistinctSubstringTwoFixture, LongestDistinctSubstringTwoTests) {
    LongestDistinctSubstringTwoData data = GetParam();

    Solution solution;

    std::string actual = solution.findLongestSubstring(data.get_s());

    ASSERT_EQ(actual, data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(LongestDistinctSubstringTwoTests, LongestDistinctSubstringTwoFixture, testing::ValuesIn(
    Loader<LongestDistinctSubstringTwoData>()(find_path("strings/data/longest_distinct_substring_two.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
