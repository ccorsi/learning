/**
 * @file sort_arraytests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains tests to the problem https://www.techiedelight.com/?problem=SortArray
 * @version 0.1
 * @date 2023-04-05
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
#include "sort_array.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::utils;
using namespace valhalla::arrays::sort_array;

// Test Fixture Data Class
class SortArrayData {
    std::vector<int> m_input;
    std::vector<int> m_expected;
public:
    SortArrayData() = default;

    std::vector<int> const & get_input() { return m_input; }
    std::vector<int> const & get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const SortArrayData &);
    friend std::istream& operator>>(std::istream&, SortArrayData &);

};

std::ostream& operator<<(std::ostream& out, const SortArrayData & data) {
    out << "SortArrayData [ input=[";
    for (int value : data.m_input)
        out << " " << value;
    out << " ] expected=[";
    for (int value : data.m_expected)
        out << " " << value;
    out << " ] ]";

    return out;
}

std::istream& operator>>(std::istream& in, SortArrayData &data) {
    ::loaders::vectors::vectorLoader<
      int,
      std::vector<int>,
      char,
      ::checkers::is_space_or<','>
    > inputLoader(data.m_input,'[', ']');
    in >> inputLoader;

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
class SortArrayFixture :
    public testing::TestWithParam<SortArrayData> {
};

// Parameterized Test Definition
TEST_P(SortArrayFixture, SortArrayTests) {
    SortArrayData data = GetParam();

    Solution solution;

    std::vector<int> input = data.get_input();

    solution.sort(input);

    ASSERT_EQ(input, data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(SortArrayTests, SortArrayFixture, testing::ValuesIn(
    Loader<SortArrayData>()(find_path("arrays/data/sort_array.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
