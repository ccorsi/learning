/**
 * @file search_nearly_sorted_arraytests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief These are tests for the problem https://www.techiedelight.com/?problem=SearchNearlySortedArray
 * @version 0.1
 * @date 2023-02-21
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include <iostream>

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "paths.h"
#include "loader.h"
#include "search_nearly_sorted_array.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::arrays::search_nearly_sorted_array;
using testing::AnyOfArray;

// Test Fixture Data Class
class SearchNearlySortedArrayData {
    std::vector<int> m_input;
    int m_target;
    std::vector<int> m_expected;
public:
    SearchNearlySortedArrayData() = default;

    std::vector<int> const & get_input() { return m_input; }
    int get_target() { return m_target; }
    std::vector<int> const & get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const SearchNearlySortedArrayData &);
    friend std::istream& operator>>(std::istream&, SearchNearlySortedArrayData &);

};

std::ostream& operator<<(std::ostream& out, const SearchNearlySortedArrayData & data) {
    out << "SearchNearlySortedArrayData [ input=[";
    for (int value : data.m_input)
        out << " " << value;
    out << " ] target=" << data.m_target << " expected=[";
    for (int value : data.m_expected)
        out << " " << value;
    out << " ]";
    out << " ]";

    return out;
}

std::istream& operator>>(std::istream& in, SearchNearlySortedArrayData &data) {
    std::string line;

    if (static_cast<char>(in.peek()) == '[') {
        char chr;
        in >> chr; // read the '[' character
        while (static_cast<char>(in.peek()) != ']') {
            int value;
            in >> value;
            data.m_input.push_back(value);
        } // while
        std::getline(in, line); // read ']' and end of line
    } // if

    in >> data.m_target;
    std::getline(in, line); // read end of line

    if (static_cast<char>(in.peek()) == '(') {
        char chr;
        in >> chr; // read the '(' character
        while (static_cast<char>(in.peek()) != ')') {
            int value;
            in >> value;
            data.m_expected.push_back(value);
        } // while
        std::getline(in, line);  // read the ')' character and end of line
    } // if

    return in;
}

// Test Fixture Class
class SearchNearlySortedArrayFixture :
    public testing::TestWithParam<SearchNearlySortedArrayData> {
};

// Parameterized Test Definition
TEST_P(SearchNearlySortedArrayFixture, SearchNearlySortedArrayTests) {
    SearchNearlySortedArrayData data = GetParam();

    Solution solution;

    int actual = solution.findIndex(data.get_input(), data.get_target());

    ASSERT_THAT(actual, AnyOfArray(data.get_expected()));
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(SearchNearlySortedArrayTests, SearchNearlySortedArrayFixture, testing::ValuesIn(
    Loader<SearchNearlySortedArrayData>()(find_path("arrays/data/search_nearly_sorted_array.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}