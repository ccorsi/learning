/**
 * @file maximum_product_subarraytests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains tests to the problem https://www.techiedelight.com/?problem=MaximumProductSubarray
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
#include "maximum_product_subarray.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::utils;
using namespace valhalla::arrays::maximum_product_subarray;

// Test Fixture Data Class
class MaximumProductSubarrayData {
    std::vector<int> m_input;
    int m_expected;
public:
    MaximumProductSubarrayData() = default;

    std::vector<int> const & get_input() { return m_input; }
    int get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const MaximumProductSubarrayData &);
    friend std::istream& operator>>(std::istream&, MaximumProductSubarrayData &);

};

std::ostream& operator<<(std::ostream& out, const MaximumProductSubarrayData & data) {
    out << "MaximumProductSubarrayData [ input=[";
    for (int value : data.m_input)
        out << " " << value;
    out << " ] expected=" << data.m_expected << " ]";

    return out;
}

std::istream& operator>>(std::istream& in, MaximumProductSubarrayData &data) {
    ::vectors::vectorLoader<int, std::vector<int>, char, checkers::is_space_or<','>> loader(data.m_input, '[', ']');

    in >> loader >> data.m_expected;

    std::string line;
    std::getline(in, line);

    return in;
}

// Test Fixture Class
class MaximumProductSubarrayFixture :
    public testing::TestWithParam<MaximumProductSubarrayData> {
};

// Parameterized Test Definition
TEST_P(MaximumProductSubarrayFixture, MaximumProductSubarrayTests) {
    MaximumProductSubarrayData data = GetParam();

    Solution solution;

    int actual = solution.findMaxProduct(data.get_input());

    ASSERT_EQ(actual, data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(MaximumProductSubarrayTests, MaximumProductSubarrayFixture, testing::ValuesIn(
    Loader<MaximumProductSubarrayData>()(find_path("arrays/data/maximum_product_subarray.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
