/**
 * @file equilibrium_indextests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief
 * @version 0.1
 * @date 2023-01-25
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "equilibrium_index.h"

using namespace valhalla::arrays::equilibrium_index;

// Test Fixture Data Class
class EquilibriumIndexData {
    std::vector<int> m_input;
    std::unordered_set<int> m_expected;
public:
    EquilibriumIndexData() = default;
    EquilibriumIndexData(std::vector<int> input, std::unordered_set<int> expected) : m_input(input), m_expected(expected) {}

    std::vector<int> const & get_input() { return m_input; }
    std::unordered_set<int> const & get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const EquilibriumIndexData&);
};

#include <iostream>

std::ostream& operator<<(std::ostream& out, const EquilibriumIndexData &value) {
    out << "EquilibriumIndexData [ input=[";
    for(int v : value.m_input)
        out << " " << v;
    out << " ], expected=[";
    for(int v : value.m_expected)
        out << " " << v;
    out << " ] ]";

    return out;
}

// Test Fixture Class
class EquilibriumIndexFixture :
    public testing::TestWithParam<EquilibriumIndexData> {
};

TEST_P(EquilibriumIndexFixture, EquilibriumIndexTests) {
    EquilibriumIndexData data = GetParam();

    Solution solution;

    std::unordered_set<int> actual = solution.find_index(data.get_input());

    ASSERT_EQ(data.get_expected(), actual);
}

INSTANTIATE_TEST_SUITE_P(EquilibriumIndexTests, EquilibriumIndexFixture, testing::Values(
    EquilibriumIndexData({},{}),
    EquilibriumIndexData({0, -3, 5, -4, -2, 3, 1, 0}, {0, 3, 7}),
    EquilibriumIndexData({-7, 3, 7, -3, 1}, {4}),
    EquilibriumIndexData({1, 2, -4, 2}, {0})
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
