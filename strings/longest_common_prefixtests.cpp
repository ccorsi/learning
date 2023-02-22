/**
 * @file longest_common_prefixtests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains the tests for the problem https://www.techiedelight.com/?problem=LongestCommonPrefix
 * @version 0.1
 * @date 2023-02-22
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include <iostream>

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "paths.h"
#include "loader.h"
#include "longest_common_prefix.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::strings::longest_common_prefix;

// Test Fixture Data Class
class LongestCommonPrefixData {
    std::vector<std::string> m_input;
    std::string m_expected;
public:
    LongestCommonPrefixData() = default;

    std::vector<std::string> const & get_input() { return m_input; }
    std::string const & get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const LongestCommonPrefixData &);
    friend std::istream& operator>>(std::istream&, LongestCommonPrefixData &);

};

std::ostream& operator<<(std::ostream& out, const LongestCommonPrefixData & data) {
    out << "LongestCommonPrefixData [ input=[";
    for(std::string str : data.m_input)
        out << " \"" << str << "\"";
    out << " ] expected=\"" << data.m_expected << "\"";
    out << " ]";

    return out;
}

std::istream& operator>>(std::istream& in, LongestCommonPrefixData &data) {
    if (static_cast<char>(in.peek()) == '[') {
        std::string line;
        std::getline(in, line); // read the '[' line
        while (static_cast<char>(in.peek()) != ']') {
            std::getline(in, line);
            data.m_input.push_back(line);
        } // while
        std::getline(in, line); // read the ']' line
        std::getline(in, data.m_expected); // read expected string
    } // if

    return in;
}

// Test Fixture Class
class LongestCommonPrefixFixture :
    public testing::TestWithParam<LongestCommonPrefixData> {
};

// Parameterized Test Definition
TEST_P(LongestCommonPrefixFixture, LongestCommonPrefixTests) {
    LongestCommonPrefixData data = GetParam();

    Solution solution;

    std::string actual = solution.findLCP(data.get_input());

    ASSERT_EQ(actual, data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(LongestCommonPrefixTests, LongestCommonPrefixFixture, testing::ValuesIn(
    Loader<LongestCommonPrefixData>()(find_path("strings/data/longest_common_prefix.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
