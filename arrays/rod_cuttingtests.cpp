/**
 * @file rod_cuttingtests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains tests to the problem https://www.techiedelight.com/?problem=RodCutting
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
#include "rod_cutting.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::utils;
using namespace valhalla::arrays::rod_cutting;

// Test Fixture Data Class
class RodCuttingData {
    std::vector<int> m_input;
    int m_n, m_expected;
public:
    RodCuttingData() = default;

    std::vector<int> const & get_input() { return m_input; }
    int get_n() { return m_n; }
    int get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const RodCuttingData &);
    friend std::istream& operator>>(std::istream&, RodCuttingData &);

};

std::ostream& operator<<(std::ostream& out, const RodCuttingData & data) {
    out << "RodCuttingData [ input=[";
    for (int value : data.m_input) {
        out << " " << value;
    }
    out << " ] n=" << data.m_n << " expect=" << data.m_expected << " ]";

    return out;
}

std::istream& operator>>(std::istream& in, RodCuttingData &data) {
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
    > nLoader(&data.m_n);
    in >> nLoader;

    ::loaders::primitive::primitiveLoader<
      int,
      char,
      ::checkers::is_space_or<','>
    > expectedLoader(&data.m_expected);
    in >> expectedLoader;

    return in;
}

// Test Fixture Class
class RodCuttingFixture :
    public testing::TestWithParam<RodCuttingData> {
};

// Parameterized Test Definition
TEST_P(RodCuttingFixture, RodCuttingTests) {
    RodCuttingData data = GetParam();

    Solution solution;

    int actual = solution.findMaxProfit(data.get_input(), data.get_n());

    ASSERT_EQ(actual, data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(RodCuttingTests, RodCuttingFixture, testing::ValuesIn(
    Loader<RodCuttingData>()(find_path("arrays/data/rod_cutting.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
