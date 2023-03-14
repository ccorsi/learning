/**
 * @file ball_arrangementstests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains tests for the problem https://www.techiedelight.com/?problem=BallArrangements
 * @version 0.1
 * @date 2023-03-11
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
#include "ball_arrangements.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::dynamic_programming::ball_arrangements;

// Test Fixture Data Class
class BalArrangeMentsData {
    int m_red, m_blue, m_green;
    int m_expected;
public:
    BalArrangeMentsData() = default;

    int get_red() { return m_red; }
    int get_blue() { return m_blue; }
    int get_green() { return m_green; }
    int get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const BalArrangeMentsData &);
    friend std::istream& operator>>(std::istream&, BalArrangeMentsData &);

};

std::ostream& operator<<(std::ostream& out, const BalArrangeMentsData & data) {
    out << "BalArrangeMentsData [ red=" << data.m_red << " blue=" << data.m_blue
        << " green=" << data.m_green << " expected=" << data.m_expected << " ]";

    return out;
}

std::istream& operator>>(std::istream& in, BalArrangeMentsData &data) {
    in >> data.m_red >> data.m_blue >> data.m_green >> data.m_expected;
    std::string line;
    std::getline(in, line); // read end of line

    return in;
}

// Test Fixture Class
class BalArrangeMentsFixture :
    public testing::TestWithParam<BalArrangeMentsData> {
};

// Parameterized Test Definition
TEST_P(BalArrangeMentsFixture, BalArrangeMentsTests) {
    BalArrangeMentsData data = GetParam();

    Solution solution;

    int actual = solution.totalWays(data.get_red(), data.get_blue(), data.get_green());

    ASSERT_EQ(actual, data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(BalArrangeMentsTests, BalArrangeMentsFixture, testing::ValuesIn(
    Loader<BalArrangeMentsData>()(find_path("dynamic_programming/data/ball_arrangements.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
