/**
 * @file search_circular_arraytests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains the tests for the problem https://www.techiedelight.com/?problem=SearchCircularArray
 * @version 0.1
 * @date 2023-02-20
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
#include "search_circular_array.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::arrays::search_circular_array;

// Test Fixture Data Class
class SearchCircularArrayData {
    std::vector<int> m_input;
    int m_target;
    int m_expected;

public:
    SearchCircularArrayData() = default;

    std::vector<int> const & get_input() { return m_input; }
    int get_target() { return m_target; }
    int get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const SearchCircularArrayData &);
    friend std::istream& operator>>(std::istream&, SearchCircularArrayData &);

};

std::ostream& operator<<(std::ostream& out, const SearchCircularArrayData & data) {
    out << "SearchCircularArrayData [ input=[";
    for(int value : data.m_input)
        out << " " << value;
    out << " ] target=" << data.m_target << " expected=" << data.m_expected;
    out << " ]";

    return out;
}

std::istream& operator>>(std::istream& in, SearchCircularArrayData &data) {
    std::string line;
    std::getline(in, line);

    if (line == "[") {
        std::getline(in, line);
        while (line != "]") {
            data.m_input.push_back(std::atoi(line.c_str()));
            std::getline(in, line);
        } // while
    } // if
    in >> data.m_target;
    std::getline(in, line); // read end of line
    in >> data.m_expected;
    std::getline(in, line); // read end of line

    return in;
}

// Test Fixture Class
class SearchCircularArrayFixture :
    public testing::TestWithParam<SearchCircularArrayData> {
};

// Parameterized Test Definition
TEST_P(SearchCircularArrayFixture, SearchCircularArrayTests) {
    SearchCircularArrayData data = GetParam();

    Solution solution;

    int actual = solution.findIndex(data.get_input(), data.get_target());

    ASSERT_EQ(actual, data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(SearchCircularArrayTests, SearchCircularArrayFixture, testing::ValuesIn(
    Loader<SearchCircularArrayData>()(find_path("arrays/data/search_circular_array.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
