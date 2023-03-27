/**
 * @file maximum_sum_numbertests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains tests to the problem https://www.techiedelight.com/?problem=MaximumSumNumber
 * @version 0.1
 * @date 2023-03-26
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
#include "maximum_sum_number.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::utils;
using namespace valhalla::arrays::maximum_sum_number;

// Test Fixture Data Class
class MaximumSumNumberData {
    std::vector<int> m_input;
    std::pair<int,int> m_expected;
public:
    MaximumSumNumberData() = default;

    std::vector<int> const & get_input() { return m_input; }
    std::pair<int,int> const & get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const MaximumSumNumberData &);
    friend std::istream& operator>>(std::istream&, MaximumSumNumberData &);

};

std::ostream& operator<<(std::ostream& out, const MaximumSumNumberData & data) {
    out << "MaximumSumNumberData [ input=[";
    for (int value : data.m_input)
        out << " " << value;
    out << " ] expected=(" << data.m_expected.first << "," << data.m_expected.second << ") ]";

    return out;
}

std::istream& operator>>(std::istream& in, MaximumSumNumberData &data) {
    ::loaders::vectors::vectorLoader<
        int,
        std::vector<int>,
        char,
        ::checkers::is_space_or<','>
    > inputLoader(data.m_input, '[', ']');
    in >> inputLoader;

    ::loaders::pairs::pairLoader<int, int, char, '(', ')', ::checkers::is_space_or<','>> expectedLoader(data.m_expected);
    in >> expectedLoader;

    return in;
}

// Test Fixture Class
class MaximumSumNumberFixture :
    public testing::TestWithParam<MaximumSumNumberData> {
};

// Parameterized Test Definition
TEST_P(MaximumSumNumberFixture, MaximumSumNumberTests) {
    MaximumSumNumberData data = GetParam();

    Solution solution;

    std::vector<int> input(data.get_input());

    std::pair<int,int> actual = solution.constructMaxSumNumber(input);

    ASSERT_EQ(actual, data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(MaximumSumNumberTests, MaximumSumNumberFixture, testing::ValuesIn(
    Loader<MaximumSumNumberData>()(find_path("arrays/data/maximum_sum_number.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
