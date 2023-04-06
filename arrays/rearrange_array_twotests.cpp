/**
 * @file rearrange_array_twotests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief
 * @version 0.1
 * @date 2023-02-06
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include <iostream>

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "rearrange_array_two.h"

using namespace valhalla::arrays::rearrange_array_two;
using testing::AnyOfArray;

// Test Fixture Data Class
class RearrangeArrayTwoData {
    std::vector<int> m_input;
    std::vector<std::vector<int>> m_expected;
public:
     RearrangeArrayTwoData() = default;
     RearrangeArrayTwoData(std::vector<int> input, std::vector<std::vector<int>> expected) : m_input(input), m_expected(expected) {}

     std::vector<int> const & get_input() { return m_input; }
     std::vector<std::vector<int>> const & get_expected() { return m_expected; }

     friend std::ostream& operator<<(std::ostream&, const RearrangeArrayTwoData &);
};

std::ostream& operator<<(std::ostream& out, const RearrangeArrayTwoData &data) {
    out << "RearrangeArrayTwoData [ input=[";
    for (int value : data.m_input)
        out << " " << value;
    out << " ] expected=[";
    for (std::vector<int> values : data.m_expected) {
        out << " [";
        for (int value : values) {
            out << " " << value;
        } // for
        out << " ]";
    } // for
    out << " ] ]"; 

    return out;
}


// Test Fixture Class
class RearrangeArrayTwoFixture :
    public testing::TestWithParam<RearrangeArrayTwoData> {
};

// Parameterized Test Definition
TEST_P(RearrangeArrayTwoFixture, RearrangeArrayTwoTests) {
    RearrangeArrayTwoData data = GetParam();

    Solution solution;

    std::vector<int> actual = data.get_input();

    solution.rearrange(actual);

    std::vector<std::vector<int>> const & expected(data.get_expected());

    ASSERT_THAT(actual, AnyOfArray(expected.begin(), expected.end()));
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(RearrangeArrayTwoTests, RearrangeArrayTwoFixture, testing::Values(
    RearrangeArrayTwoData({9, -3, 5, -2, -8, -6, 1, 3}, {{9, -3, 5, -2, 1, -8, 3, -6}, {5, -2, 9, -6, 1, -8, 3, -3}, {9, -3, 5, -2, 1, -6, 3, -8}}),
    RearrangeArrayTwoData({9, -3, 5, -2, -8, -6}, {{5, -2, 9, -6, -3, -8}, {-2, 5, -6, 9, -3, -8}, {9, -3, 5, -2, -8, -6}}),
    RearrangeArrayTwoData({5, 4, 6, -1, 3}, {{5, -1, 4, 6, 3}, {-1, 5, 4, 6, 3}, {5, -1, 6, 4, 3}})
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
