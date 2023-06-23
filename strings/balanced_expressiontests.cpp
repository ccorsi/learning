/**
 * @file balanced_expressiontests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains tests to the problem https://www.techiedelight.com/?problem=BalancedExpression
 * @version 0.1
 * @date 2023-06-23
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
#include "balanced_expression.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::utils;
using namespace valhalla::strings::balanced_expression;

// Test Fixture Data Class
class BalancedExpressionData {
    std::string m_s;
    bool m_expected;
public:
    BalancedExpressionData() = default;

    std::string const & get_s() { return m_s; }
    bool get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const BalancedExpressionData &);
    friend std::istream& operator>>(std::istream&, BalancedExpressionData &);

};

std::ostream& operator<<(std::ostream& out, const BalancedExpressionData & data) {
    return out << "BalancedExpressionData [ s=\"" << data.m_s << "\" expected="
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

std::istream& operator>>(std::istream& in, BalancedExpressionData &data) {
    ::checkers::skip_spaces<char,::checkers::is_space_or<','>> skipSpace;

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
        bool,
        char,
        loader::v4::reader<bool,char>,
        1,
        ::checkers::is_character_noop<char>,
        ::checkers::is_no_character<char>,
        ::checkers::is_space_or<','>
    > expectedLoader(data.m_expected);
    in >> expectedLoader;

    return in;
}

// Test Fixture Class
class BalancedExpressionFixture :
    public testing::TestWithParam<BalancedExpressionData> {
};

// Parameterized Test Definition
TEST_P(BalancedExpressionFixture, BalancedExpressionTests) {
    BalancedExpressionData data = GetParam();

    Solution solution;

    bool actual = solution.isBalanced(data.get_s());

    ASSERT_EQ(actual, data.get_expected());

}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(BalancedExpressionTests, BalancedExpressionFixture, testing::ValuesIn(
    Loader<BalancedExpressionData>()(find_path("strings/data/balanced_expression.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
