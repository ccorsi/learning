/**
 * @file coin_change_problemtests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains tests for the problem https://www.techiedelight.com/?problem=CoinChangeProblem
 * @version 0.1
 * @date 2023-05-03
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
#include "coin_change_problem.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::utils;
using namespace valhalla::arrays::coin_change_problem;

// Test Fixture Data Class
class CoinChangeProblemData {
    std::vector<int> m_input;
    int m_target;
    int m_expected;
public:
    CoinChangeProblemData() = default;

    std::vector<int> const & get_input() { return m_input; }
    int get_target() { return m_target; }
    int get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const CoinChangeProblemData &);
    friend std::istream& operator>>(std::istream&, CoinChangeProblemData &);

};

std::ostream& operator<<(std::ostream& out, const CoinChangeProblemData & data) {
    out << "CoinChangeProblemData [ input=[";
    for (int value : data.m_input)
        out << " " << value;
    out << " ] target=" << data.m_target << " expected=" << data.m_expected << " ]";

    return out;
}

std::istream& operator>>(std::istream& in, CoinChangeProblemData &data) {
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
    > targetLoader(&data.m_target);
    in >> targetLoader;

    ::loaders::primitive::primitiveLoader<
      int,
      char,
      ::checkers::is_space_or<','>
    > expectedLoader(&data.m_expected);
    in >> expectedLoader;

    return in;
}

// Test Fixture Class
class CoinChangeProblemFixture :
    public testing::TestWithParam<CoinChangeProblemData> {
};

// Parameterized Test Definition
TEST_P(CoinChangeProblemFixture, CoinChangeProblemTests) {
    CoinChangeProblemData data = GetParam();

    Solution solution;

    int actual = solution.findMinCoins(data.get_input(), data.get_target());

    ASSERT_EQ(actual, data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(CoinChangeProblemTests, CoinChangeProblemFixture, testing::ValuesIn(
    Loader<CoinChangeProblemData>()(find_path("arrays/data/coin_change_problem.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
