/**
 * @file maximum_product_subsettests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains tests to the problem https://www.techiedelight.com/?problem=MaximumProductSubset
 * @version 0.1
 * @date 2023-03-20
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
#include "maximum_product_subset.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::utils;
using namespace valhalla::arrays::maximum_product_subset;

// Test Fixture Data Class
class MaximumProductSubsetData {
    std::vector<int> m_input;
    int m_expected;
public:
    MaximumProductSubsetData() = default;

    std::vector<int> const & get_input() { return m_input; }
    int get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const MaximumProductSubsetData &);
    friend std::istream& operator>>(std::istream&, MaximumProductSubsetData &);

};

std::ostream& operator<<(std::ostream& out, const MaximumProductSubsetData & data) {
    out << "MaximumProductSubsetData [ input=[";
    for (int value : data.m_input)
        out << " " << value;
    out << " ] expected=" << data.m_expected << " ]";

    return out;
}

std::istream& operator>>(std::istream& in, MaximumProductSubsetData &data) {
    ::loaders::vectors::vectorLoader<
        int,
        std::vector<int>,
        char,
        ::checkers::is_space_or<','>
    > inputLoader(data.m_input, '[', ']');
    in >> inputLoader;

    in >> data.m_expected;

    ::checkers::is_space isSpace;

    // skip spaces
    while (isSpace(in.peek())) in.get();

    return in;
}

// Test Fixture Class
class MaximumProductSubsetFixture :
    public testing::TestWithParam<MaximumProductSubsetData> {
};

// Parameterized Test Definition
TEST_P(MaximumProductSubsetFixture, MaximumProductSubsetTests) {
    MaximumProductSubsetData data = GetParam();

    Solution solution;

    int actual = solution.findMaxProduct(data.get_input());

    ASSERT_EQ(actual, data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(MaximumProductSubsetTests, MaximumProductSubsetFixture, testing::ValuesIn(
    Loader<MaximumProductSubsetData>()(find_path("arrays/data/maximum_product_subset.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
