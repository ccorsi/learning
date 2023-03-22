/**
 * @file buy_and_sell_stock_twotests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains tests to the problem https://www.techiedelight.com/?problem=BuyAndSellStockII
 * @version 0.1
 * @date 2023-03-21
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include <iostream>
#include <exception>

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "paths.h"
#include "loaders.h"
#include "buy_and_sell_stock_two.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::utils;
using namespace valhalla::arrays::buy_and_sell_stock_two;

// Test Fixture Data Class
class BuyAndSellStockTwoData {
    std::vector<int> m_input;
    int m_expected;
public:
    BuyAndSellStockTwoData() = default;

    std::vector<int> const & get_input() { return m_input; }
    int get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const BuyAndSellStockTwoData &);
    friend std::istream& operator>>(std::istream&, BuyAndSellStockTwoData &);

};

std::ostream& operator<<(std::ostream& out, const BuyAndSellStockTwoData & data) {
    out << "BuyAndSellStockTwoData [ input=[";
    for (int value : data.m_input)
        out << " " << value;
    out << " ] expected=" << data.m_expected << " ]";

    return out;
}

std::istream& operator>>(std::istream& in, BuyAndSellStockTwoData &data) {
    ::loaders::vectors::vectorLoader<
        int,
        std::vector<int>,
        char,
        ::checkers::is_space_or<','>
    > inputLoader(data.m_input, '[', ']');
    in >> inputLoader;

    in >> data.m_expected;

    ::checkers::skip_spaces<char, ::checkers::is_space> skipSpace;

    skipSpace(in);

    return in;
}

// Test Fixture Class
class BuyAndSellStockTwoFixture :
    public testing::TestWithParam<BuyAndSellStockTwoData> {
};

// Parameterized Test Definition
TEST_P(BuyAndSellStockTwoFixture, BuyAndSellStockTwoTests) {
    BuyAndSellStockTwoData data = GetParam();

    Solution solution;

    int actual = solution.findMaximumProfit(data.get_input());

    ASSERT_EQ(actual, data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(BuyAndSellStockTwoTests, BuyAndSellStockTwoFixture, testing::ValuesIn(
    Loader<BuyAndSellStockTwoData>()(find_path("arrays/data/buy_and_sell_stock_two.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
