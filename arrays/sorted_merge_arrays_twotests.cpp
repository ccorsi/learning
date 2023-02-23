/**
 * @file sorted_merge_arrays_twotests.cpp
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

#include "sorted_merge_arrays_two.h"

using namespace valhalla::arrays::sorted_merge_arrays_two;

// Test Fixture Data Class
class SortedMergeArraysTwoData {
    std::vector<int> m_x_input;
    std::vector<int> m_y_input;
    std::vector<int> m_expected;
public:
     SortedMergeArraysTwoData() = default;
     SortedMergeArraysTwoData(std::vector<int> X, std::vector<int> Y, std::vector<int> expected) : m_x_input(X), m_y_input(Y), m_expected(expected) {}

     std::vector<int> get_x_input() { return m_x_input; }
     std::vector<int> get_y_input() { return m_y_input; }
     std::vector<int> const & get_expected() { return m_expected; }

     friend std::ostream& operator<<(std::ostream&, const SortedMergeArraysTwoData &);
};

std::ostream& operator<<(std::ostream& out, const SortedMergeArraysTwoData &data) {
    out << "SortedMergeArraysTwoData [ X=[";
    for (int value : data.m_x_input)
        out << " " << value;
    out << " ], Y=[";
    for (int value : data.m_y_input)
        out << " " << value;
    out << " ], expected=[";
    for (int value : data.m_expected)
        out << " " << value;
    out << " ]";

    return out;
}


// Test Fixture Class
class SortedMergeArraysTwoFixture :
    public testing::TestWithParam<SortedMergeArraysTwoData> {
};

// Parameterized Test Definition
TEST_P(SortedMergeArraysTwoFixture, SortedMergeArraysTwoTests) {
    SortedMergeArraysTwoData data = GetParam();

    Solution solution;

    std::vector<int> x = data.get_x_input();
    std::vector<int> y = data.get_y_input();

    std::vector<int> actual = solution.merge(x, y);

    ASSERT_EQ(actual, data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(SortedMergeArraysTwoTests, SortedMergeArraysTwoFixture, testing::Values(
    SortedMergeArraysTwoData({1, 3, 5}, {2, 6, 7, 10}, {10, 7, 6, 5, 3, 2, 1})
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
