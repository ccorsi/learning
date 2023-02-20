/**
 * @file interleaving_stringtests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief
 * @version 0.1
 * @date 2023-02-14
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include <iostream>
#include <fstream>

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "paths.h"
#include "loader.h"
#include "interleaving_string.h"

using namespace valhalla::strings::interleaving_string;
using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;

// Test Fixture Data Class
class InterleavingStringData {
    std::string m_x_input;
    std::string m_y_input;
    std::unordered_set<std::string> m_expected;

public:
    InterleavingStringData() = default;
    InterleavingStringData(std::string x, std::string y, std::unordered_set<std::string> expected) : m_x_input(x), m_y_input(y), m_expected(expected) {}

    std::string get_x_input() { return m_x_input; }
    std::string get_y_input() { return m_y_input; }
    std::unordered_set<std::string> const & get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const InterleavingStringData&);
    friend std::istream& operator>>(std::istream&, InterleavingStringData&);
};

std::ostream& operator<<(std::ostream& out, const InterleavingStringData &data) {
    out << "InterleavingStringData [ X=\"" << data.m_x_input << "\" Y=\"" << data.m_y_input << "\" expected=[" ;
    for (std::string s : data.m_expected)
        out << " \"" << s << "\"";
    out << " ] ]";

    return out;
}

std::istream& operator>>(std::istream& in, InterleavingStringData &data) {
    // populate the X and Y inputs
    std::getline(in, data.m_x_input);
    std::getline(in, data.m_y_input);

    // populate the expected entries
    std::string line;
    std::getline(in, line);
    if (line == "{") {
        std::getline(in, line);
        while (line != "}") {
            data.m_expected.insert(line);
            std::getline(in, line);
        } // while
    } // if

    return in;
}

// Test Fixture Class
class InterleavingStringFixture :
    public testing::TestWithParam<InterleavingStringData> {
};

// Parameterized Test Definition
TEST_P(InterleavingStringFixture, InterleavingStringTests) {
    InterleavingStringData data = GetParam();

    Solution solution;

    std::unordered_set<std::string> actual = solution.findInterleavings(data.get_x_input(), data.get_y_input());

    ASSERT_EQ(actual, data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(InterleavingStringTests, InterleavingStringFixture,
                         testing::ValuesIn(Loader<InterleavingStringData>()(find_path("strings/data/interleaving_string.txt"))));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
