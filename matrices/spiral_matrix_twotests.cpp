/**
 * @file spiral_matrix_twotests.cpp
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

#include "spiral_matrix_two.h"

using namespace valhalla::matrices::spiral_matrix_two;

// Test Fixture Data Class
class SpiralMatrixTwoData {
    int m_input;
    std::vector<std::vector<int>> m_expected;
public:
     SpiralMatrixTwoData() = default;
     SpiralMatrixTwoData(int N, std::vector<std::vector<int>> expected) : m_input(N), m_expected(expected) {}

     int get_input() { return m_input; }
     std::vector<std::vector<int>> const & get_expected() { return m_expected; }

     friend std::ostream& operator<<(std::ostream&, const SpiralMatrixTwoData &);
};

std::ostream& operator<<(std::ostream& out, const SpiralMatrixTwoData &data) {
    out << "SpiralMatrixTwoData [ input=" << data.m_input << ", expected=[";
    for(std::vector<int> values : data.m_expected) {
        out << " [";
        for(int value : values)
            out << " " << value;
        out << " ]";
    } // for
    out << " ] ]";

    return out;
}

// Test Fixture Class
class SpiralMatrixTwoFixture :
    public testing::TestWithParam<SpiralMatrixTwoData> {
};

// Parameterized Test Definition
TEST_P(SpiralMatrixTwoFixture, SpiralMatrixTwoTests) {
    SpiralMatrixTwoData data = GetParam();

    Solution solution;

    std::vector<std::vector<int>> actual = solution.spiralTraversal(data.get_input());

    ASSERT_EQ(actual, data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(SpiralMatrixTwoTests, SpiralMatrixTwoFixture, testing::Values(
    SpiralMatrixTwoData(1, {{1}}),
    SpiralMatrixTwoData(5, {{25, 24, 23, 22, 21}, {10, 9,  8,  7,  20}, {11, 2,  1,  6,  19}, {12, 3,  4,  5,  18}, {13, 14, 15, 16, 17}}),
    SpiralMatrixTwoData(1, {{1}})
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
