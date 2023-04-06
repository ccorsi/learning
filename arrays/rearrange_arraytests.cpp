/**
 * @file rearrange_arraytests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief
 * @version 0.1
 * @date 2023-02-05
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include <iostream>

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "rearrange_array.h"

using namespace valhalla::arrays::rearrange_array;
using testing::AnyOfArray;

// Test Fixture Data Class
class RearrangeArrayData {
    std::vector<int> m_input;
    std::vector<std::vector<int>> m_expected;
public:
     RearrangeArrayData() = default;
     RearrangeArrayData(std::vector<int> input, std::vector<std::vector<int>> expected) : m_input(input), m_expected(expected) {}

     std::vector<int> const & get_input() { return m_input; }
     std::vector<std::vector<int>> const & get_expected() { return m_expected; }

     friend std::ostream& operator<<(std::ostream&, const RearrangeArrayData&);
};

std::ostream& operator<<(std::ostream& out, const RearrangeArrayData &data) {
    out << "RearrangeArrayData [ input=[";
    for (int value : data.m_input)
        out << " " << value;
    out << " ], expected=[";
    for (std::vector<int> values : data.m_expected) {
        out << " [";
        for (int value : values)
            out << " " << value;
        out << " ]";
    } // for
    out << " ] ]";

    return out;
}

// Test Fixture Class
class RearrangeArrayFixture :
    public testing::TestWithParam<RearrangeArrayData> {
};

// Parameterized Test Definition
TEST_P(RearrangeArrayFixture, RearrangeArrayTests) {
    RearrangeArrayData data = GetParam();

    Solution solution;

    std::vector<int> actual = data.get_input();

    solution.rearrange(actual);

    ASSERT_THAT(actual, AnyOfArray(data.get_expected()));
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(RearrangeArrayTests, RearrangeArrayFixture, testing::Values(
    RearrangeArrayData({1, 2, 3, 4, 5, 6, 7}, {{1, 3, 2, 5, 4, 7, 6}, {1, 5, 2, 6, 3, 7, 4}}),
    RearrangeArrayData({6, 9, 2, 5, 1, 4}, {{6, 9, 2, 5, 1, 4}, {1, 5, 2, 6, 4, 9}})
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
