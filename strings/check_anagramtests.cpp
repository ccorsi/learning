/**
 * @file check_anagramtests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief
 * @version 0.1
 * @date 2023-02-13
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include <iostream>

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "check_anagram.h"

using namespace valhalla::strings::check_anagram;

// Test Fixture Data Class
class CheckAnagramData {
    std::string m_x_input;
    std::string m_y_input;
    bool        m_expected;

public:
    CheckAnagramData() = default;
    CheckAnagramData(std::string x, std::string y, bool expected) : m_x_input(x), m_y_input(y), m_expected(expected) {}

    std::string get_x_input() { return m_x_input; }
    std::string get_y_input() { return m_y_input; }
    bool get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const CheckAnagramData&);

};

std::ostream& operator<<(std::ostream& out, const CheckAnagramData &data) {
    out << "CheckAnagramData [ X=\"" << data.m_x_input << "\" Y=\"" << data.m_y_input << "\" expected=";
    out << data.m_expected << " ]";

    return out;
}

// Test Fixture Class
class CheckAnagramFixture :
    public testing::TestWithParam<CheckAnagramData> {
};

// Parameterized Test Definition
TEST_P(CheckAnagramFixture, CheckAnagramTests) {
    CheckAnagramData data = GetParam();

    Solution solution;

    ASSERT_EQ(solution.isAnagram(data.get_x_input(), data.get_y_input()), data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(CheckAnagramTests, CheckAnagramFixture, testing::Values(
    CheckAnagramData("silent", "listen", true),
    CheckAnagramData("incest", "insect", true),
    CheckAnagramData("bad", "god", false)
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
