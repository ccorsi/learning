/**
 * @file search_sorted_arraytests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains tests for the problem https://www.techiedelight.com/?problem=SearchSortedArray
 * @version 0.1
 * @date 2023-02-20
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include <iostream>
#include <string>

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "paths.h"
#include "loader.h"
#include "search_sorted_array.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::arrays::search_sorted_array;
using testing::AnyOfArray;

// Test Fixture Data Class
class SearchSortedArrayData {
    std::vector<int> m_input;
    int m_target;
    std::vector<int> m_expected;
public:
    SearchSortedArrayData() = default;
    SearchSortedArrayData(std::vector<int> input, int target, std::vector<int> expected) : m_input(input), m_target(target), m_expected(expected) {}

    std::vector<int> const & get_input() { return m_input; }
    int get_target() { return m_target; }
    std::vector<int> const & get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const SearchSortedArrayData &);
    friend std::istream& operator>>(std::istream&, SearchSortedArrayData &);

};

std::ostream& operator<<(std::ostream& out, const SearchSortedArrayData & data) {
    out << "SearchSortedArrayData [ input=[";
    for (int value : data.m_input)
        out << " " << value;
    out << " ], target=" << data.m_target << ", expected=[";
    for (int value : data.m_expected)
        out << " " << value;
    out << " ] ]";

    return out;
}

std::istream& operator>>(std::istream& in, SearchSortedArrayData &data) {
    std::string line;
    std::getline(in, line);
    if (line == "[") {
        std::getline(in, line);
        while (line != "]") {
            data.m_input.push_back(std::atoi(line.c_str()));
            std::getline(in, line); // read the end of line
        } // while
    } // if
    in >> data.m_target;
    std::getline(in, line); // read the end of line
    std::getline(in, line); // read the next line
    if (line == "[") {
        std::getline(in, line);
        while (line != "]") {
            data.m_expected.push_back(std::atoi(line.c_str()));
            std::getline(in, line); // read the end of line
        } // while
    } // if

    return in;
}

// Test Fixture Class
class SearchSortedArrayFixture :
    public testing::TestWithParam<SearchSortedArrayData> {
};

// Parameterized Test Definition
TEST_P(SearchSortedArrayFixture, SearchSortedArrayTests) {
    SearchSortedArrayData data = GetParam();

    Solution solution;

    int actual = solution.findIndex(data.get_input(), data.get_target());

    ASSERT_THAT(actual, AnyOfArray(data.get_expected()));
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(SearchSortedArrayTests, SearchSortedArrayFixture, testing::ValuesIn(
    Loader<SearchSortedArrayData>()(find_path("arrays/data/search_sorted_array.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
