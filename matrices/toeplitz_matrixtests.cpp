/**
 * @file toeplitz_matrixtests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains the tests to the problem https://www.techiedelight.com/?problem=ToeplitzMatrix
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
#include "toeplitz_matrix.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::matrices::toeplitz_matrix;

// Test Fixture Data Class
class ToeplitzMatrixData {
    std::vector<std::vector<int>> m_input;
    bool m_expected;
public:
    ToeplitzMatrixData() = default;

    std::vector<std::vector<int>> const & get_input() { return m_input; }
    bool get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const ToeplitzMatrixData &);
    friend std::istream& operator>>(std::istream&, ToeplitzMatrixData &);

};

std::ostream& operator<<(std::ostream& out, const ToeplitzMatrixData & data) {
    out << "ToeplitzMatrixData [ input=[";
    for (std::vector<int> values : data.m_input) {
        out << " [";
        for (int value : values)
            out << " " << value;
        out << " ]";
    } // for
    out << " ] expected=" << ((data.m_expected) ? "true" : "false") << " ]";

    return out;
}

std::istream& operator>>(std::istream& in, ToeplitzMatrixData &data) {
    matrixLoader<int> loader(data.m_input);

    in >> loader;

    in >> data.m_expected;
    std::string line;
    std::getline(in, line); // read the end of line

    return in;
}

// Test Fixture Class
class ToeplitzMatrixFixture :
    public testing::TestWithParam<ToeplitzMatrixData> {
};

// Parameterized Test Definition
TEST_P(ToeplitzMatrixFixture, ToeplitzMatrixTests) {
    ToeplitzMatrixData data = GetParam();

    Solution solution;

    bool actual = solution.checkToeplitz(data.get_input());

    ASSERT_EQ(actual, data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(ToeplitzMatrixTests, ToeplitzMatrixFixture, testing::ValuesIn(
    Loader<ToeplitzMatrixData>()(find_path("matrices/data/toeplitz_matrix.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
