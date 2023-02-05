/**
 * @file majority_elementtests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief
 * @version 0.1
 * @date 2023-02-04
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "majority_element.h"

using namespace valhalla::arrays::majority_element;

// Test Fixture Data Class
class MajorityElementData {
    std::vector<int> m_input;
    const int m_expected;
public:
    MajorityElementData() = default;
    MajorityElementData(std::vector<int> input, int expected) : m_input(input), m_expected(expected) {}

    std::vector<int>& get_input() { return m_input; }
    int get_expected() { return m_expected; }
};

// Test Fixture Class
class MajorityElementFixture :
    public testing::TestWithParam<MajorityElementData> {
};

TEST_P(MajorityElementFixture, MajorityElementTests) {
    MajorityElementData data = GetParam();

    Solution solution;

    int actual = solution.findMajorityElement(data.get_input());

    ASSERT_EQ(data.get_expected(), actual);
}

INSTANTIATE_TEST_SUITE_P(MajorityElementTests, MajorityElementFixture, testing::Values(
    MajorityElementData({2, 8, 7, 2, 2, 5, 2, 3, 1, 2, 2}, 2),
    MajorityElementData({1, 3, 1, 1}, 1)
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
