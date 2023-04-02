/**
 * @file minimum_rangetests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains tests to the problem https://www.techiedelight.com/?problem=MinimumRange
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
#include "minimum_range.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::utils;
using namespace valhalla::arrays::minimum_range;

// Test Fixture Data Class
class MinimumRangeData {
    std::vector<int> m_x_input, m_y_input, m_z_input;
    std::pair<int,int>  m_expected;
public:
    MinimumRangeData() = default;

    std::vector<int> const & get_x_input() { return m_x_input; }
    std::vector<int> const & get_y_input() { return m_y_input; }
    std::vector<int> const & get_z_input() { return m_z_input; }
    std::pair<int,int> const & get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const MinimumRangeData &);
    friend std::istream& operator>>(std::istream&, MinimumRangeData &);

};

std::ostream& operator<<(std::ostream& out, const MinimumRangeData & data) {
    out << "MinimumRangeData [ X=[";
    for (int value : data.m_x_input)
        out << " " << value;
    out << " ] Y=[";
    for (int value : data.m_y_input)
        out << " " << value;
    out << " ] Z=[";
    for (int value : data.m_z_input)
        out << " " << value;
    out << " ] expected=(" << data.m_expected.first << "," << data.m_expected.second << ") ]";

    return out;
}

std::istream& operator>>(std::istream& in, MinimumRangeData &data) {
    ::loaders::vectors::vectorLoader<
      int,
      std::vector<int>,
      char,
      ::checkers::is_space_or<','>
    > inputXLoader(data.m_x_input,'[', ']');
    in >> inputXLoader;

    ::loaders::vectors::vectorLoader<
      int,
      std::vector<int>,
      char,
      ::checkers::is_space_or<','>
    > inputYLoader(data.m_y_input,'[', ']');
    in >> inputYLoader;

    ::loaders::vectors::vectorLoader<
      int,
      std::vector<int>,
      char,
      ::checkers::is_space_or<','>
    > inputZLoader(data.m_z_input,'[', ']');
    in >> inputZLoader;

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
class MinimumRangeFixture :
    public testing::TestWithParam<MinimumRangeData> {
};

// Parameterized Test Definition
TEST_P(MinimumRangeFixture, MinimumRangeTests) {
    MinimumRangeData data = GetParam();

    Solution solution;

    std::pair<int,int> actual = solution.findMinRange(data.get_x_input(), data.get_y_input(), data.get_z_input());

    ASSERT_EQ(actual, data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(MinimumRangeTests, MinimumRangeFixture, testing::ValuesIn(
    Loader<MinimumRangeData>()(find_path("arrays/data/minimum_range.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
