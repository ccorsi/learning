/**
 * @file k_sum_subarraytests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains tests to the problem https://www.techiedelight.com/?problem=KSumSubarray
 * @version 0.1
 * @date 2023-03-15
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
#include "k_sum_subarray.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::utils;
using namespace valhalla::arrays::k_sum_subarray;

// Test Fixture Data Class
class KSumSubarrayData {
    std::vector<int> m_input;
    int m_k;
    std::vector<std::vector<int>> m_expected;
public:
    KSumSubarrayData() = default;

    std::vector<int> const & get_input() { return m_input; }
    int get_k() { return m_k; }
    std::vector<std::vector<int>> const & get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const KSumSubarrayData &);
    friend std::istream& operator>>(std::istream&, KSumSubarrayData &);

};

std::ostream& operator<<(std::ostream& out, const KSumSubarrayData & data) {
    out << "KSumSubarrayData [ input=[";
    for (int value : data.m_input)
        out << " " << value;
    out << " ] k=" << data.m_k << " expected=[";
    for (std::vector<int> values : data.m_expected) {
        out << " [";
        for (int value : values)
            out << " " << value;
        out << " ]";
    } // for
    out << " ] ]";

    return out;
}

std::istream& operator>>(std::istream& in, KSumSubarrayData &data) {
    ::vectors::vectorLoader<int, std::vector<int>, char, ::checkers::is_space_or<','>> inputLoader(data.m_input, '[', ']');
    in >> inputLoader;

    in >> data.m_k;
    std::string line;
    std::getline(in, line); // read end of line

    ::matrix::matrixLoader<
        int,
        std::vector<int>,
        std::vector<std::vector<int>>,
        char,
        ::checkers::is_space_or<','>
    > expectedLoader(data.m_expected, '[', ']');
    in >> expectedLoader;

    return in;
}

// Test Fixture Class
class KSumSubarrayFixture :
    public testing::TestWithParam<KSumSubarrayData> {
};

// Parameterized Test Definition
TEST_P(KSumSubarrayFixture, KSumSubarrayTests) {
    KSumSubarrayData data = GetParam();

    Solution solution;

    std::vector<int> actual = solution.findSubarray(data.get_input(), data.get_k());

    std::vector<std::vector<int>> const & expected = data.get_expected();

    ASSERT_THAT(actual, ::testing::AnyOfArray(expected.begin(), expected.end()));
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(KSumSubarrayTests, KSumSubarrayFixture, testing::ValuesIn(
    Loader<KSumSubarrayData>()(find_path("arrays/data/k_sum_subarray.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
