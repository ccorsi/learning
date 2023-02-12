/**
 * @file spiral_matrix_threetests.cpp
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

#include "spiral_matrix_three.h"

using namespace valhalla::matrices::spiral_matrix_three;

// Test Fixture Data Class
class SpiralMatrixThreeData {
    std::vector<int> m_input;
    std::vector<std::vector<int>> m_expected;
public:
     SpiralMatrixThreeData() = default;
     SpiralMatrixThreeData(std::vector<int> input, std::vector<std::vector<int>> expected) : m_input(input), m_expected(expected) {}

     std::vector<int> const & get_input() { return m_input; }
     std::vector<std::vector<int>> const & get_expected() { return m_expected; }

     friend std::ostream& operator<<(std::ostream &, const SpiralMatrixThreeData &);
};

std::ostream& operator<<(std::ostream& out, const SpiralMatrixThreeData &data) {
    out << "SpiralMatrixThreeData [ input=[";
    for (int value : data.m_input)
        out << " " << value;
    out << " ], expected=[";
    for (std::vector<int> values : data.m_expected) {
        out << " [";
        for (int value : values)
            out << " " << value;
        out << " ]";
    }
    out << " ] ]";

    return out;
}

// Test Fixture Class
class SpiralMatrixThreeFixture :
    public testing::TestWithParam<SpiralMatrixThreeData> {
};

// Parameterized Test Definition
TEST_P(SpiralMatrixThreeFixture, SpiralMatrixThreeTests) {
    SpiralMatrixThreeData data = GetParam();

    Solution solution;

    std::vector<std::vector<int>> actual = solution.createSpiralMatrix(data.get_input());

    ASSERT_EQ(actual, data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(SpiralMatrixThreeTests, SpiralMatrixThreeFixture, testing::Values(
    SpiralMatrixThreeData({}, {}),
    SpiralMatrixThreeData({1}, {{1}}),
    SpiralMatrixThreeData({1, 2, 3, 4}, {{1, 2}, {4, 3}}),
    SpiralMatrixThreeData({1, 2, 3, 4, 5, 6, 7, 8, 9}, { {1, 2, 3}, {8, 9, 4}, {7, 6, 5}}),
    SpiralMatrixThreeData({1, 2}, {{1}}),
    SpiralMatrixThreeData({1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25}, {{1, 2, 3, 4, 5}, {16, 17, 18, 19, 6}, {15, 24, 25, 20, 7}, {14, 23, 22, 21, 8}, {13, 12, 11, 10, 9}})
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
