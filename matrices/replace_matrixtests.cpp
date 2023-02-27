/**
 * @file replace_matrixtests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains the tests for the problem https://www.techiedelight.com/?problem=ReplaceMatrix
 * @version 0.1
 * @date 2023-02-24
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
#include "replace_matrix.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::matrices::replace_matrix;

// Test Fixture Data Class
class ReplaceMatrixData {
    std::vector<std::vector<int>> m_input;
    std::vector<std::vector<int>> m_expected;
public:
    ReplaceMatrixData() = default;

    std::vector<std::vector<int>> get_input() { return m_input; }
    std::vector<std::vector<int>> const & get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const ReplaceMatrixData &);
    friend std::istream& operator>>(std::istream&, ReplaceMatrixData &);

};

std::ostream& operator<<(std::ostream& out, const ReplaceMatrixData & data) {
    out << "ReplaceMatrixData [ input=[";
    for (const std::vector<int> & values : data.m_input) {
        out << " [";
        for (const int value : values)
            out << " " << value;
        out << " ]";
    } // for
    out << " ] expected=[";
    for (const std::vector<int> & values : data.m_expected) {
        out << " [";
        for (const int value : values)
            out << " " << value;
        out << " ]";
    } // for
    out << " ] ]";

    return out;
}

std::istream& operator>>(std::istream& in, ReplaceMatrixData &data) {
    if (static_cast<char>(in.peek()) == '[') {
        std::string line;
        std::getline(in, line); // read the '[' line
        // std::cout << "Input Read line: " << line << std::endl;
        while (static_cast<char>(in.peek()) != ']') {
            data.m_input.push_back(std::vector<int>()); // create a new instance of vector
            std::vector<int> & values = data.m_input.back(); // get a reference to the newly create instance
            vectorLoader<int> vecLoader('[',']', values); // create a loader instance
            // std::cout << "Before calling vectorLoader >> operator" << std::endl;
            in >> vecLoader; // load the values into the vector
            // std::cout << "Loader vector= [";
            // for(int value : values)
            //     std::cout << " " << value;
            // std::cout << " ]" << std::endl;
        } // while
        std::getline(in, line); // read the ']' and end of line
        // std::cout << "Input Done Read line: " << line << std::endl;
        if (static_cast<char>(in.peek()) == '[') {
            std::getline(in, line); // read the '[' line
            // std::cout << "Expected Read line: " << line << std::endl;
            while (static_cast<char>(in.peek() != ']')) {
                data.m_expected.push_back(std::vector<int>()); // create a new instance of vector
                std::vector<int> & values = data.m_expected.back(); // get a reference to the newly create instance
                vectorLoader<int> vecLoader('[',']', values); // create a matrix loader instance
                // std::cout << "Before calling vectorLoader >> operator" << std::endl;
                in >> vecLoader; // load the values into vector
                // std::cout << "Loader vector= [";
                // for(int value : values)
                //     std::cout << " " << value;
                // std::cout << " ]" << std::endl;
            } // while
            std::getline(in, line); // read the ']' and end of line
            // std::cout << "Expected Done Read line: " << line << std::endl;
            return in; // return only successfully processed data
        } // if
    } // if

    // std::cout << "Throwing an exception" << std::endl;
    throw std::runtime_error("Invalid input format");
}

// Test Fixture Class
class ReplaceMatrixFixture :
    public testing::TestWithParam<ReplaceMatrixData> {
};

void print_matrix(std::vector<std::vector<int>> const & matrix) {
    std::cout << "[" << std::endl;
    for (std::vector<int> values : matrix) {
        std::cout << "[";
        for (int value : values)
            std::cout << " " << value;
        std::cout << " ]" << std::endl;
    } // for
    std::cout << "]" << std::endl;
} // print_matrix

// Parameterized Test Definition
TEST_P(ReplaceMatrixFixture, ReplaceMatrixTests) {
    ReplaceMatrixData data = GetParam();

    Solution solution;

    std::vector<std::vector<int>> actual = data.get_input();

    solution.replaceZeroes(actual);

    // std::cout << "Input: ";
    // print_matrix(data.get_input());
    // std::cout << "Actual: ";
    // print_matrix(actual);
    // std::cout << "Expected: ";
    // print_matrix(data.get_expected());

    ASSERT_EQ(actual, data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(ReplaceMatrixTests, ReplaceMatrixFixture, testing::ValuesIn(
    Loader<ReplaceMatrixData>()(find_path("matrices/data/replace_matrix.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
