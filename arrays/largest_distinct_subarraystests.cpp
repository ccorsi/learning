/**
 * @file largest_distinct_subarraystests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains tests to the problem https://www.techiedelight.com/?problem=LargestDistinctSubarrays
 * @version 0.1
 * @date 2023-03-26
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
#include "largest_distinct_subarrays.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::utils;
using namespace valhalla::arrays::largest_distinct_subarrays;

// Test Fixture Data Class
class LargestDistinctSubarraysData {
    std::vector<int> m_input;
    std::set<std::vector<int>> m_expected;
public:
    LargestDistinctSubarraysData() = default;

    std::vector<int> const & get_input() { return m_input; }
    std::set<std::vector<int>> const & get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const LargestDistinctSubarraysData &);
    friend std::istream& operator>>(std::istream&, LargestDistinctSubarraysData &);

};

std::ostream& operator<<(std::ostream& out, const LargestDistinctSubarraysData & data) {
    out << "LargestDistinctSubarraysData [ input=[";
    for (int value : data.m_input)
        out << " " << value;
    out << " ] expected={";
    for (std::vector<int> values : data.m_expected) {
        out << " [";
        for (int value : values)
            out << " " << value;
        out << " ]";
    } // for
    out << " } ]";

    return out;
}

std::istream& operator>>(std::istream& in, LargestDistinctSubarraysData &data) {
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
        in.get(); // read '{' character
        skipSpace(in);

        while (static_cast<char>(in.peek()) != '}') {
            std::vector<int> expected;

            ::loaders::vectors::vectorLoader<
                int,
                std::vector<int>,
                char,
                ::checkers::is_space_or<','>
            > expectedLoader(expected, '[', ']');
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
class LargestDistinctSubarraysFixture :
    public testing::TestWithParam<LargestDistinctSubarraysData> {
};

// Parameterized Test Definition
TEST_P(LargestDistinctSubarraysFixture, LargestDistinctSubarraysTests) {
    LargestDistinctSubarraysData data = GetParam();

    Solution solution;

    std::set<std::vector<int>> actual = solution.findDistinctSubarrays(data.get_input());

    ASSERT_EQ(actual, data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(LargestDistinctSubarraysTests, LargestDistinctSubarraysFixture, testing::ValuesIn(
    Loader<LargestDistinctSubarraysData>()(find_path("arrays/data/largest_distinct_subarrays.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
