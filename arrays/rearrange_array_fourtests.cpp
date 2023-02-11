/**
 * @file rearrange_array_fourtests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief
 * @version 0.1
 * @date 2023-02-10
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include <iostream>

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "rearrange_array_four.h"

using namespace valhalla::arrays::rearrange_array_four;
using ::testing::AnyOfArray;

// Test Fixture Data Class
class RearrangeArrayFourData {
    std::vector<int> m_input;
    std::vector<std::vector<int>> m_expected;
public:
     RearrangeArrayFourData() = default;
     RearrangeArrayFourData(std::vector<int> input, std::vector<std::vector<int>> expected) : m_input(input), m_expected(expected) {}

     std::vector<int> get_input() { return m_input; }
     const std::vector<std::vector<int>> & get_expected() { return m_expected; }

     friend std::ostream& operator<<(std::ostream&, const RearrangeArrayFourData &);
};

std::ostream& operator<<(std::ostream& out, const RearrangeArrayFourData &data) {
    out << "RearrangeArrayFourData [ input=[";
    for (int v : data.m_input)
        out << " " << v;
    out << " ], expected=[";
    for (std::vector<int> values : data.m_expected) {
        out << " [";
        for (int value : values) {
            out << " " << value;
        } // for
        out << " ]";
    } // for
    out << " ]";

    return out;
}

// Test Fixture Class
class RearrangeArrayFourFixture :
    public testing::TestWithParam<RearrangeArrayFourData> {
};

// Parameterized Test Definition
TEST_P(RearrangeArrayFourFixture, RearrangeArrayFourTests) {
    RearrangeArrayFourData data = GetParam();

    Solution solution;

    std::vector<int> actual(data.get_input());

    solution.rearrange(actual);

    const std::vector<std::vector<int>> & expected = data.get_expected();

    ASSERT_THAT(actual, AnyOfArray(expected.begin(), expected.end()));
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(RearrangeArrayFourTests, RearrangeArrayFourFixture, testing::Values(
    RearrangeArrayFourData({9, -3, 5, -2, -8, -6, 1, 3}, {{-3, -2, -8, -6, 9, 5, 1, 3}, {-6, -3, -8, -2, 5, 9, 1, 3}}),
    RearrangeArrayFourData({-4, -2, -7, -9}, {{-4, -2, -7, -9}}),
    RearrangeArrayFourData({2, 4, 3, 1, 5}, {{2, 4, 3, 1, 5}}),
    RearrangeArrayFourData({1, 2, 3, 4, 5, 6, -1, 3, -5, -9, 3, -10, 11, -13, -14, -20}, {{-20, -14, -13, -10, -9, -5, -1, 3, 6, 5, 3, 4, 11, 3, 2, 1}})
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
