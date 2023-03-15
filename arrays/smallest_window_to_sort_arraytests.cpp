/**
 * @file smallest_window_to_sort_arraytests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains tests to the problem https://www.techiedelight.com/?problem=SmallestWindowToSortArray
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
#include "smallest_window_to_sort_array.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::utils;
using namespace valhalla::arrays::smallest_window_to_sort_array;

// Test Fixture Data Class
class SmallestWindowToSortArrayData {
    std::vector<int> m_input;
    std::pair<int,int> m_expected;
public:
    SmallestWindowToSortArrayData() = default;

    std::vector<int> const & get_input() { return m_input; }
    std::pair<int,int> const & get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const SmallestWindowToSortArrayData &);
    friend std::istream& operator>>(std::istream&, SmallestWindowToSortArrayData &);

};

std::ostream& operator<<(std::ostream& out, const SmallestWindowToSortArrayData & data) {
    out << "SmallestWindowToSortArrayData [ input=[";
    for (int value : data.m_input)
        out << " " << value;
    out << " ] expected=(" << data.m_expected.first << "," << data.m_expected.second << ") ]";

    return out;
}

std::istream& operator>>(std::istream& in, SmallestWindowToSortArrayData &data) {
    ::loaders::vectors::vectorLoader<
        int,
        std::vector<int>,
        char,
        ::checkers::is_space_or<','>
    > loader(data.m_input, '[', ']');

    in >> loader;

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
class SmallestWindowToSortArrayFixture :
    public testing::TestWithParam<SmallestWindowToSortArrayData> {
};

// Parameterized Test Definition
TEST_P(SmallestWindowToSortArrayFixture, SmallestWindowToSortArrayTests) {
    SmallestWindowToSortArrayData data = GetParam();

    Solution solution;

    std::pair<int,int> actual = solution.findSmallestWindow(data.get_input());

    ASSERT_EQ(actual, data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(SmallestWindowToSortArrayTests, SmallestWindowToSortArrayFixture, testing::ValuesIn(
    Loader<SmallestWindowToSortArrayData>()(find_path("arrays/data/smallest_window_to_sort_array.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
