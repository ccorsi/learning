/**
 * @file longest_increasing_subsequencetests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains tests to the problem https://www.techiedelight.com/?problem=LongestIncreasingSubsequence
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
#include "longest_increasing_subsequence.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::utils;
using namespace valhalla::arrays::longest_increasing_subsequence;

// Test Fixture Data Class
class LongestIncreasingSubsequenceData {
    std::vector<int> m_input;
    int m_expected;
public:
    LongestIncreasingSubsequenceData() = default;

    std::vector<int> const & get_input() { return m_input; }
    int get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const LongestIncreasingSubsequenceData &);
    friend std::istream& operator>>(std::istream&, LongestIncreasingSubsequenceData &);

};

std::ostream& operator<<(std::ostream& out, const LongestIncreasingSubsequenceData & data) {
    out << "LongestIncreasingSubsequenceData [ input=[";
    for (int value : data.m_input) {
        out << " " << value;
    } // for
    out << " ] expected=" << data.m_expected << " ]";

    return out;
}

std::istream& operator>>(std::istream& in, LongestIncreasingSubsequenceData &data) {
    ::loaders::vectors::vectorLoader<
      int,
      std::vector<int>,
      char,
      ::checkers::is_space_or<','>
    > inputLoader(data.m_input,'[', ']');
    in >> inputLoader;

    ::loaders::primitive::primitiveLoader<
      int,
      char,
      ::checkers::is_space_or<','>
    > expectedLoader(&data.m_expected);
    in >> expectedLoader;

    return in;
}

// Test Fixture Class
class LongestIncreasingSubsequenceFixture :
    public testing::TestWithParam<LongestIncreasingSubsequenceData> {
};

// Parameterized Test Definition
TEST_P(LongestIncreasingSubsequenceFixture, LongestIncreasingSubsequenceTests) {
    LongestIncreasingSubsequenceData data = GetParam();

    Solution solution;

    int actual = solution.findLISLength(data.get_input());

    ASSERT_EQ(actual, data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(LongestIncreasingSubsequenceTests, LongestIncreasingSubsequenceFixture, testing::ValuesIn(
    Loader<LongestIncreasingSubsequenceData>()(find_path("arrays/data/longest_increasing_subsequence.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
