/**
 * @file minimum_number_k_swapstests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains tests to the problem https://www.techiedelight.com/?problem=MinimumNumberKSwaps
 * @version 0.1
 * @date 2023-05-20
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
#include "minimum_number_k_swaps.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::utils;
using namespace valhalla::strings::minimum_number_k_swaps;

// Test Fixture Data Class
class MinimumNumberKSwapsData {
    std::string m_input, m_expected;
    int m_k;
public:
    MinimumNumberKSwapsData() = default;

    std::string const & get_input() { return m_input; }
    int get_k() { return m_k; }
    std::string const & get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const MinimumNumberKSwapsData &);
    friend std::istream& operator>>(std::istream&, MinimumNumberKSwapsData &);

};

std::ostream& operator<<(std::ostream& out, const MinimumNumberKSwapsData & data) {
    return out << "MinimumNumberKSwapsData [ input=\"" << data.m_input << "\" k=" << data.m_k
               << " expected=\"" << data.m_expected << "\" ]";
}

std::istream& operator>>(std::istream& in, MinimumNumberKSwapsData &data) {
    ::loaders::primitive::primitiveLoader<
      std::string,
      char,
      ::checkers::is_space_or<','>
    > inputLoader(&data.m_input);
    in >> inputLoader;

    ::loaders::primitive::primitiveLoader<
      int,
      char,
      ::checkers::is_space_or<','>
    > kLoader(&data.m_k);
    in >> kLoader;

    ::loaders::primitive::primitiveLoader<
      std::string,
      char,
      ::checkers::is_space_or<','>
    > expectedLoader(&data.m_expected);
    in >> expectedLoader;

    return in;
}

// Test Fixture Class
class MinimumNumberKSwapsFixture :
    public testing::TestWithParam<MinimumNumberKSwapsData> {
};

// Parameterized Test Definition
TEST_P(MinimumNumberKSwapsFixture, MinimumNumberKSwapsTests) {
    MinimumNumberKSwapsData data = GetParam();

    Solution solution;

    std::string actual = solution.findMinNumber(data.get_input(), data.get_k());

    ASSERT_EQ(actual, data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(MinimumNumberKSwapsTests, MinimumNumberKSwapsFixture, testing::ValuesIn(
    Loader<MinimumNumberKSwapsData>()(find_path("strings/data/minimum_number_k_swaps.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
