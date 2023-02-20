/**
 * @file interleaving_string_twotests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief
 * @version 0.1
 * @date 2023-02-18
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
#include "interleaving_string_two.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::strings::interleaving_string_two;

// Test Fixture Data Class
class InterleavingStringTwoData {
    std::string m_x_input;
    std::string m_y_input;
    std::string m_s_input;
    bool m_expected;

public:
    InterleavingStringTwoData() = default;
    InterleavingStringTwoData(std::string X, std::string Y, std::string S, bool expected) : m_x_input(X), m_y_input(Y), m_s_input(S), m_expected(expected) {}

    std::string get_x_input() { return m_x_input; }
    std::string get_y_input() { return m_y_input; }
    std::string get_s_input() { return m_s_input; }
    bool get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const InterleavingStringTwoData &);
    friend std::istream& operator>>(std::istream&, InterleavingStringTwoData &);

};

std::ostream& operator<<(std::ostream& out, const InterleavingStringTwoData & data) {
    out << "InterleavingStringTwoData [ X=\"" << data.m_x_input << "\" Y=\"" << data.m_y_input;
    out << "\" S=\"" << data.m_s_input << "\" expected=" << ((data.m_expected) ? "true" : "false");
    out << " ]";

    return out;
}

std::istream& operator>>(std::istream& in, InterleavingStringTwoData &data) {
    std::getline(in, data.m_x_input);
    std::getline(in, data.m_y_input);
    std::getline(in, data.m_s_input);
    in >> data.m_expected;
    // read the newline
    std::string line;
    std::getline(in, line);

    return in;
}

// Test Fixture Class
class InterleavingStringTwoFixture :
    public testing::TestWithParam<InterleavingStringTwoData> {
};

// Parameterized Test Definition
TEST_P(InterleavingStringTwoFixture, InterleavingStringTwoTests) {
    InterleavingStringTwoData data = GetParam();

    Solution solution;

    bool actual = solution.isInterleaving(data.get_x_input(), data.get_y_input(), data.get_s_input());

    ASSERT_EQ(actual, data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(InterleavingStringTwoTests, InterleavingStringTwoFixture, testing::ValuesIn(
    Loader<InterleavingStringTwoData>()(find_path("strings/data/interleaving_string_two.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
