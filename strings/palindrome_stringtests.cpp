/**
 * @file palindrome_stringtests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains tests to the problem https://www.techiedelight.com/?problem=PalindromeString
 * @version 0.1
 * @date 2023-06-28
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
#include "palindrome_string.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::utils;
using namespace valhalla::strings::palindrome_string;

// Test Fixture Data Class
class PalindromeStringData {
    std::string m_s;
    bool m_expected;
public:
    PalindromeStringData() = default;

    std::string const & get_s() { return m_s; }
    bool get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const PalindromeStringData &);
    friend std::istream& operator>>(std::istream&, PalindromeStringData &);

};

std::ostream& operator<<(std::ostream& out, const PalindromeStringData & data) {
    return out << "PalindromeStringData [ s=\"" << data.m_s << "\" expected="
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

std::istream& operator>>(std::istream& in, PalindromeStringData &data) {
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
class PalindromeStringFixture :
    public testing::TestWithParam<PalindromeStringData> {
};

// Parameterized Test Definition
TEST_P(PalindromeStringFixture, PalindromeStringTests) {
    PalindromeStringData data = GetParam();

    Solution solution;

    bool actual = solution.isPalindrome(data.get_s());

    ASSERT_EQ(actual, data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(PalindromeStringTests, PalindromeStringFixture, testing::ValuesIn(
    Loader<PalindromeStringData>()(find_path("strings/data/palindrome_string.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
