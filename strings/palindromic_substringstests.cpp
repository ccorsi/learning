/**
 * @file palindromic_substringstests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains tests to the problem https://www.techiedelight.com/?problem=PalindromicSubstrings
 * @version 0.1
 * @date 2023-06-22
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
#include "palindromic_substrings.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::utils;
using namespace valhalla::strings::palindromic_substrings;

// Test Fixture Data Class
class PalindromicSubstringsData {
    std::string m_input;
    std::unordered_set<std::string> m_expected;
public:
    PalindromicSubstringsData() = default;

    std::string const & get_input() { return m_input; }
    std::unordered_set<std::string> const & get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const PalindromicSubstringsData &);
    friend std::istream& operator>>(std::istream&, PalindromicSubstringsData &);

};

std::ostream& operator<<(std::ostream& out, const PalindromicSubstringsData & data) {
    out << "PalindromicSubstringsData [ input=\"" << data.m_input << "\" expected=[";
    for (std::string value : data.m_expected) {
        out << " \"" << value << "\"";
    } // for
    return out << " ] ]";
}

struct SetReader {
    std::basic_istream<char> & operator()(std::basic_istream<char> & in, std::unordered_set<std::string> & uset, int state) {
        std::string entry;

        ::loaders::loader::v4::dataLoader<
            std::string,
            char,
            loader::v4::reader<std::string,char>,
            1,
            ::checkers::is_character_noop<char>,
            ::checkers::is_no_character<char>,
            ::checkers::is_space_or<','>
        > enrtyLoader(entry);
        in >> enrtyLoader;

        uset.insert(entry);

        return in;
    }
};

std::istream& operator>>(std::istream& in, PalindromicSubstringsData &data) {
    ::loaders::loader::v4::dataLoader<
        std::string,
        char,
        loader::v4::reader<std::string,char>,
        1,
        ::checkers::is_character_noop<char>,
        ::checkers::is_no_character<char>,
        ::checkers::is_space_or<','>
    > inputLoader(data.m_input);
    in >> inputLoader;

    ::loaders::loader::v4::dataLoader<
        std::unordered_set<std::string>,
        char,
        SetReader,
        1,
        ::checkers::is_character<char,'{'>,
        ::checkers::is_character<char,'}'>,
        ::checkers::is_space_or<','>
    > expectedLoader(data.m_expected);
    in >> expectedLoader;

    return in;
}

// Test Fixture Class
class PalindromicSubstringsFixture :
    public testing::TestWithParam<PalindromicSubstringsData> {
};

// Parameterized Test Definition
TEST_P(PalindromicSubstringsFixture, PalindromicSubstringsTests) {
    PalindromicSubstringsData data = GetParam();

    Solution solution;

    std::unordered_set<std::string> actual = solution.findPalindromicSubstrings(data.get_input());

    ASSERT_EQ(actual, data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(PalindromicSubstringsTests, PalindromicSubstringsFixture, testing::ValuesIn(
    Loader<PalindromicSubstringsData>()(find_path("strings/data/palindromic_substrings.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
