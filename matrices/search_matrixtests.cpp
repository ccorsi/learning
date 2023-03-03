/**
 * @file search_matrixtests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains tests for the problem https://www.techiedelight.com/?problem=SearchMatrix
 * @version 0.1
 * @date 2023-03-03
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
#include "search_matrix.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::matrices::search_matrix;

// Test Fixture Data Class
class SearchMatrixData {
    std::vector<std::vector<int>> m_input;
    int m_target;
    std::set<std::pair<int,int>> m_expected;
public:
    SearchMatrixData() = default;

    std::vector<std::vector<int>> const & get_input() { return m_input; }
    int get_target() { return m_target; }
    std::set<std::pair<int,int>> const & get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const SearchMatrixData &);
    friend std::istream& operator>>(std::istream&, SearchMatrixData &);

};

std::ostream& operator<<(std::ostream& out, const SearchMatrixData & data) {
    out << "SearchMatrixData [ input=[";
    for (std::vector<int> values : data.m_input) {
        out << " [";
        for (int value : values)
            out << " " << value;
        out << " ]";
    } // for
    out << " ] target=" << data.m_target << " expected={";
    for (std::pair<int,int> point : data.m_expected) {
        out << " (" << point.first << "," << point.second << ")";
    }
    out << " } ]";

    return out;
}

std::istream& operator>>(std::istream& in, SearchMatrixData &data) {
    if (static_cast<char>(in.peek()) == '[') {
        matrixLoader<int> loader(data.m_input);
        in >> loader;
        in >> data.m_target;
        std::string line;
        std::getline(in, line); // read end of line
        if (static_cast<char>(in.peek()) == '{') {
            std::getline(in, line); // read the '{' line
            while (static_cast<char>(in.peek()) != '}') {
                if (static_cast<char>(in.peek()) == '(') {
                    char chr;
                    std::pair<int,int> point;
                    in >> chr >> point.first >> point.second;
                    data.m_expected.insert(point); // add to set
                    std::getline(in, line); // read ')' to end of line
                } else {
                    // std::cout << "Inner invalid input format" << std::endl;
                    throw std::runtime_error("Invalid input format");
                } // else
            } // while
            std::getline(in, line); // read '}' line
            return in;
        } // if
    } // if

    // std::cout << "Outer invalid input format" << std::endl;

    throw std::runtime_error("Invalid input format");
}

// Test Fixture Class
class SearchMatrixFixture :
    public testing::TestWithParam<SearchMatrixData> {
};

// Parameterized Test Definition
TEST_P(SearchMatrixFixture, SearchMatrixTests) {
    SearchMatrixData data = GetParam();

    Solution solution;

    std::set<std::pair<int,int>> actual = solution.findElement(data.get_input(), data.get_target());

    ASSERT_EQ(actual, data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(SearchMatrixTests, SearchMatrixFixture, testing::ValuesIn(
    Loader<SearchMatrixData>()(find_path("matrices/data/search_matrix.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
