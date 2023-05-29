/**
 * @file rod_cutting_twotests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains tests to the problem https://www.techiedelight.com/?problem=RodCuttingII
 * @version 0.1
 * @date 2023-05-21
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include <iostream>

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "paths.h"
#include "loaders.h"
#include "rod_cutting_two.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::utils;
using namespace valhalla::dynamic_programming::rod_cutting_two;

// Test Fixture Data Class
class RodCuttingTwoData {
    int m_input;
    long m_expected;
public:
    RodCuttingTwoData() = default;

    int get_input() { return m_input; }
    long get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const RodCuttingTwoData &);
    friend std::istream& operator>>(std::istream&, RodCuttingTwoData &);

};

std::ostream& operator<<(std::ostream& out, const RodCuttingTwoData & data) {
    return out << "RodCuttingTwoData [ input=" << data.m_input << " expected="
               << data.m_expected << " ]";
}

std::istream& operator>>(std::istream& in, RodCuttingTwoData &data) {
    ::loaders::primitive::primitiveLoader<
      int,
      char,
      ::checkers::is_space_or<','>
    > inputLoader(&data.m_input);
    in >> inputLoader;

    ::loaders::primitive::primitiveLoader<
      long,
      char,
      ::checkers::is_space_or<','>
    > expectedLoader(&data.m_expected);
    in >> expectedLoader;

    return in;
}

// Test Fixture Class
class RodCuttingTwoFixture :
    public testing::TestWithParam<RodCuttingTwoData> {
};

// Parameterized Test Definition
TEST_P(RodCuttingTwoFixture, RodCuttingTwoTests) {
    RodCuttingTwoData data = GetParam();

    Solution solution;

    long actual = solution.findMaxProfit(data.get_input());

    // std::cout << data.get_input() << ", " << data.get_expected() << ", " << actual << std::endl;
    ASSERT_EQ(actual, data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(RodCuttingTwoTests, RodCuttingTwoFixture, testing::ValuesIn(
    Loader<RodCuttingTwoData>()(find_path("dynamic_programming/data/rod_cutting_two.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
