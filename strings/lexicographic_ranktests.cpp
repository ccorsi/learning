/**
 * @file lexicographic_ranktests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains tests to the problem https://www.techiedelight.com/?problem=LexicographicRank
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
#include "lexicographic_rank.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::utils;
using namespace valhalla::strings::lexicographic_rank;

// Test Fixture Data Class
class LexicographicRankData {
    std::string m_s;
    long m_expected;
public:
    LexicographicRankData() = default;

    std::string const & get_s() { return m_s; }
    long get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const LexicographicRankData &);
    friend std::istream& operator>>(std::istream&, LexicographicRankData &);

};

std::ostream& operator<<(std::ostream& out, const LexicographicRankData & data) {
    return out << "LexicographicRankData [ s=\"" << data.m_s << "\" expected="
        << data.m_expected << " ]";
}

struct StringReader {
    std::basic_istream<char> & operator()(std::basic_istream<char> & in, std::string & str, int state) {
        if (static_cast<char>(in.peek()) != '"') {
            str += static_cast<char>(in.get());
        }

        return in;
    }
};

std::istream& operator>>(std::istream& in, LexicographicRankData &data) {
    ::loaders::loader::v5::dataLoader<
        std::string,
        char,
        StringReader,
        1,
        ::checkers::is_character<char,'"'>,
        ::checkers::is_character<char,'"'>,
        ::checkers::is_space_or<','>,
        ::checkers::is_space_noop<int>
    > sLoader(data.m_s);
    in >> sLoader;

    ::loaders::loader::v5::dataLoader<
        long,
        char,
        loader::v5::reader<long,char>,
        1,
        ::checkers::is_character_noop<char>,
        ::checkers::is_no_character<char>,
        ::checkers::is_space_or<','>
    > expectedLoader(data.m_expected);
    in >> expectedLoader;

    return in;
}

// Test Fixture Class
class LexicographicRankFixture :
    public testing::TestWithParam<LexicographicRankData> {
};

// Parameterized Test Definition
TEST_P(LexicographicRankFixture, LexicographicRankTests) {
    LexicographicRankData data = GetParam();

    Solution solution;

    long actual = solution.findLexicographicRank(data.get_s());

    ASSERT_EQ(actual, data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(LexicographicRankTests, LexicographicRankFixture, testing::ValuesIn(
    Loader<LexicographicRankData>()(find_path("strings/data/lexicographic_rank.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
