/**
 * @file convert_matrixtests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains the tests for the problem https://www.techiedelight.com/?problem=ConvertMatrix
 * @version 0.1
 * @date 2023-02-22
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
#include "convert_matrix.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::matrices::convert_matrix;

// Test Fixture Data Class
class ConvertMatrixData {
    std::vector<std::vector<int>> m_input;
    std::vector<std::vector<int>> m_expected;
public:
    ConvertMatrixData() = default;

    std::vector<std::vector<int>> get_input() { return m_input; }
    std::vector<std::vector<int>> const & get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const ConvertMatrixData &);
    friend std::istream& operator>>(std::istream&, ConvertMatrixData &);

};

std::ostream& operator<<(std::ostream& out, const ConvertMatrixData & data) {
    out << "ConvertMatrixData [ input=[";
    for (std::vector<int> values : data.m_input) {
        out << " [";
        for (int value : values)
            out << " " << value;
        out << " ]";
    } // for
    out << " ] expected=[";
    for (std::vector<int> values : data.m_expected) {
        out << " [";
        for (int value : values)
            out << " " << value;
        out << " ]";
    } // for
    out << " ] ]";

    return out;
}

std::istream& operator>>(std::istream& in, ConvertMatrixData &data) {
    if (static_cast<char>(in.peek()) == '[') {
        std::string line;
        std::getline(in, line); // read '[' character line
        std::vector<int>::size_type row = 0;
        while (static_cast<char>(in.peek()) != ']') {
            // std::cout << "1 - Read [" << std::endl;
            if (static_cast<char>(in.peek()) == '[') {
                char chr;
                in >> chr; // read the '[' character
                // std::cout << "1 - Read chr " << chr << std::endl;
                data.m_input.push_back(std::vector<int>()); // add a new vector to the vector
                while (static_cast<char>(in.peek()) != ']') {
                    int value;
                    in >> value; // read the next value
                    // std::cout << "1 - Adding value: " << value << " for row " << row << std::endl;
                    data.m_input[row].push_back(value);
                    // std::cout << "1 - Added value: " << value << " for row " << row << std::endl;
                } // while
                std::getline(in, line); // read the ']' and end of line
                // std::cout << "1 - line: " << line << std::endl;
                row++; // increment the row
            } // if
        } // while
        std::getline(in, line); // read ']' character line
        // std::cout << "1 - Read line: " << line << std::endl;
        row = 0; // reset the row since we are loading another matrix
        if (static_cast<char>(in.peek()) == '[') {
            std::getline(in, line); // read '[' character line
            // std::cout << "2 - Read [ " << line << std::endl;
            while (static_cast<char>(in.peek()) != ']') {
                if (static_cast<char>(in.peek()) == '[') {
                    char chr;
                    in >> chr; // read the '[' character
                    // std::cout << "2 - Read chr " << chr << std::endl;
                    data.m_expected.push_back(std::vector<int>()); // add a new vector to the vector
                    while (static_cast<char>(in.peek()) != ']') {
                        int value;
                        in >> value; // read the next value
                        // std::cout << "2 - Adding value: " << value << " for row " << row << std::endl;
                        data.m_expected[row].push_back(value);
                        // std::cout << "2 - Added value: " << value << " for row " << row << std::endl;
                    } // while
                    std::getline(in, line); // read the ']' and end of line
                    row++; // increment the row
                    // std::cout << "1 - line: " << line << std::endl;
                } // if
            } // while
            std::getline(in, line); // read ']' character line
            // std::cout << "2 - Read line: " << line << std::endl;
        } // if
    } // if

    return in;
}

// Test Fixture Class
class ConvertMatrixFixture :
    public testing::TestWithParam<ConvertMatrixData> {
};

// Parameterized Test Definition
TEST_P(ConvertMatrixFixture, ConvertMatrixTests) {
    ConvertMatrixData data = GetParam();

    Solution solution;

    std::vector<std::vector<int>> actual = data.get_input();

    solution.convertMatrix(actual);

    ASSERT_EQ(actual, data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(ConvertMatrixTests, ConvertMatrixFixture, testing::ValuesIn(
    Loader<ConvertMatrixData>()(find_path("matrices/data/convert_matrix.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
