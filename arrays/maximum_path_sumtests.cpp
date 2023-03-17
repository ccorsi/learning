/**
 * @file maximum_path_sumtests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains tests to the problem https://www.techiedelight.com/?problem=MaximumPathSum
 * @version 0.1
 * @date 2023-03-15
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
#include "maximum_path_sum.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::utils;
using namespace valhalla::arrays::maximum_path_sum;

// Test Fixture Data Class
class MaximumPathSumData {
    std::vector<int> m_x_input;
    std::vector<int> m_y_input;
    int m_expected;
public:
    MaximumPathSumData() = default;

    std::vector<int> const & get_x_input() { return m_x_input; }
    std::vector<int> const & get_y_input() { return m_y_input; }
    int get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const MaximumPathSumData &);
    friend std::istream& operator>>(std::istream&, MaximumPathSumData &);

};

std::ostream& operator<<(std::ostream& out, const MaximumPathSumData & data) {
    out << "MaximumPathSumData [ X=[";
    for (int value : data.m_x_input)
        out << " " << value;
    out << " ] Y=[";
    for (int value : data.m_y_input)
        out << " " << value;
    out << " ] expected=" << data.m_expected << " ]";

    return out;
}

std::istream& operator>>(std::istream& in, MaximumPathSumData &data) {
    ::loaders::vectors::vectorLoader<
        int,
        std::vector<int>,
        char,
        ::checkers::is_space_or<','>
    > xLoader(data.m_x_input, '[', ']');
    in >> xLoader;

    ::loaders::vectors::vectorLoader<
        int,
        std::vector<int>,
        char,
        ::checkers::is_space_or<','>
    > yLoader(data.m_y_input, '[', ']');
    in >> yLoader;

    in >> data.m_expected;
    std::string line;
    std::getline(in, line); // read the end of line

    return in;
}

// Test Fixture Class
class MaximumPathSumFixture :
    public testing::TestWithParam<MaximumPathSumData> {
};

// Parameterized Test Definition
TEST_P(MaximumPathSumFixture, MaximumPathSumTests) {
    MaximumPathSumData data = GetParam();

    Solution solution;

    int actual = solution.findMaxPathSum(data.get_x_input(), data.get_y_input());

    ASSERT_EQ(actual, data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(MaximumPathSumTests, MaximumPathSumFixture, testing::ValuesIn(
    Loader<MaximumPathSumData>()(find_path("arrays/data/maximum_path_sum.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
