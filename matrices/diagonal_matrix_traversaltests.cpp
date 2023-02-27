/**
 * @file diagonal_matrix_traversaltests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains the tests for the problem https://www.techiedelight.com/?problem=DiagonalMatrixTraversal
 * @version 0.1
 * @date 2023-02-24
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
#include "diagonal_matrix_traversal.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::matrices::diagonal_matrix_traversal;

// Test Fixture Data Class
class DiagonalMatrixTraversalData {
    std::vector<std::vector<int>> m_input;
    std::vector<std::vector<int>> m_expected;
public:
    DiagonalMatrixTraversalData() = default;

    std::vector<std::vector<int>> const & get_input() { return m_input; }
    std::vector<std::vector<int>> const & get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const DiagonalMatrixTraversalData &);
    friend std::istream& operator>>(std::istream&, DiagonalMatrixTraversalData &);

};

std::ostream& operator<<(std::ostream& out, const DiagonalMatrixTraversalData & data) {
    out << "DiagonalMatrixTraversalData [ ";
    out << " ]";

    return out;
}

std::istream& operator>>(std::istream& in, DiagonalMatrixTraversalData &data) {
    if (static_cast<char>(in.peek()) == '[') {
        std::string line;
        std::getline(in, line); // read the '[' line
        while (static_cast<char>(in.peek()) != ']') {
            if (static_cast<char>(in.peek()) == '[') {
                char chr;
                in >> chr; // read the '[' character
                data.m_input.push_back(std::vector<int>()); // add a instance of a vector
                std::vector<int> & entries = data.m_input.back(); // get a reference to the added entry
                while (static_cast<char>(in.peek()) != ']') {
                    int value;
                    in >> value;
                    entries.push_back(value); // add the entry to the vector
                } // while
                std::getline(in, line); // read the ']' and the end of the line
            } // if
        } // while
        std::getline(in, line); // read the ']' and the end of the line
        if (static_cast<char>(in.peek()) == '[') {
            std::getline(in, line); // read the '[' line
            while (static_cast<char>(in.peek()) != ']') {
                if (static_cast<char>(in.peek()) == '[') {
                    char chr;
                    in >> chr; // read the '[' character
                    data.m_expected.push_back(std::vector<int>()); // add a instance of a vector
                    std::vector<int> & entries = data.m_expected.back(); // get a reference to the added entry
                    while (static_cast<char>(in.peek()) != ']') {
                        int value;
                        in >> value;
                        entries.push_back(value); // add the entry to the vector
                    } // while
                    std::getline(in, line); // read the ']' and the end of the line
                } // if
            } // while
            std::getline(in, line); // read the ']' and the end of the line
        } // if
    } // if

    return in;
}

// Test Fixture Class
class DiagonalMatrixTraversalFixture :
    public testing::TestWithParam<DiagonalMatrixTraversalData> {
};

// Parameterized Test Definition
TEST_P(DiagonalMatrixTraversalFixture, DiagonalMatrixTraversalTests) {
    DiagonalMatrixTraversalData data = GetParam();

    Solution solution;

    std::vector<std::vector<int>> actual = solution.diagonalTraversal(data.get_input());

    ASSERT_EQ(actual, data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(DiagonalMatrixTraversalTests, DiagonalMatrixTraversalFixture, testing::ValuesIn(
    Loader<DiagonalMatrixTraversalData>()(find_path("matrices/data/diagonal_matrix_traversal.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
