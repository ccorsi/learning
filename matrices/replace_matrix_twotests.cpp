/**
 * @file replace_matrix_twotests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains the tests for the problem https://www.techiedelight.com/?problem=ReplaceMatrixII
 * @version 0.1
 * @date 2023-02-27
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
#include "replace_matrix_two.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::matrices::replace_matrix_two;

// Test Fixture Data Class
class ReplaceMatrixTwoData {
    std::vector<std::vector<int>> m_input;
    std::vector<std::vector<int>> m_expected;
public:
    ReplaceMatrixTwoData() = default;

    std::vector<std::vector<int>> const & get_input() { return m_input; }
    std::vector<std::vector<int>> const & get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const ReplaceMatrixTwoData &);
    friend std::istream& operator>>(std::istream&, ReplaceMatrixTwoData &);

};

std::ostream& operator<<(std::ostream& out, const ReplaceMatrixTwoData & data) {
    out << "ReplaceMatrixTwoData [ input=[";
    for (std::vector<int> values : data.m_input) {
        out << " [";
        for (int value : values)
            out << " " << value;
        out << " ]";
    } // for
    out << " ] expected=[";
    for (std::vector<int> values : data.m_expected) {
        out << " [";
        for (int value :  values)
            out << " " << value;
        out << " ]";
    } // for
    out << " ] ]";

    return out;
}

std::istream& operator>>(std::istream& in, ReplaceMatrixTwoData &data) {
    matrixLoader<int> inputLoader(data.m_input), expectedLoader(data.m_expected);

    in >> inputLoader >> expectedLoader;

    return in;
}

// Test Fixture Class
class ReplaceMatrixTwoFixture :
    public testing::TestWithParam<ReplaceMatrixTwoData> {
};

void print_matrix(std::vector<std::vector<int>> const & mat) {
    std::cout << "[" << std::endl;
    for (std::vector<int> values : mat) {
        std::cout << "[";
        for (int value : values)
            std::cout << " " << value;
        std::cout << " ]" << std::endl;
    } // for
    std::cout << "]" << std::endl;
}

// Parameterized Test Definition
TEST_P(ReplaceMatrixTwoFixture, ReplaceMatrixTwoTests) {
    ReplaceMatrixTwoData data = GetParam();

    Solution solution;

    std::vector<std::vector<int>> actual = data.get_input();

    solution.replaceZeros(actual);

    // std::cout << "Input: ";
    // print_matrix(data.get_input());
    // std::cout << "Expected: ";
    // print_matrix(data.get_expected());

    ASSERT_EQ(actual, data.get_expected());

}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(ReplaceMatrixTwoTests, ReplaceMatrixTwoFixture, testing::ValuesIn(
    Loader<ReplaceMatrixTwoData>()(find_path("matrices/data/replace_matrix_two.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
