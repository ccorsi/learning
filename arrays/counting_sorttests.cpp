/**
 * @file counting_sorttests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains tests to the problem https://www.techiedelight.com/?problem=CountingSort
 * @version 0.1
 * @date 2023-04-11
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
#include "counting_sort.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::utils;
using namespace valhalla::arrays::counting_sort;

// Test Fixture Data Class
class CountingSortData {
    std::vector<int> m_input;
    int m_k;
    std::vector<int> m_expected;
public:
    CountingSortData() = default;

    std::vector<int> const & get_input() { return m_input; }
    int get_k() { return m_k; }
    std::vector<int> const & get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const CountingSortData &);
    friend std::istream& operator>>(std::istream&, CountingSortData &);

};

std::ostream& operator<<(std::ostream& out, const CountingSortData & data) {
    out << "CountingSortData [ input=[";
    for (int value : data.m_input)
        out << " " << value;
    out << " ] k=" << data.m_k << " expected=[";
    for (int value : data.m_expected)
        out << " " << value;
    out << " ] ]";

    return out;
}

std::istream& operator>>(std::istream& in, CountingSortData &data) {
    ::loaders::vectors::vectorLoader<
      int,
      std::vector<int>,
      char,
      ::checkers::is_space_or<','>
    > inputLoader(data.m_input,'[', ']');
    in >> inputLoader;

    ::checkers::skip_spaces<char, ::checkers::is_space_or<','>> skipSpace;

    skipSpace(in);
    in >> data.m_k;
    skipSpace(in);

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
class CountingSortFixture :
    public testing::TestWithParam<CountingSortData> {
};

// Parameterized Test Definition
TEST_P(CountingSortFixture, CountingSortTests) {
    CountingSortData data = GetParam();

    Solution solution;

    std::vector<int> input = data.get_input();

    solution.sort(input, data.get_k());

    ASSERT_EQ(input, data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(CountingSortTests, CountingSortFixture, testing::ValuesIn(
    Loader<CountingSortData>()(find_path("arrays/data/counting_sort.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
