/**
 * @file k_sum_subarray_twotests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains tests to the problem https://www.techiedelight.com/?problem=KSumSubarrayII
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
#include "k_sum_subarray_two.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::utils;
using namespace valhalla::arrays::k_sum_subarray_two;

// Test Fixture Data Class
class KSumSubarrayTwoData {
    std::vector<int> m_input;
    int m_k;
    std::set<std::vector<int>> m_expected;
public:
    KSumSubarrayTwoData() = default;

    std::vector<int> const & get_input() { return m_input; }
    int get_k() { return m_k; }
    std::set<std::vector<int>> const & get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const KSumSubarrayTwoData &);
    friend std::istream& operator>>(std::istream&, KSumSubarrayTwoData &);

};

std::ostream& operator<<(std::ostream& out, const KSumSubarrayTwoData & data) {
    out << "KSumSubarrayTwoData [ input=[";
    for (int value : data.m_input)
        out << " " << value;
    out << " ] k=" << data.m_k << " expected={";
    for (std::vector<int> values : data.m_expected) {
        out << " [";
        for (int value : values)
            out << " " << value;
        out << " ]";
    } // for
    out << " } ]";

    return out;
}

std::istream& operator>>(std::istream& in, KSumSubarrayTwoData &data) {
    ::vectors::vectorLoader<
        int,
        std::vector<int>,
        char,
        ::checkers::is_space_or<','>
    > inputLoader(data.m_input, '[', ']');
    in >> inputLoader;

    in >> data.m_k;
    std::string line;
    std::getline(in, line);

    ::checkers::is_space skip;
    while (skip(in.peek())) in.get();

    if (static_cast<char>(in.peek()) == '{') {
        std::getline(in, line); // read '{' line
        while (static_cast<char>(in.peek()) != '}') {
            std::vector<int> expect;
            ::vectors::vectorLoader<
                int,
                std::vector<int>,
                char,
                ::checkers::is_space_or<','>
            > expectLoader(expect, '[', ']');
            in >> expectLoader;
            data.m_expected.insert(expect);
        } // while
        std::getline(in, line); // read '}' line
        return in;
    } // if

    throw std::runtime_error("Invalid input format");
}

// Test Fixture Class
class KSumSubarrayTwoFixture :
    public testing::TestWithParam<KSumSubarrayTwoData> {
};

// Parameterized Test Definition
TEST_P(KSumSubarrayTwoFixture, KSumSubarrayTwoTests) {
    KSumSubarrayTwoData data = GetParam();

    Solution solution;

    std::set<std::vector<int>> actual = solution.getAllSubarrays(data.get_input(), data.get_k());

    ASSERT_EQ(actual, data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(KSumSubarrayTwoTests, KSumSubarrayTwoFixture, testing::ValuesIn(
    Loader<KSumSubarrayTwoData>()(find_path("arrays/data/k_sum_subarray_two.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
