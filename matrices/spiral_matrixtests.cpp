/**
 * @file spiral_matrixtests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief
 * @version 0.1
 * @date 2023-02-11
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include <iostream>

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "spiral_matrix.h"

using namespace valhalla::matrices::spiral_matrix;

// Test Fixture Data Class
class SpiralMatrixData {
    std::vector<std::vector<int>> m_input;
    std::vector<int> m_expected;

public:
     SpiralMatrixData() = default;
     SpiralMatrixData(std::vector<std::vector<int>> input, std::vector<int> expected) : m_input(input), m_expected(expected) {}

     std::vector<std::vector<int>> const & get_input() { return m_input; }
     std::vector<int> const & get_expected() { return m_expected; }

     friend std::ostream& operator<<(std::ostream&, const SpiralMatrixData &);
};

std::ostream& operator<<(std::ostream& out, const SpiralMatrixData &data) {
    out << "SpiralMatrixData [ input=[";
    for (std::vector<int> values : data.m_input) {
        out << " [";
        for (int value : values)
            out << " " << value;
        out << " ]";
    } // for
    out << " ], expected=[";
    for (int value : data.m_expected)
        out << " " << value;
    out << " ] ]";

    return out;
}

// Test Fixture Class
class SpiralMatrixFixture :
    public testing::TestWithParam<SpiralMatrixData> {
};

// Parameterized Test Definition
TEST_P(SpiralMatrixFixture, SpiralMatrixTests) {
    SpiralMatrixData data = GetParam();

    Solution solution;

    std::vector<int> actual = solution.spiralTraversal(data.get_input());

    ASSERT_EQ(actual, data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(SpiralMatrixTests, SpiralMatrixFixture, testing::Values(
    SpiralMatrixData({{1, 2, 3, 4, 5}, {16, 17, 18, 19, 6}, {15, 24, 25, 20, 7}, {14, 23, 22, 21, 8}, {13, 12, 11, 10, 9}}, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25}),
    SpiralMatrixData({{1, 2, 3}, {6, 5, 4}}, {1, 2, 3, 4, 5, 6}),
    SpiralMatrixData({{1}}, {1}),
    SpiralMatrixData({{1 ,2}}, {1, 2})
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
