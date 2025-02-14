/**
 * @file longest_balanced_parenthesistests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief
 * @version 0.1
 * @date 2025-02-07
 *
 * @copyright Copyright (c) 2025 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */
#include <iostream>

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "paths.h"
#include "loaders.h"
#include "longest_balanced_parenthesis.h"
#include "readers.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::utils::readers;
using namespace valhalla::utils;
using namespace valhalla::stack::longest_balanced_parenthesis;

// Test Fixture Data Class
class LongestBalancedParenthesisData {
    std::string m_input;
    int m_expected;
public:
    LongestBalancedParenthesisData() = default;

    std::string const & get_input() { return m_input; }
    int get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const LongestBalancedParenthesisData &);
    friend std::istream& operator>>(std::istream&, LongestBalancedParenthesisData &);

};

std::ostream& operator<<(std::ostream& out, const LongestBalancedParenthesisData & data) {
    out << "LongestBalancedParenthesisData [ input=\"" << data.m_input
        << "\", expected=" << data.m_expected;
    out << " ]";

    return out;
}

std::istream& operator>>(std::istream& in, LongestBalancedParenthesisData &data) {
    ::loaders::loader::v6::dataLoader<
        std::string,
        char,
        StringReader,
        1,
        ::checkers::is_character<char, '"'>,
        ::checkers::is_character<char, '"'>,
        ::checkers::is_space_or<','>,
        ::checkers::is_space_noop<char>
    > InputLoader(data.m_input);
    in >> InputLoader;

    ::loaders::loader::v6::dataLoader<int,char> ExpectedLoader(data.m_expected);
    in >> ExpectedLoader;

    return in;
}

// Test Fixture Class
class LongestBalancedParenthesisFixture :
    public testing::TestWithParam<LongestBalancedParenthesisData> {
};

// Parameterized Test Definition
TEST_P(LongestBalancedParenthesisFixture, LongestBalancedParenthesisTests) {
    LongestBalancedParenthesisData data = GetParam();

    Solution solution;

    ASSERT_EQ(data.get_expected(), solution.findLength(data.get_input()));
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(LongestBalancedParenthesisTests, LongestBalancedParenthesisFixture, testing::ValuesIn(
    Loader<LongestBalancedParenthesisData>()(find_path("stack/data/longest_balanced_parenthesis.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

