/**
 * @file tiles_problemtests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains tests to the problem https://www.techiedelight.com/?problem=TilesProblem
 * @version 0.1
 * @date 2023-06-19
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
#include "tiles_problem.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::utils;
using namespace valhalla::matrices::tiles_problem;

// Test Fixture Data Class
class TilesProblemData {
    int m_input;
    long m_expected;
public:
    TilesProblemData() = default;

    int get_input() { return m_input; }
    long get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const TilesProblemData &);
    friend std::istream& operator>>(std::istream&, TilesProblemData &);

};

std::ostream& operator<<(std::ostream& out, const TilesProblemData & data) {
    return out << "TilesProblemData [ input=" << data.m_input << " expected=" << data.m_expected
        << " ]";
}

std::istream& operator>>(std::istream& in, TilesProblemData &data) {
    ::loaders::loader::v4::dataLoader<
        int,
        char,
        loader::v4::reader<int,char>,
        1,
        ::checkers::is_character_noop<char>,
        ::checkers::is_no_character<char>,
        ::checkers::is_space_or<','>
    > inputLoader(data.m_input);
    in >> inputLoader;

    ::loaders::loader::v4::dataLoader<
        long,
        char,
        loader::v4::reader<long,char>,
        1,
        ::checkers::is_character_noop<char>,
        ::checkers::is_no_character<char>,
        ::checkers::is_space_or<','>
    > expectedLoader(data.m_expected);
    in >> expectedLoader;

    return in;
}

// Test Fixture Class
class TilesProblemFixture :
    public testing::TestWithParam<TilesProblemData> {
};

// Parameterized Test Definition
TEST_P(TilesProblemFixture, TilesProblemTests) {
    TilesProblemData data = GetParam();

    Solution solution;

    long actual = solution.findTotalWays(data.get_input());

    ASSERT_EQ(actual, data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(TilesProblemTests, TilesProblemFixture, testing::ValuesIn(
    Loader<TilesProblemData>()(find_path("matrices/data/tiles_problem.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
