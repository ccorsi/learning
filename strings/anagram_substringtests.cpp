/**
 * @file anagram_substringtests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains tests to the problem https://www.techiedelight.com/?problem=AnagramSubstring
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
#include "anagram_substring.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::utils;
using namespace valhalla::strings::anagram_substring;

// Test Fixture Data Class
class AnagramSubstringData {
    std::string m_x, m_y;
    std::vector<int> m_expected;
public:
    AnagramSubstringData() = default;

    std::string const & get_x() { return m_x; }
    std::string const & get_y() { return m_y; }
    std::vector<int> const & get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const AnagramSubstringData &);
    friend std::istream& operator>>(std::istream&, AnagramSubstringData &);

};

std::ostream& operator<<(std::ostream& out, const AnagramSubstringData & data) {
    out << "AnagramSubstringData [ X=\"" << data.m_x << "\" Y=\"" << data.m_y << "\" expected=[";
    for (int value : data.m_expected) {
        out << " " << value;
    } // for
    return out << " ] ]";
}

struct VectorReader {
    std::basic_istream<char> & operator()(std::basic_istream<char> & in, std::vector<int> & vec, int state) {
        int entry;

        ::loaders::loader::v5::dataLoader<
            int,
            char,
            loader::v5::reader<int,char>,
            1,
            ::checkers::is_character_noop<char>,
            ::checkers::is_no_character<char>,
            ::checkers::is_space_or<','>,
            ::checkers::is_space_or<','>
        > entryLoader(entry);
        in >> entryLoader;

        vec.push_back(entry);

        return in;
    }
};

struct StringReader {
    std::basic_istream<char> & operator()(std::basic_istream<char> & in, std::string & str, int state) {
        if (static_cast<char>(in.peek()) != '"') {
            str += static_cast<char>(in.get());
        }

        return in;
    }
};

std::istream& operator>>(std::istream& in, AnagramSubstringData &data) {
    ::loaders::loader::v5::dataLoader<
        std::string,
        char,
        StringReader,
        1,
        ::checkers::is_character<char,'"'>,
        ::checkers::is_character<char,'"'>,
        ::checkers::is_space_or<','>,
        ::checkers::is_space_noop<int>
    > xLoader(data.m_x);
    in >> xLoader;

    ::loaders::loader::v5::dataLoader<
        std::string,
        char,
        StringReader,
        1,
        ::checkers::is_character<char,'"'>,
        ::checkers::is_character<char,'"'>,
        ::checkers::is_space_or<','>,
        ::checkers::is_space_noop<int>
    > yLoader(data.m_y);
    in >> yLoader;

    ::loaders::loader::v5::dataLoader<
        std::vector<int>,
        char,
        VectorReader,
        1,
        ::checkers::is_character<char,'['>,
        ::checkers::is_character<char,']'>,
        ::checkers::is_space_or<','>,
        ::checkers::is_space_or<','>
    > expectedLoader(data.m_expected);
    in >> expectedLoader;

    return in;
}

// Test Fixture Class
class AnagramSubstringFixture :
    public testing::TestWithParam<AnagramSubstringData> {
};

// Parameterized Test Definition
TEST_P(AnagramSubstringFixture, AnagramSubstringTests) {
    AnagramSubstringData data = GetParam();

    Solution solution;

    std::vector<int> actual = solution.findAllAnagrams(data.get_x(), data.get_y());

    ASSERT_EQ(actual, data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(AnagramSubstringTests, AnagramSubstringFixture, testing::ValuesIn(
    Loader<AnagramSubstringData>()(find_path("strings/data/anagram_substring.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
