/**
 * @file sort_with_duplicatestests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains tests to the problem https://www.techiedelight.com/?problem=SortWithDuplicates
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
#include "sort_with_duplicates.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::utils;
using namespace valhalla::arrays::sort_with_duplicates;

// Test Fixture Data Class
class SortWithDuplicatesData {
    std::vector<int> m_input;
    std::vector<int> m_expected;
public:
    SortWithDuplicatesData() = default;

    std::vector<int> const & get_input() { return m_input; }
    std::vector<int> const & get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const SortWithDuplicatesData &);
    friend std::istream& operator>>(std::istream&, SortWithDuplicatesData &);

};

std::ostream& operator<<(std::ostream& out, const SortWithDuplicatesData & data) {
    out << "SortWithDuplicatesData [ input=[";
    for (int value : data.m_input)
        out << " " << value;
    out << " ] expected=[";
    for (int value : data.m_expected)
        out << " " << value;
    out << " ] ]";

    return out;
}

std::istream& operator>>(std::istream& in, SortWithDuplicatesData &data) {
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
class SortWithDuplicatesFixture :
    public testing::TestWithParam<SortWithDuplicatesData> {
};

// Parameterized Test Definition
TEST_P(SortWithDuplicatesFixture, SortWithDuplicatesTests) {
    SortWithDuplicatesData data = GetParam();

    Solution solution;

    std::vector<int> input = data.get_input();

    solution.sort(input);

    ASSERT_EQ(input, data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(SortWithDuplicatesTests, SortWithDuplicatesFixture, testing::ValuesIn(
    Loader<SortWithDuplicatesData>()(find_path("arrays/data/sort_with_duplicates.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
