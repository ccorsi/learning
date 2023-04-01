/**
 * @file sorted_triplettests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains tests to the problem https://www.techiedelight.com/?problem=SortedTriplet
 * @version 0.1
 * @date 2023-03-28
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
#include "sorted_triplet.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::utils;
using namespace valhalla::arrays::sorted_triplet;

// Test Fixture Data Class
class SortedTripletData {
    std::vector<int> m_input;
    std::set<std::tuple<int,int,int>> m_expected;

public:
    SortedTripletData() = default;

    std::vector<int> const & get_input() { return m_input; }
    std::set<std::tuple<int,int,int>> const & get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const SortedTripletData &);
    friend std::istream& operator>>(std::istream&, SortedTripletData &);

};

std::ostream& operator<<(std::ostream& out, const SortedTripletData & data) {
    out << "SortedTripletData [ input=[";
    for (int value : data.m_input)
        out << " " << value;
    out << " ] expected={";
    for (std::tuple<int,int,int> expected : data.m_expected)
        out << " (" << std::get<0>(expected) << "," << std::get<1>(expected)
            << "," << std::get<2>(expected) << ")";
    out << " } ]";

    return out;
}

std::istream& operator>>(std::istream& in, SortedTripletData &data) {
    ::loaders::vectors::vectorLoader<
      int,
      std::vector<int>,
      char,
      ::checkers::is_space_or<','>
    > inputLoader(data.m_input,'[', ']');
    in >> inputLoader;

    ::checkers::skip_spaces<char, ::checkers::is_space_or<','>> skipSpace;

    skipSpace(in);

    if (static_cast<char>(in.peek()) == '{') {
        in.get(); // read '{' character
        skipSpace(in);

        while (static_cast<char>(in.peek()) != '}') {
            std::tuple<int,int,int> expected;

            ::loaders::tuple::tupleTripletLoader<
              int,
              int,
              int,
              char,
              '(',
              ')',
              ::checkers::is_space_or<','>
            > expectedLoader(expected);
            in >> expectedLoader;

            data.m_expected.insert(expected);
            skipSpace(in);
        } // while
        in.get(); // read '}' character
        skipSpace(in);

        return in;
    } // if

    throw std::runtime_error("Invalid input format");
}

// Test Fixture Class
class SortedTripletFixture :
    public testing::TestWithParam<SortedTripletData> {
};

// Parameterized Test Definition
TEST_P(SortedTripletFixture, SortedTripletTests) {
    SortedTripletData data = GetParam();

    Solution solution;

    std::tuple<int,int,int> actual = solution.findSortedTriplet(data.get_input());

    ASSERT_THAT(actual, ::testing::AnyOfArray(data.get_expected()));
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(SortedTripletTests, SortedTripletFixture, testing::ValuesIn(
    Loader<SortedTripletData>()(find_path("arrays/data/sorted_triplet.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
