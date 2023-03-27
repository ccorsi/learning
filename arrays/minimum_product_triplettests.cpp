/**
 * @file minimum_product_triplettests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains tests to the problem https://www.techiedelight.com/?problem=MinimumProductTriplet
 * @version 0.1
 * @date 2023-03-27
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
#include "minimum_product_triplet.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::utils;
using namespace valhalla::arrays::minimum_product_triplet;

// Test Fixture Data Class
class MinimumProductTripletData {
    std::vector<int> m_input;
    int m_expected;
public:
    MinimumProductTripletData() = default;

    std::vector<int> const & get_input() { return m_input; }
    int get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const MinimumProductTripletData &);
    friend std::istream& operator>>(std::istream&, MinimumProductTripletData &);

};

std::ostream& operator<<(std::ostream& out, const MinimumProductTripletData & data) {
    out << "MinimumProductTripletData [ input=[";
    for (int value : data.m_input)
        out << " " << value;
    out << " ] expected=" << data.m_expected << " ]";

    return out;
}

std::istream& operator>>(std::istream& in, MinimumProductTripletData &data) {
    ::loaders::vectors::vectorLoader<
        int,
        std::vector<int>,
        char,
        ::checkers::is_space_or<','>
    > inputLoader(data.m_input, '[', ']');
    in >> inputLoader;

    ::checkers::skip_spaces<char, ::checkers::is_space_or<','>> skipSpace;

    skipSpace(in);
    in >> data.m_expected;
    skipSpace(in);

    return in;
}

// Test Fixture Class
class MinimumProductTripletFixture :
    public testing::TestWithParam<MinimumProductTripletData> {
};

// Parameterized Test Definition
TEST_P(MinimumProductTripletFixture, MinimumProductTripletTests) {
    MinimumProductTripletData data = GetParam();

    Solution solution;

    std::vector<int> input = data.get_input();

    int actual = solution.findMin(input);

    ASSERT_EQ(actual, data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(MinimumProductTripletTests, MinimumProductTripletFixture, testing::ValuesIn(
    Loader<MinimumProductTripletData>()(find_path("arrays/data/minimum_product_triplet.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
