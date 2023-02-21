/**
 * @file isomorphic_stringstests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains tests for the problem https://www.techiedelight.com/?problem=IsomorphicStrings
 * @version 0.1
 * @date 2023-02-20
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
#include "isomorphic_strings.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::strings::isomorphic_strings;

// Test Fixture Data Class
class IsomorphicStringData {
    std::string m_x_input;
    std::string m_y_input;
    bool m_expected;
public:
    IsomorphicStringData() = default;
    IsomorphicStringData(std::string X, std::string Y, bool expected) : m_x_input(X), m_y_input(Y), m_expected(expected) {}

    std::string get_x_input() { return m_x_input; }
    std::string get_y_input() { return m_y_input; }
    bool get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const IsomorphicStringData &);
    friend std::istream& operator>>(std::istream&, IsomorphicStringData &);

};

std::ostream& operator<<(std::ostream& out, const IsomorphicStringData & data) {
    out << "IsomorphicStringData [ X=\"" << data.m_x_input << "\", Y=\"" << data.m_y_input << "\", expected=" <<
        ((data.m_expected == true) ? "true" : "false");
    out << " ]";

    return out;
}

std::istream& operator>>(std::istream& in, IsomorphicStringData &data) {
    std::getline(in, data.m_x_input);
    std::getline(in, data.m_y_input);

    in >> data.m_expected;
    std::string line;
    std::getline(in, line); // read the remaining end of line

    return in;
}

// Test Fixture Class
class IsomorphicStringFixture :
    public testing::TestWithParam<IsomorphicStringData> {
};

// Parameterized Test Definition
TEST_P(IsomorphicStringFixture, IsomorphicStringTests) {
    IsomorphicStringData data = GetParam();

    Solution solution;

    bool actual = solution.isIsomorphic(data.get_x_input(), data.get_y_input());

    ASSERT_EQ(actual, data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(IsomorphicStringTests, IsomorphicStringFixture, testing::ValuesIn(
    Loader<IsomorphicStringData>()(find_path("strings/data/isomorphic_strings.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
