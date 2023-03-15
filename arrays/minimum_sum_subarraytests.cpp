/**
 * @file minimum_sum_subarraytests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains tests for the problem https://www.techiedelight.com/?problem=MinimumSumSubarray
 * @version 0.1
 * @date 2023-03-14
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
#include "minimum_sum_subarray.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::utils;
using namespace valhalla::arrays::minimum_sum_subarray;

// Test Fixture Data Class
class MinimumSumSubarrayData {
    std::vector<int> m_input;
    int m_k;
    std::vector<int> m_expected;
public:
    MinimumSumSubarrayData() = default;

    std::vector<int> const & get_input() { return m_input; }
    int get_k() { return m_k; }
    std::vector<int> const & get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const MinimumSumSubarrayData &);
    friend std::istream& operator>>(std::istream&, MinimumSumSubarrayData &);

};

std::ostream& operator<<(std::ostream& out, const MinimumSumSubarrayData & data) {
    out << "MinimumSumSubarrayData [ input=[";
    for (int value : data.m_input)
        out << " " << value;
    out << " ] k=" << data.m_k << " expected=[";
    for (int value : data.m_expected)
        out << " " << value;
    out << " ] ]";

    return out;
}

std::istream& operator>>(std::istream& in, MinimumSumSubarrayData &data) {
    ::vectors::vectorLoader<int, std::vector<int>, char, ::checkers::is_space_or<','>> inputLoader(data.m_input, '[', ']');
    in >> inputLoader;
    in >> data.m_k;
    ::vectors::vectorLoader<int, std::vector<int>, char, ::checkers::is_space_or<','>> expectedLoader(data.m_expected, '[', ']');
    in >> expectedLoader;

    return in;
}

// Test Fixture Class
class MinimumSumSubarrayFixture :
    public testing::TestWithParam<MinimumSumSubarrayData> {
};

// Parameterized Test Definition
TEST_P(MinimumSumSubarrayFixture, MinimumSumSubarrayTests) {
    MinimumSumSubarrayData data = GetParam();

    Solution solution;

    std::vector<int> actual = solution.findMinSumSubarray(data.get_input(), data.get_k());

    ASSERT_EQ(actual, data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(MinimumSumSubarrayTests, MinimumSumSubarrayFixture, testing::ValuesIn(
    Loader<MinimumSumSubarrayData>()(find_path("arrays/data/minimum_sum_subarray.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
