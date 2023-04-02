/**
 * @file minimum_range_twotests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains tests to the problem https://www.techiedelight.com/?problem=MinimumRangeII
 * @version 0.1
 * @date 2023-04-01
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
#include "minimum_range_two.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::utils;
using namespace valhalla::arrays::minimum_range_two;

// Test Fixture Data Class
class MinimumRangeTwoData {
    std::vector<std::vector<int>> m_input;
    std::pair<int,int> m_expected;
public:
    MinimumRangeTwoData() = default;

    std::vector<std::vector<int>> const & get_input() { return m_input; }
    std::pair<int,int> const & get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const MinimumRangeTwoData &);
    friend std::istream& operator>>(std::istream&, MinimumRangeTwoData &);

};

std::ostream& operator<<(std::ostream& out, const MinimumRangeTwoData & data) {
    out << "MinimumRangeTwoData [ input=[";
    for (std::vector<int> values : data.m_input) {
        out << " [";
        for (int value : values)
            out << " " << value;
        out << " ]";
    } // for
    out << " ] expected=(" << data.m_expected.first << "," << data.m_expected.second << ") ]";

    return out;
}

std::istream& operator>>(std::istream& in, MinimumRangeTwoData &data) {
    ::loaders::matrix::matrixLoader<
      int,
      std::vector<int>,
      std::vector<std::vector<int>>,
      char,
      ::checkers::is_space_or<','>
    > inputLoader(data.m_input, '[', ']');
    in >> inputLoader;

    ::loaders::pairs::pairLoader<
      int,
      int,
      char,
      '(',
      ')',
      ::checkers::is_space_or<','>
    > expectedLoader(data.m_expected);
    in >> expectedLoader;

    return in;
}

// Test Fixture Class
class MinimumRangeTwoFixture :
    public testing::TestWithParam<MinimumRangeTwoData> {
};

// Parameterized Test Definition
TEST_P(MinimumRangeTwoFixture, MinimumRangeTwoTests) {
    MinimumRangeTwoData data = GetParam();

    Solution solution;

    std::pair<int,int> actual = solution.findMinimumRange(data.get_input());

    ASSERT_EQ(actual, data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(MinimumRangeTwoTests, MinimumRangeTwoFixture, testing::ValuesIn(
    Loader<MinimumRangeTwoData>()(find_path("arrays/data/minimum_range_two.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
