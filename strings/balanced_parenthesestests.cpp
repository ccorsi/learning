/**
 * @file balanced_parenthesestests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains tests to the problem https://www.techiedelight.com/?problem=BalancedParentheses
 * @version 0.1
 * @date 2023-06-26
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
#include "balanced_parentheses.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::utils;
using namespace valhalla::strings::balanced_parentheses;

// Test Fixture Data Class
class BalancedParenthesesData {
    int m_n;
    std::unordered_set<std::string> m_expected;
public:
    BalancedParenthesesData() = default;

    int get_n() { return m_n; }
    std::unordered_set<std::string> const & get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const BalancedParenthesesData &);
    friend std::istream& operator>>(std::istream&, BalancedParenthesesData &);

};

std::ostream& operator<<(std::ostream& out, const BalancedParenthesesData & data) {
    out << "BalancedParenthesesData [ n=" << data.m_n << " expected={";
    for (std::string value : data.m_expected) {
        out << " \"" << value << "\"";
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

std::istream& operator>>(std::istream& in, BalancedParenthesesData &data) {
    ::loaders::loader::v5::dataLoader<
        int,
        char,
        loader::v5::reader<int,char>,
        1,
        ::checkers::is_character_noop<char>,
        ::checkers::is_no_character<char>,
        ::checkers::is_space_or<','>
    > nLoader(data.m_n);
    in >> nLoader;

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
class BalancedParenthesesFixture :
    public testing::TestWithParam<BalancedParenthesesData> {
};

// Parameterized Test Definition
TEST_P(BalancedParenthesesFixture, BalancedParenthesesTests) {
    BalancedParenthesesData data = GetParam();

    Solution solution;

    std::unordered_set<std::string> actual = solution.findPalindromicPermutations(data.get_n());

    ASSERT_EQ(actual, data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(BalancedParenthesesTests, BalancedParenthesesFixture, testing::ValuesIn(
    Loader<BalancedParenthesesData>()(find_path("strings/data/balanced_parentheses.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
