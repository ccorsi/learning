/**
 * @file fill_matrixtests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains tests to the problem https://www.techiedelight.com/?problem=FillMatrix
 * @version 0.1
 * @date 2023-02-28
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
#include "fill_matrix.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::matrices::fill_matrix;

// Test Fixture Data Class
class FillMatrixData {
    std::vector<std::vector<int>> m_input;
    std::vector<std::vector<int>> m_expected;
public:
    FillMatrixData() = default;

    std::vector<std::vector<int>> const & get_input() { return m_input; }
    std::vector<std::vector<int>> const & get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const FillMatrixData &);
    friend std::istream& operator>>(std::istream&, FillMatrixData &);

};

std::ostream& operator<<(std::ostream& out, const FillMatrixData & data) {
    out << "FillMatrixData [ input=[";
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

std::istream& operator>>(std::istream& in, FillMatrixData &data) {
    {
        matrixLoader<int> loader = matrixLoader<int>(data.m_input);
        in >> loader;
    }
    {
        matrixLoader<int> loader = matrixLoader<int>(data.m_expected);
        in >> loader;
    }

    return in;
}

// Test Fixture Class
class FillMatrixFixture :
    public testing::TestWithParam<FillMatrixData> {
};

void print_matrix(std::vector<std::vector<int>> const & mat) {
    std::cout << "[" << std::endl;
    for(std::vector<int> values : mat) {
        std::cout << "[";
        for (int value : values) {
            std::cout << " " << value;
        } // for
        std::cout << " ]" << std::endl;
    } // for
    std::cout << "]" << std::endl;
}

// Parameterized Test Definition
TEST_P(FillMatrixFixture, FillMatrixTests) {
    FillMatrixData data = GetParam();

    Solution solution;

    std::vector<std::vector<int>> actual = data.get_input();

    solution.fillMatrix(actual);

    std::cout << "Actual: ";
    print_matrix(actual);

    ASSERT_EQ(actual, data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(FillMatrixTests, FillMatrixFixture, testing::ValuesIn(
    Loader<FillMatrixData>()(find_path("matrices/data/fill_matrix.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
