/**
 * @file non_overlapping_pairstests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains tests to the problem https://www.techiedelight.com/?problem=NonOverlappingPairs
 * @version 0.1
 * @date 2023-03-27
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
#include "non_overlapping_pairs.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::utils;
using namespace valhalla::arrays::non_overlapping_pairs;

// Test Fixture Data Class
class NonOverlappingPairsData {
    std::vector<int> m_input;
    std::set<std::set<std::pair<int,int>>> m_expected;
public:
    NonOverlappingPairsData() = default;

    std::vector<int> const & get_input() { return m_input; }
    std::set<std::set<std::pair<int,int>>> const & get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const NonOverlappingPairsData &);
    friend std::istream& operator>>(std::istream&, NonOverlappingPairsData &);

};

std::ostream& operator<<(std::ostream& out, const NonOverlappingPairsData & data) {
    out << "NonOverlappingPairsData [ input=[";
    for (int value : data.m_input)
        out << " " << value;
    out << " ] expected={";
    for (std::set<std::pair<int,int>> values : data.m_expected) {
        out << " {";
        for (std::pair<int,int> value : values) {
            out << " (" << value.first << "," << value.second << ")";
        } // for
        out << " }";
    } // for
    out << " } ]";

    return out;
}

std::istream& operator>>(std::istream& in, NonOverlappingPairsData &data) {
    ::loaders::vectors::vectorLoader<
        int,
        std::vector<int>,
        char,
        ::checkers::is_space_or<','>
    > inputLoader(data.m_input, '[', ']');
    in >> inputLoader;

    ::checkers::skip_spaces<char, ::checkers::is_space_or<','>> skipSpace;

    skipSpace(in);

    if (static_cast<char>(in.peek()) == '{') {
        in.get(); // read the '{' character
        skipSpace(in);

        while (static_cast<char>(in.peek()) != '}') {
            if (static_cast<char>(in.peek() == '{')) {
                in.get(); // read the '{' character
                skipSpace(in);
                std::set<std::pair<int,int>> expected;

                while (static_cast<char>(in.peek()) != '}') {
                    std::pair<int,int> value;
                    ::pairs::pairLoader<int,int,char,'(', ')', ::checkers::is_space_or<','>> expectedLoader(value);
                    in >> expectedLoader;

                    expected.insert(value);
                    skipSpace(in);
                } // while
                in.get(); // read '}' character
                skipSpace(in);

                data.m_expected.insert(expected);
            } // if
        } // while
        in.get(); // read '}' character
        skipSpace(in);

        return in;
    } // if

    throw std::runtime_error("Invalid input format");
}

// Test Fixture Class
class NonOverlappingPairsFixture :
    public testing::TestWithParam<NonOverlappingPairsData> {
};

// Parameterized Test Definition
TEST_P(NonOverlappingPairsFixture, NonOverlappingPairsTests) {
    NonOverlappingPairsData data = GetParam();

    Solution solution;

    std::set<std::set<std::pair<int,int>>> actual = solution.findPairs(data.get_input());

    ASSERT_EQ(actual, data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(NonOverlappingPairsTests, NonOverlappingPairsFixture, testing::ValuesIn(
    Loader<NonOverlappingPairsData>()(find_path("arrays/data/non_overlapping_pairs.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
