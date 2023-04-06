/**
 * @file longest_consecutive_subsequencetests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains the tests to the problem https://www.techiedelight.com/?problem=LongestConsecutiveSubsequence
 * @version 0.1
 * @date 2023-04-01
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
#include "longest_consecutive_subsequence.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::utils;
using namespace valhalla::arrays::longest_consecutive_subsequence;

// Test Fixture Data Class
class LongestConsecutiveSubsequenceData {
    std::vector<int> m_input;
    int m_expected;
public:
    LongestConsecutiveSubsequenceData() = default;

    std::vector<int> const & get_input() { return m_input; }
    int get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const LongestConsecutiveSubsequenceData &);
    friend std::istream& operator>>(std::istream&, LongestConsecutiveSubsequenceData &);

};

std::ostream& operator<<(std::ostream& out, const LongestConsecutiveSubsequenceData & data) {
    out << "LongestConsecutiveSubsequenceData [ input=[";
    for (int value : data.m_input)
        out << " " << value;
    out << " ] expected=" << data.m_expected << " ]";

    return out;
}

std::istream& operator>>(std::istream& in, LongestConsecutiveSubsequenceData &data) {
    ::loaders::vectors::vectorLoader<
      int,
      std::vector<int>,
      char,
      ::checkers::is_space_or<','>
    > inputLoader(data.m_input,'[', ']');
    in >> inputLoader;

    ::checkers::skip_spaces<char, ::checkers::is_space_or<','>> skipSpace;

    skipSpace(in);
    in >> data.m_expected;
    skipSpace(in);

    return in;
}

// Test Fixture Class
class LongestConsecutiveSubsequenceFixture :
    public testing::TestWithParam<LongestConsecutiveSubsequenceData> {
};

// Parameterized Test Definition
TEST_P(LongestConsecutiveSubsequenceFixture, LongestConsecutiveSubsequenceTests) {
    LongestConsecutiveSubsequenceData data = GetParam();

    Solution solution;

    std::vector<int> input = data.get_input();

    int actual = solution.findMaxLenSubseq(input);

    ASSERT_EQ(actual, data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(LongestConsecutiveSubsequenceTests, LongestConsecutiveSubsequenceFixture, testing::ValuesIn(
    Loader<LongestConsecutiveSubsequenceData>()(find_path("arrays/data/longest_consecutive_subsequence.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
