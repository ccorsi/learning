/**
 * @file combinations_tentests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains tests for the problem https://www.techiedelight.com/?problem=CombinationsX
 * @version 0.1
 * @date 2023-03-06
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
#include "combinations_ten.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::dynamic_programming::combinations_ten;

// Test Fixture Data Class
class CombinationsTenData {
    std::vector<std::vector<char>> m_keypad;
    int m_input;
    int m_expected;
public:
    CombinationsTenData() = default;

    std::vector<std::vector<char>> const & get_keypad() { return m_keypad; }
    int get_input() { return m_input; }
    int get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const CombinationsTenData &);
    friend std::istream& operator>>(std::istream&, CombinationsTenData &);

};

std::ostream& operator<<(std::ostream& out, const CombinationsTenData & data) {
    out << "CombinationsTenData [ keypad={";
    for (std::vector<char> keys : data.m_keypad) {
        out << " {";
        for (char key : keys)
            out << " '" << key << "'";
        out << " }";
    } // for
    out << " } input=" << data.m_input << " expected=" << data.m_expected << " ]";

    return out;
}

std::istream& operator>>(std::istream& in, CombinationsTenData &data) {
    in >> matrixLoader<char>(data.m_keypad, '{', '}');
    in >> data.m_input >> data.m_expected;
    std::string line;
    std::getline(in, line); // read end of line

    return in;
}

// Test Fixture Class
class CombinationsTenFixture :
    public testing::TestWithParam<CombinationsTenData> {
};

// Parameterized Test Definition
TEST_P(CombinationsTenFixture, CombinationsTenTests) {
    CombinationsTenData data = GetParam();

    Solution solution;

    int actual = solution.findCombinations(data.get_keypad(), data.get_input());

    ASSERT_EQ(actual, data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(CombinationsTenTests, CombinationsTenFixture, testing::ValuesIn(
    Loader<CombinationsTenData>()(find_path("dynamic_programming/data/combinations_ten.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
