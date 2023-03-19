/**
 * @file sort_array_single_swaptests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains tests to the problem https://www.techiedelight.com/?problem=SortArraySingleSwap
 * @version 0.1
 * @date 2023-03-18
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
#include "sort_array_single_swap.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::utils;
using namespace valhalla::arrays::sort_array_single_swap;

// Test Fixture Data Class
class SortArraySingleSwapData {
    std::vector<int> m_input;
    std::vector<int> m_expected;
public:
    SortArraySingleSwapData() = default;

    std::vector<int> const & get_input() { return m_input; }
    std::vector<int> const & get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const SortArraySingleSwapData &);
    friend std::istream& operator>>(std::istream&, SortArraySingleSwapData &);

};

std::ostream& operator<<(std::ostream& out, const SortArraySingleSwapData & data) {
    out << "SortArraySingleSwapData [ input=[";
    for(int value : data.m_input)
        out << " " << value;
    out << " ] expected=[";
    for (int value : data.m_expected)
        out << " " << value;
    out << " ] ]";

    return out;
}

std::istream& operator>>(std::istream& in, SortArraySingleSwapData &data) {
    ::loaders::vectors::vectorLoader<
        int,
        std::vector<int>,
        char,
        ::checkers::is_space_or<','>
    > inputLoader(data.m_input, '[', ']');
    in >> inputLoader;

    ::loaders::vectors::vectorLoader<
        int,
        std::vector<int>,
        char,
        ::checkers::is_space_or<','>
    > expectedLoader(data.m_expected, '[', ']');
    in >> expectedLoader;

    return in;
}

// Test Fixture Class
class SortArraySingleSwapFixture :
    public testing::TestWithParam<SortArraySingleSwapData> {
};

// Parameterized Test Definition
TEST_P(SortArraySingleSwapFixture, SortArraySingleSwapTests) {
    SortArraySingleSwapData data = GetParam();

    Solution solution;

    std::vector<int> actual(data.get_input());

    solution.sortArray(actual);

    ASSERT_EQ(actual, data.get_expected());

}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(SortArraySingleSwapTests, SortArraySingleSwapFixture, testing::ValuesIn(
    Loader<SortArraySingleSwapData>()(find_path("arrays/data/sort_array_single_swap.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
