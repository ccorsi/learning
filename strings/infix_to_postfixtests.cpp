/**
 * @file infix_to_postfixtests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains tests to the problem https://www.techiedelight.com/?problem=InfixToPostfix
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
#include "infix_to_postfix.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::utils;
using namespace valhalla::strings::infix_to_postfix;

// Test Fixture Data Class
class InfixToPostfixData {
    std::string m_infix, m_expected;
public:
    InfixToPostfixData() = default;

    std::string const & get_infix() { return m_infix; }
    std::string const & get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const InfixToPostfixData &);
    friend std::istream& operator>>(std::istream&, InfixToPostfixData &);

};

std::ostream& operator<<(std::ostream& out, const InfixToPostfixData & data) {
    return out << "InfixToPostfixData [ infix=\"" << data.m_infix << "\" expected=\""
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

std::istream& operator>>(std::istream& in, InfixToPostfixData &data) {
    ::loaders::loader::v5::dataLoader<
        std::string,
        char,
        StringReader,
        1,
        ::checkers::is_character<char,'"'>,
        ::checkers::is_character<char,'"'>,
        ::checkers::is_space_or<','>,
        ::checkers::is_space_noop<int>
    > infixLoader(data.m_infix);
    in >> infixLoader;

    ::loaders::loader::v5::dataLoader<
        std::string,
        char,
        StringReader,
        1,
        ::checkers::is_character<char,'"'>,
        ::checkers::is_character<char,'"'>,
        ::checkers::is_space_or<','>,
        ::checkers::is_space_noop<int>
    > expectedLoader(data.m_expected);
    in >> expectedLoader;

    return in;
}

// Test Fixture Class
class InfixToPostfixFixture :
    public testing::TestWithParam<InfixToPostfixData> {
};

// Parameterized Test Definition
TEST_P(InfixToPostfixFixture, InfixToPostfixTests) {
    InfixToPostfixData data = GetParam();

    Solution solution;

    std::string actual = solution.infixToPostfix(data.get_infix());

    ASSERT_EQ(actual, data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(InfixToPostfixTests, InfixToPostfixFixture, testing::ValuesIn(
    Loader<InfixToPostfixData>()(find_path("strings/data/infix_to_postfix.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
