/**
 * @file longest_increasing_subsequence_twotests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains tests to the problem https://www.techiedelight.com/?problem=LongestIncreasingSubsequenceII
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
#include "longest_increasing_subsequence_two.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::utils;
using namespace valhalla::arrays::longest_increasing_subsequence_two;

// Test Fixture Data Class
class LongestIncreasingSubsequenceTwoData {
    std::vector<int> m_input;
    std::set<std::vector<int>> m_expected;
public:
    LongestIncreasingSubsequenceTwoData() = default;

    std::vector<int> const & get_input() { return m_input; }
    std::set<std::vector<int>> const & get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const LongestIncreasingSubsequenceTwoData &);
    friend std::istream& operator>>(std::istream&, LongestIncreasingSubsequenceTwoData &);

};

std::ostream& operator<<(std::ostream& out, const LongestIncreasingSubsequenceTwoData & data) {
    out << "LongestIncreasingSubsequenceTwoData [ input=[";
    for (int value : data.m_input) {
        out << " " << value;
    } // for
    out << " ] expected={";
    for (std::vector<int> values : data.m_expected) {
        out << " [";
        for (int value : values) {
            out << " " << value;
        } // for
        out << " ]";
    } // for
    out << " } ]";

    return out;
}

std::istream& operator>>(std::istream& in, LongestIncreasingSubsequenceTwoData &data) {
    ::loaders::vectors::vectorLoader<
      int,
      std::vector<int>,
      char,
      ::checkers::is_space_or<','>
    > inputLoader(data.m_input,'[', ']');
    in >> inputLoader;

    ::checkers::skip_spaces<char, ::checkers::is_space_or<','>> skipSpaces;

    skipSpaces(in);

    if (static_cast<char>(in.peek()) == '{') {
        in.get(); // read '{' character
        skipSpaces(in);

        while (static_cast<char>(in.peek()) != '}') {
            std::vector<int> elements;

            ::loaders::vectors::vectorLoader<
              int,
              std::vector<int>,
              char,
              ::checkers::is_space_or<','>
            > elementsLoader(elements,'[', ']');
            in >> elementsLoader;

            data.m_expected.insert(elements);
        } // while

        in.get(); // read '}' character
        skipSpaces(in);

        return in;
    } // if

    throw std::runtime_error("Invalid input format encountered");
}

// Test Fixture Class
class LongestIncreasingSubsequenceTwoFixture :
    public testing::TestWithParam<LongestIncreasingSubsequenceTwoData> {
};

// Parameterized Test Definition
TEST_P(LongestIncreasingSubsequenceTwoFixture, LongestIncreasingSubsequenceTwoTests) {
    LongestIncreasingSubsequenceTwoData data = GetParam();

    Solution solution;

    std::vector<int> actual = solution.findLIS(data.get_input());

    ASSERT_THAT(actual, ::testing::AnyOfArray(data.get_expected()));
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(LongestIncreasingSubsequenceTwoTests, LongestIncreasingSubsequenceTwoFixture, testing::ValuesIn(
    Loader<LongestIncreasingSubsequenceTwoData>()(find_path("arrays/data/longest_increasing_subsequence_two.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
