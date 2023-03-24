/**
 * @file minimum_absolute_differencetests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains tests to the problem https://www.techiedelight.com/?problem=MinimumAbsoluteDifference
 * @version 0.1
 * @date 2023-03-22
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
#include "minimum_absolute_difference.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::utils;
using namespace valhalla::arrays::minimum_absolute_difference;

// Test Fixture Data Class
class MinimumAbsoluteDifferenceData {
    std::vector<int> m_input;
    int m_x, m_y;
    int m_expected;
public:
    MinimumAbsoluteDifferenceData() = default;

    std::vector<int> const & get_input() { return m_input; }
    int get_x_input() { return m_x; }
    int get_y_input() { return m_y; }
    int get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const MinimumAbsoluteDifferenceData &);
    friend std::istream& operator>>(std::istream&, MinimumAbsoluteDifferenceData &);

};

std::ostream& operator<<(std::ostream& out, const MinimumAbsoluteDifferenceData & data) {
    out << "MinimumAbsoluteDifferenceData [ input=[";
    for (int value : data.m_input)
        out  << " " << value;
    out << " ] x=" << data.m_x << " y=" << data.m_y << " ]";

    return out;
}

std::istream& operator>>(std::istream& in, MinimumAbsoluteDifferenceData &data) {
    ::loaders::vectors::vectorLoader<
        int,
        std::vector<int>,
        char,
        ::checkers::is_space_or<','>
    > inputLoader(data.m_input, '[', ']');
    in >> inputLoader;

    ::checkers::skip_spaces<char, ::checkers::is_space_or<','>> skipSpace;

    skipSpace(in);
    in >> data.m_x;

    skipSpace(in);
    in >> data.m_y;

    skipSpace(in);
    in >> data.m_expected;

    skipSpace(in);

    return in;
}

// Test Fixture Class
class MinimumAbsoluteDifferenceFixture :
    public testing::TestWithParam<MinimumAbsoluteDifferenceData> {
};

// Parameterized Test Definition
TEST_P(MinimumAbsoluteDifferenceFixture, MinimumAbsoluteDifferenceTests) {
    MinimumAbsoluteDifferenceData data = GetParam();

    Solution solution;

    int actual = solution.findDifference(data.get_input(), data.get_x_input(), data.get_y_input());

    ASSERT_EQ(actual, data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(MinimumAbsoluteDifferenceTests, MinimumAbsoluteDifferenceFixture, testing::ValuesIn(
    Loader<MinimumAbsoluteDifferenceData>()(find_path("arrays/data/minimum_absolute_difference.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
