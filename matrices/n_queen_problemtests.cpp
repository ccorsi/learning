/**
 * @file n_queen_problemtests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains tests for the problem https://www.techiedelight.com/?problem=NQueenProblem
 * @version 0.1
 * @date 2023-03-01
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include <iostream>
#include <stdexcept>

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "paths.h"
#include "loader.h"
#include "n_queen_problem.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::matrices::n_queen_problem;

// Test Fixture Data Class
class NQueenProblemData {
    int m_n;
    std::set<std::vector<std::vector<int>>> m_expected;
public:
    NQueenProblemData() = default;

    int get_n() { return m_n; }
    std::set<std::vector<std::vector<int>>> const & get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const NQueenProblemData &);
    friend std::istream& operator>>(std::istream&, NQueenProblemData &);

};

std::ostream& operator<<(std::ostream& out, const NQueenProblemData & data) {
    out << "NQueenProblemData [ N=" << data.m_n << " expected={";
    for (std::vector<std::vector<int>> mat : data.m_expected) {
        out << " [";
        for (std::vector<int> values : mat) {
            out << " [";
            for (int value : values)
                out << " " << value;
            out << " ]";
        }
        out << " ]";
    }
    out << " } ]";

    return out;
}

std::istream& operator>>(std::istream& in, NQueenProblemData &data) {
    in >> data.m_n;
    std::string line;
    std::getline(in, line); // read end of line
    if (static_cast<char>(in.peek()) == '{') {
        std::getline(in, line); // read '{' character line
        while (static_cast<char>(in.peek()) != '}') {
            std::vector<std::vector<int>> mat;
            matrixLoader<int> loader(mat);
            in >> loader;
            data.m_expected.insert(mat);
        } // while
        std::getline(in, line); // read '}' character line
        // std::cout << "Loaded: " << data << std::endl;
    } else {
        throw std::runtime_error("Invalid opening character");
    } // else

    return in;
}

// Test Fixture Class
class NQueenProblemFixture :
    public testing::TestWithParam<NQueenProblemData> {
};

// Parameterized Test Definition
TEST_P(NQueenProblemFixture, NQueenProblemTests) {
    NQueenProblemData data = GetParam();

    Solution solution;

    std::set<std::vector<std::vector<int>>> actual = solution.solveNQueen(data.get_n());

    ASSERT_EQ(actual, data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(NQueenProblemTests, NQueenProblemFixture, testing::ValuesIn(
    Loader<NQueenProblemData>()(find_path("matrices/data/n_queen_problem.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
