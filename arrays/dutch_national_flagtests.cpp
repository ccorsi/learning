/**
 * @file dutch_national_flagtests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief
 * @version 0.1
 * @date 2023-01-17
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */
#include <iostream>

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "dutch_national_flag.h"

using namespace valhalla::arrays::dutch_national_flag;

class DutchNationalFlagData {
    std::vector<int> m_actual, m_expected;
public:
    DutchNationalFlagData() = default;
    DutchNationalFlagData(std::vector<int>& actual, std::vector<int>& expected) :
        m_actual(actual), m_expected(expected) {}
    DutchNationalFlagData(std::vector<int> actual, std::vector<int> expected) :
        m_actual(actual), m_expected(expected) {}

    const std::vector<int>& GetActual() { return m_actual; }
    const std::vector<int>& GetExpected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const DutchNationalFlagData&);
};

std::ostream& operator<<(std::ostream& out, const DutchNationalFlagData &data) {
    out << "DutchNationalData [ actual = {";
    for(int value : data.m_actual) {
        out << " " << value;
    }
    out << " }, expected = {";
    for(int value : data.m_expected) {
        out << " " << value;
    }
    out << " } ]";

    return out;
}

class DutchNationalFlagFixture :
    public testing::TestWithParam<DutchNationalFlagData> {
};

TEST_P(DutchNationalFlagFixture, DutchNationalFlag) {
    Solution solution;

    DutchNationalFlagData data = GetParam();

    std::vector<int> actual(data.GetActual());

    solution.sort(actual);

    ASSERT_EQ(data.GetExpected(), actual);
}

INSTANTIATE_TEST_SUITE_P(DutchNationalFlag, DutchNationalFlagFixture,
    testing::Values(
        DutchNationalFlagData({},{}),
        DutchNationalFlagData({0},{0}),
        DutchNationalFlagData({0, 1, 2},{0, 1, 2}),
        DutchNationalFlagData({1, 0},{0, 1}),
        DutchNationalFlagData({0, 1, 2, 2, 1, 0, 0, 2, 0, 1, 1, 0},
                              {0, 0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2}),
        DutchNationalFlagData({0, 1, 2, 0, 1, 2, 0, 2, 1},
                              {0, 0, 0, 1, 1, 1, 2, 2, 2}),
        DutchNationalFlagData({1, 1, 1, 1, 1, 1, 1, 1},
                              {1, 1, 1, 1, 1, 1, 1, 1})
    ));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}