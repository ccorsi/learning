/**
 * @file longest_bitonic_subarraytests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief
 * @version 0.1
 * @date 2023-02-04
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include <iostream>

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "longest_bitonic_subarray.h"
#include "contains_one_of.h"

using namespace valhalla::arrays::longest_bitonic_subarray;
using namespace valhalla::utils::testing;

// Test Fixture Data Class
class LongestBitonicSubarrayData {
    std::vector<int> m_input;
    std::vector<std::vector<int>> m_expected;
public:
    LongestBitonicSubarrayData() = default;
    LongestBitonicSubarrayData(std::vector<int> input, std::vector<std::vector<int>> expected) : m_input(input), m_expected(expected) {}

    std::vector<int> const &get_input() { return m_input; }
    std::vector<std::vector<int>> const &get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const LongestBitonicSubarrayData &);
};

std::ostream& operator<<(std::ostream& out, const LongestBitonicSubarrayData &value) {
    out << "LongestBitonicSubarrayData [ input=[";
    for (int v : value.m_input)
        out << " " << v;
    out << " ], expected= [";
    for (std::vector<int> values : value.m_expected) {
        out << " [";
        for (int v : values)
            out << " " << v;
        out << " ]";
    }
    out << " ] ]";

    return out;
}

// Test Fixture Class
class LongestBitonicSubarrayFixture :
    public testing::TestWithParam<LongestBitonicSubarrayData> {
};

TEST_P(LongestBitonicSubarrayFixture, LongestBitonicSubarrayTests) {
    LongestBitonicSubarrayData data = GetParam();

    Solution solution;

    std::vector<int> actual = solution.findBitonicSubarray(data.get_input());

    ASSERT_TRUE(ContainsOneOf<int>(data.get_expected())(actual));

}

INSTANTIATE_TEST_SUITE_P(LongestBitonicSubarrayTests, LongestBitonicSubarrayFixture, testing::Values(
    LongestBitonicSubarrayData({}, {{}}),
    LongestBitonicSubarrayData({3, 5, 8, 4, 5, 9, 10, 8, 5, 3, 4},{{4, 5, 9, 10, 8, 5, 3}}),
    LongestBitonicSubarrayData({-5, -1, 0, 2, 1, 6, 5, 4, 2}, {{-5, -1, 0, 2, 1}, {1, 6, 5, 4, 2}}),
    LongestBitonicSubarrayData({1, 2, 3, 4, 5}, {{1, 2, 3, 4, 5}}),
    LongestBitonicSubarrayData({5, 4, 3, 2, 1}, {{5, 4, 3, 2, 1}})
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
