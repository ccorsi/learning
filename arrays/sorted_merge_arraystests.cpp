/**
 * @file sorted_merge_arraystests.cpp
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

#include "sorted_merge_arrays.h"

using namespace valhalla::arrays::sorted_merge_arrays;

// Test Fixture Data Class
class SortedMergeArraysData {
    std::vector<int> m_X_input;
    std::vector<int> m_Y_input;
    std::vector<int> m_expected;
public:
     SortedMergeArraysData() = default;
     SortedMergeArraysData(std::vector<int> X, std::vector<int> Y, std::vector<int> expected) : m_X_input(X), m_Y_input(Y), m_expected(expected) {}

     std::vector<int> const & get_X_input() { return m_X_input; }
     std::vector<int> const & get_Y_input() { return m_Y_input; }
     std::vector<int> const & get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream &, const SortedMergeArraysData &);
};

std::ostream& operator<<(std::ostream& out, const SortedMergeArraysData &data) {
    out << "SortedMergeArraysData [ X=[";
    for (int value : data.m_X_input)
        out << " " << value;
    out << " ], Y=[";
    for (int value : data.m_Y_input)
        out << " " << value;
    out << " ], expected=[";
    for (int value : data.m_expected)
        out << " " << value;
    out << " ]";

    return out;
}


// Test Fixture Class
class SortedMergeArraysFixture :
    public testing::TestWithParam<SortedMergeArraysData> {
};

// Parameterized Test Definition
TEST_P(SortedMergeArraysFixture, SortedMergeArraysTests) {
    SortedMergeArraysData data = GetParam();

    Solution solution;

    std::vector<int> actual = solution.merge(data.get_X_input(), data.get_Y_input());

    ASSERT_EQ(actual, data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(SortedMergeArraysTests, SortedMergeArraysFixture, testing::Values(
    SortedMergeArraysData({1, 3, 5, 7}, {2, 4, 6}, {1, 2, 3, 4, 5, 6, 7})
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
