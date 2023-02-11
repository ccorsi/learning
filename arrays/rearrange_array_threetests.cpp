/**
 * @file rearrange_array_threetests.cpp
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

#include "rearrange_array_three.h"

using namespace valhalla::arrays::rearrange_array_three;

// Test Fixture Data Class
class RearrangeArrayThreeData {
    std::vector<int> m_input;
    std::vector<int> m_expected;
public:
     RearrangeArrayThreeData() = default;
     RearrangeArrayThreeData(std::vector<int> input, std::vector<int> expected) : m_input(input), m_expected(expected) {}

     std::vector<int> get_input() { return m_input; }
     const std::vector<int> & get_expected() { return m_expected; }

     friend std::ostream& operator<<(std::ostream&, const RearrangeArrayThreeData &);
};

std::ostream& operator<<(std::ostream& out, const RearrangeArrayThreeData &data) {
    out << "RearrangeArrayThreeData [ input=[";
    for (int value : data.m_input)
        out << " " << value;
    out << " ], expected=[";
    for (int value : data.m_expected)
        out << " " << value;
    out << " ] ]";

    return out;
}


// Test Fixture Class
class RearrangeArrayThreeFixture :
    public testing::TestWithParam<RearrangeArrayThreeData> {
};

// Parameterized Test Definition
TEST_P(RearrangeArrayThreeFixture, RearrangeArrayThreeTests) {
    RearrangeArrayThreeData data = GetParam();

    Solution solution;

    std::vector<int> actual = data.get_input();

    solution.rearrange(actual);

    ASSERT_EQ(actual, data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(RearrangeArrayThreeTests, RearrangeArrayThreeFixture, testing::Values(
    RearrangeArrayThreeData({1, 3, 4, 2, 0}, {4, 0, 3, 1, 2}),
    RearrangeArrayThreeData({0, 1, 2, 3, 4}, {0, 1, 2, 3, 4}),
    RearrangeArrayThreeData({1, 0, 3, 2, 4}, {1, 0, 3, 2, 4})
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
