/**
 * @file check_circular_movestests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains tests to the problem https://www.techiedelight.com/?problem=CheckCircularMoves
 * @version 0.1
 * @date 2023-06-22
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
#include "check_circular_moves.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::utils;
using namespace valhalla::strings::check_circular_moves;

// Test Fixture Data Class
class CheckCircularMovesData {
    std::string m_input;
    bool m_expected;
public:
    CheckCircularMovesData() = default;

    std::string const & get_input() { return m_input; }
    bool get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const CheckCircularMovesData &);
    friend std::istream& operator>>(std::istream&, CheckCircularMovesData &);

};

std::ostream& operator<<(std::ostream& out, const CheckCircularMovesData & data) {
    return out << "CheckCircularMovesData [ input=\"" << data.m_input << "\" expected="
        << ((data.m_expected) ? "true" : "false") << " ]";
}

std::istream& operator>>(std::istream& in, CheckCircularMovesData &data) {
    ::loaders::loader::v4::dataLoader<
        std::string,
        char,
        loader::v4::reader<std::string,char>,
        1,
        ::checkers::is_character_noop<char>,
        ::checkers::is_no_character<char>,
        ::checkers::is_space_or<','>
    > inputLoader(data.m_input);
    in >> inputLoader;

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
class CheckCircularMovesFixture :
    public testing::TestWithParam<CheckCircularMovesData> {
};

// Parameterized Test Definition
TEST_P(CheckCircularMovesFixture, CheckCircularMovesTests) {
    CheckCircularMovesData data = GetParam();

    Solution solution;

    bool actual = solution.isCircularMove(data.get_input());

    ASSERT_EQ(actual, data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(CheckCircularMovesTests, CheckCircularMovesFixture, testing::ValuesIn(
    Loader<CheckCircularMovesData>()(find_path("strings/data/check_circular_moves.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
