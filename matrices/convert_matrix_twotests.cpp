/**
 * @file convert_matrix_twotests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains tests for the problem https://www.techiedelight.com/?problem=ConvertMatrixII
 * @version 0.1
 * @date 2023-02-23
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
#include "convert_matrix_two.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::matrices::convert_matrix_two;

// Test Fixture Data Class
class ConvertMatrixTwoData {
    std::vector<std::vector<int>> m_input;
    int m_expected;
public:
    ConvertMatrixTwoData() = default;

    std::vector<std::vector<int>> const & get_input() { return m_input; }
    int get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const ConvertMatrixTwoData &);
    friend std::istream& operator>>(std::istream&, ConvertMatrixTwoData &);

};

std::ostream& operator<<(std::ostream& out, const ConvertMatrixTwoData & data) {
    out << "ConvertMatrixTwoData [ input=[";
    for (std::vector<int> values : data.m_input) {
        out << " [";
        for (int value : values) {
            out << " " << value;
        } // for
        out << " ]";
    } // for
    out << " ] expected=" << data.m_expected;
    out << " ]";

    return out;
}

std::istream& operator>>(std::istream& in, ConvertMatrixTwoData &data) {
    if (static_cast<char>(in.peek()) == '[') {
        std::string line;
        std::getline(in, line); // read the '[' line
        std::vector<int>::size_type row = 0;
        while (static_cast<char>(in.peek()) != ']') {
            if (static_cast<char>(in.peek()) == '[') {
                char chr;
                in >> chr; // read the '[' character
                data.m_input.push_back(std::vector<int>()); // add a new vector to the vector
                while (static_cast<char>(in.peek()) != ']') {
                    int value;
                    in >> value; // read the next value
                    data.m_input[row].push_back(value);
                } // while
                std::getline(in, line); // read the ']' and end of line
                row++; // increment the row
            } // if
        } // while
        std::getline(in, line); // read ']' character line
        in >> data.m_expected;
        std::getline(in, line); // read the end of line
    } // if

    return in;
}

// Test Fixture Class
class ConvertMatrixTwoFixture :
    public testing::TestWithParam<ConvertMatrixTwoData> {
};

// Parameterized Test Definition
TEST_P(ConvertMatrixTwoFixture, ConvertMatrixTwoTests) {
    ConvertMatrixTwoData data = GetParam();

    Solution solution;

    std::vector<std::vector<int>> input = data.get_input();

    int actual = solution.findMinPasses(input);

    ASSERT_EQ(actual, data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(ConvertMatrixTwoTests, ConvertMatrixTwoFixture, testing::ValuesIn(
    Loader<ConvertMatrixTwoData>()(find_path("matrices/data/convert_matrix_two.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
