/**
 * @file longest_distinct_substringtests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains tests to the problem https://www.techiedelight.com/?problem=LongestDistinctSubstring
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
#include "longest_distinct_substring.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::utils;
using namespace valhalla::strings::longest_distinct_substring;

// Test Fixture Data Class
class LongestDistinctSubstringData {
    std::string m_s, m_expected;
    int m_k;
public:
    LongestDistinctSubstringData() = default;

    std::string const & get_s() { return m_s; }
    std::string const & get_expected() { return m_expected; }
    int get_k() { return m_k; }

    friend std::ostream& operator<<(std::ostream&, const LongestDistinctSubstringData &);
    friend std::istream& operator>>(std::istream&, LongestDistinctSubstringData &);

};

std::ostream& operator<<(std::ostream& out, const LongestDistinctSubstringData & data) {
    return out << "LongestDistinctSubstringData [ s=\"" << data.m_s << "\" k=" << data.m_k
        << " expected=\"" << data.m_expected << "\" ]";
}

struct StringReader {
    std::basic_istream<char> & operator()(std::basic_istream<char> & in, std::string & str, int state) {

        if (static_cast<char>(in.peek()) != '"') {
            str += static_cast<char>(in.get());
        }

        return in;
    }
};

std::istream& operator>>(std::istream& in, LongestDistinctSubstringData &data) {
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
        int,
        char,
        loader::v4::reader<int,char>,
        1,
        ::checkers::is_character_noop<char>,
        ::checkers::is_no_character<char>,
        ::checkers::is_space_or<','>
    > kLoader(data.m_k);
    in >> kLoader;

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
class LongestDistinctSubstringFixture :
    public testing::TestWithParam<LongestDistinctSubstringData> {
};

// Parameterized Test Definition
TEST_P(LongestDistinctSubstringFixture, LongestDistinctSubstringTests) {
    LongestDistinctSubstringData data = GetParam();

    Solution solution;

    std::string actual = solution.findLongestSubstring(data.get_s(), data.get_k());

    ASSERT_EQ(actual, data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(LongestDistinctSubstringTests, LongestDistinctSubstringFixture, testing::ValuesIn(
    Loader<LongestDistinctSubstringData>()(find_path("strings/data/longest_distinct_substring.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
