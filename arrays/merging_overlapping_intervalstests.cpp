/**
 * @file merging_overlapping_intervalstests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains tests to the problem https://www.techiedelight.com/?problem=MergingOverlappingIntervals
 * @version 0.1
 * @date 2023-05-15
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
#include "merging_overlapping_intervals.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::utils;
using namespace valhalla::arrays::merging_overlapping_intervals;

// Test Fixture Data Class
class MergingOverlappingIntervalsData {
    std::vector<std::pair<int,int>> m_input;
    std::set<std::pair<int,int>> m_expected;
public:
    MergingOverlappingIntervalsData() = default;

    std::vector<std::pair<int,int>> const & get_input() { return m_input; }
    std::set<std::pair<int,int>> const & get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const MergingOverlappingIntervalsData &);
    friend std::istream& operator>>(std::istream&, MergingOverlappingIntervalsData &);

};

std::ostream& operator<<(std::ostream& out, const MergingOverlappingIntervalsData & data) {
    out << "MergingOverlappingIntervalsData [ input=[";
    for (std::pair<int,int> value : data.m_input) {
        out << " (" << value.first << "," << value.second << ")";
    } // for
    out << " ], expected=[";
    for (std::pair<int,int> value : data.m_expected) {
        out << " (" << value.first << "," << value.second << ")";
    }
    out << " ] ]";

    return out;
}

std::istream& operator>>(std::istream& in, MergingOverlappingIntervalsData &data) {
    ::checkers::skip_spaces<char, ::checkers::is_space_or<','>> skipSpaces;

    skipSpaces(in);

    if (static_cast<char>(in.peek()) == '[') {
        in.get(); // read the '[' character
        skipSpaces(in);

        while (static_cast<char>(in.peek()) != ']') {
            std::pair<int,int> entry;

            ::loaders::pairs::pairLoader<
            int,
            int,
            char,
            '(',
            ')',
            ::checkers::is_space_or<','>
            > inputPairLoader(entry);
            in >> inputPairLoader;

            data.m_input.push_back(entry);

            skipSpaces(in);
        } // while

        in.get(); // read the ']' character

        skipSpaces(in);

        if (static_cast<char>(in.peek()) == '{') {
            in.get(); // read the '{' character
            skipSpaces(in);

            while (static_cast<char>(in.peek()) != '}') {
                std::pair<int,int> entry;

                ::loaders::pairs::pairLoader<
                int,
                int,
                char,
                '(',
                ')',
                ::checkers::is_space_or<','>
                > inputPairLoader(entry);
                in >> inputPairLoader;

                data.m_expected.insert(entry);

                skipSpaces(in);
            } // while

            in.get(); // read the '}' character

            skipSpaces(in);

            return in;
        } else {
            throw std::runtime_error("Invalid input format was encountered");
        } // else
    } else {
        throw std::runtime_error("Invalid input format was encountered");
    } // else
}

// Test Fixture Class
class MergingOverlappingIntervalsFixture :
    public testing::TestWithParam<MergingOverlappingIntervalsData> {
};

// Parameterized Test Definition
TEST_P(MergingOverlappingIntervalsFixture, MergingOverlappingIntervalsTests) {
    MergingOverlappingIntervalsData data = GetParam();

    Solution solution;

    std::vector<std::pair<int,int>> input = data.get_input();

    std::set<std::pair<int,int>> actual = solution.mergeIntervals(input);

    ASSERT_EQ(actual, data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(MergingOverlappingIntervalsTests, MergingOverlappingIntervalsFixture, testing::ValuesIn(
    Loader<MergingOverlappingIntervalsData>()(find_path("arrays/data/merging_overlapping_intervals.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
