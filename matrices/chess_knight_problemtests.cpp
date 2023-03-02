/**
 * @file chess_knight_problemtests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains tests for the problem https://www.techiedelight.com/?problem=ChessKnightProblem
 * @version 0.1
 * @date 2023-03-02
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
#include "chess_knight_problem.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::matrices::chess_knight_problem;

// Test Fixture Data Class
class ChessKnightProblemData {
    int m_n, m_expected;
    std::pair<int,int> m_src, m_dest;
public:
    ChessKnightProblemData() = default;

    int get_n() { return m_n; }
    std::pair<int,int> const & get_src() { return m_src; }
    std::pair<int,int> const & get_dest() { return m_dest; }
    int get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const ChessKnightProblemData &);
    friend std::istream& operator>>(std::istream&, ChessKnightProblemData &);

};

std::ostream& operator<<(std::ostream& out, const ChessKnightProblemData & data) {
    out << "ChessKnightProblemData [ n=" << data.m_n << " src=(" << data.m_src.first << ","
        << data.m_src.second << ") dest=(" << data.m_dest.first << ","
        << data.m_dest.second << ") expected=" << data.m_expected << " ]";

    return out;
}

std::istream& operator>>(std::istream& in, ChessKnightProblemData &data) {
    std::string line;

    in >> data.m_n;
    std::getline(in, line); // read end of line

    if (static_cast<char>(in.peek()) == '(') {
        char chr;
        in >> chr; // read the '(' character
        in >> data.m_src.first
         >> data.m_src.second
         >> chr; // read the ')' character
        std::getline(in, line); // read end of line
        if (static_cast<char>(in.peek()) == '(') {
            in >> chr; // read the '(' character
            in >> data.m_dest.first
            >> data.m_dest.second
            >> chr; // read the ')' character
            std::getline(in, line); // read end of line
            in >> data.m_expected;
            std::getline(in, line); // read end of line
        } else {
            throw std::runtime_error("Invalid input format");
        } // else
    } else {
        throw std::runtime_error("Invalid input format");
    } // else

    return in;
}

// Test Fixture Class
class ChessKnightProblemFixture :
    public testing::TestWithParam<ChessKnightProblemData> {
};

// Parameterized Test Definition
TEST_P(ChessKnightProblemFixture, ChessKnightProblemTests) {
    ChessKnightProblemData data = GetParam();

    Solution solution;

    int actual = solution.findShortestDistance(data.get_n(), data.get_src(), data.get_dest());

    ASSERT_EQ(actual, data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(ChessKnightProblemTests, ChessKnightProblemFixture, testing::ValuesIn(
    Loader<ChessKnightProblemData>()(find_path("matrices/data/chess_knight_problem.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
