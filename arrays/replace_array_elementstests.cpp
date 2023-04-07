/**
 * @file replace_array_elementstests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief
 * @version 0.1
 * @date 2023-02-04
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include <iostream>

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "replace_array_elements.h"

using namespace valhalla::arrays::replace_array_elements;

// Test Fixture Data Class
class ReplaceArrayElementsData {
    std::vector<int> m_input;
    std::vector<int> m_expected;
public:
    ReplaceArrayElementsData() = default;
    ReplaceArrayElementsData(std::vector<int> input, std::vector<int> expected) : m_input(input), m_expected(expected) {}

    std::vector<int> const & get_input() { return m_input; }
    std::vector<int> const & get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const ReplaceArrayElementsData &); 
};

std::ostream& operator<<(std::ostream& out, const ReplaceArrayElementsData &value) {
    out << "ReplaceArrayElementsData [ input=[";
    for (int v : value.m_input)
        out << " " << v;
    out << " ], expected=[";
    for(int v : value.m_expected)
        out << " " << v;
    out << " ] ]";

    return out;
}

// Test Fixture Class
class ReplaceArrayElementsFixture :
    public testing::TestWithParam<ReplaceArrayElementsData> {
};

TEST_P(ReplaceArrayElementsFixture, ReplaceArrayElementsTests) {
    ReplaceArrayElementsData data = GetParam();

    Solution solution;

    std::vector<int> actual(data.get_input());

    solution.rearrange(actual);

    ASSERT_EQ(data.get_expected(), actual);
}

INSTANTIATE_TEST_SUITE_P(ReplaceArrayElementsTests, ReplaceArrayElementsFixture, testing::Values(
    ReplaceArrayElementsData({1, 2, 3, 4, 5},{120, 60, 40, 30, 24}),
    ReplaceArrayElementsData({}, {}),
    ReplaceArrayElementsData({5, 3, 4, 2, 6, 8}, {1152, 1920, 1440, 2880, 960, 720}),
    ReplaceArrayElementsData({10}, {1})
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
