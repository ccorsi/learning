/**
 * @file buy_and_sell_stocktests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains tests to the problem https://www.techiedelight.com/?problem=BuyAndSellStock
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
#include "buy_and_sell_stock.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::utils;
using namespace valhalla::arrays::buy_and_sell_stock;

// Test Fixture Data Class
class BuyAndSellStockData {
    std::vector<int> m_input;
    int m_k;
    int m_expected;
public:
    BuyAndSellStockData() = default;

    std::vector<int> const & get_input() { return m_input; }
    int get_k() { return m_k; }
    int get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const BuyAndSellStockData &);
    friend std::istream& operator>>(std::istream&, BuyAndSellStockData &);

};

std::ostream& operator<<(std::ostream& out, const BuyAndSellStockData & data) {
    out << "BuyAndSellStockData [ input=[";
    for (int value : data.m_input)
        out << " " << value;
    out << " ] k=" << data.m_k << " expected=" << data.m_expected << " ]";

    return out;
}

std::istream& operator>>(std::istream& in, BuyAndSellStockData &data) {
    ::loaders::vectors::vectorLoader<
        int,
        std::vector<int>,
        char,
        ::checkers::is_space_or<','>
    > inputLoader(data.m_input, '[', ']');
    in >> inputLoader;

    in >> data.m_k >> data.m_expected;

    ::checkers::skip_spaces<char,::checkers::is_space> skipSpace;

    skipSpace(in);

    return in;
}

// Test Fixture Class
class BuyAndSellStockFixture :
    public testing::TestWithParam<BuyAndSellStockData> {
};

// Parameterized Test Definition
TEST_P(BuyAndSellStockFixture, BuyAndSellStockTests) {
    BuyAndSellStockData data = GetParam();

    Solution solution;

    int actual = solution.findMaximumProfit(data.get_input(), data.get_k());

    ASSERT_EQ(actual, data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(BuyAndSellStockTests, BuyAndSellStockFixture, testing::ValuesIn(
    Loader<BuyAndSellStockData>()(find_path("arrays/data/buy_and_sell_stock.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
