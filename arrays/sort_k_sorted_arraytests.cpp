/**
 * @file sort_k_sorted_arraytests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains tests to the problem https://www.techiedelight.com/?problem=SortKSortedArray
 * @version 0.1
 * @date 2023-05-29
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
#include "sort_k_sorted_array.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::utils;
using namespace valhalla::arrays::sort_k_sorted_array;

// Test Fixture Data Class
class SortKSortedArrayData {
    std::vector<int> m_input;
    int m_k;
    std::vector<int> m_expected;
public:
    SortKSortedArrayData() = default;

    std::vector<int> const & get_input() { return m_input; }
    int get_k() { return m_k; }

    std::vector<int> const & get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const SortKSortedArrayData &);
    friend std::istream& operator>>(std::istream&, SortKSortedArrayData &);

};

std::ostream& operator<<(std::ostream& out, const SortKSortedArrayData & data) {
    out << "SortKSortedArrayData [ input=[";
    for (int value : data.m_input) {
        out << " " << value;
    }
    out << " ] k=" << data.m_k << " expected=[";
    for (int value : data.m_expected) {
        out << " " << value;
    }
    out << " ] ]";

    return out;
}

std::istream& operator>>(std::istream& in, SortKSortedArrayData &data) {
    ::loaders::vectors::vectorLoader<
      int,
      std::vector<int>,
      char,
      ::checkers::is_space_or<','>
    > inputLoader(data.m_input,'[', ']');
    in >> inputLoader;

    ::loaders::primitive::primitiveLoader<
      int,
      char,
      ::checkers::is_space_or<','>
    > kLoader(&data.m_k);
    in >> kLoader;

    ::loaders::vectors::vectorLoader<
      int,
      std::vector<int>,
      char,
      ::checkers::is_space_or<','>
    > expectedLoader(data.m_expected,'[', ']');
    in >> expectedLoader;

    return in;
}

// Test Fixture Class
class SortKSortedArrayFixture :
    public testing::TestWithParam<SortKSortedArrayData> {
};

// Parameterized Test Definition
TEST_P(SortKSortedArrayFixture, SortKSortedArrayTests) {
    SortKSortedArrayData data = GetParam();

    Solution solution;

    std::vector<int> input = data.get_input();

    solution.sortKSortedArray(input, data.get_k());

    ASSERT_EQ(input, data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(SortKSortedArrayTests, SortKSortedArrayFixture, testing::ValuesIn(
    Loader<SortKSortedArrayData>()(find_path("arrays/data/sort_k_sorted_array.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
