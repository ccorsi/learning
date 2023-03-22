/**
 * @file buy_and_sell_stock_threetests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains tests to the problem https://www.techiedelight.com/?problem=BuyAndSellStockIII
 * @version 0.1
 * @date 2023-03-21
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
#include "buy_and_sell_stock_three.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::utils;
using namespace valhalla::arrays::buy_and_sell_stock_three;

// Test Fixture Data Class
class BuyAndSellStockThreeData {
    std::vector<int> m_x_input;
    std::vector<int> m_y_input;
    int m_expected;
public:
    BuyAndSellStockThreeData() = default;

    std::vector<int> const & get_x_input() { return m_x_input; }
    std::vector<int> const & get_y_input() { return m_y_input; }
    int get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const BuyAndSellStockThreeData &);
    friend std::istream& operator>>(std::istream&, BuyAndSellStockThreeData &);

};

std::ostream& operator<<(std::ostream& out, const BuyAndSellStockThreeData & data) {
    out << "BuyAndSellStockThreeData [ X=[";
    for (int value : data.m_x_input)
        out << " " << value;
    out << " ] Y=[";
    for (int value : data.m_y_input)
        out << " " << value;
    out << " ] expected=" << data.m_expected << " ]";

    return out;
}

std::istream& operator>>(std::istream& in, BuyAndSellStockThreeData &data) {
    ::loaders::vectors::vectorLoader<
        int,
        std::vector<int>,
        char,
        ::checkers::is_space_or<','>
    > inputXLoader(data.m_x_input, '[', ']');
    in >> inputXLoader;

    ::loaders::vectors::vectorLoader<
        int,
        std::vector<int>,
        char,
        ::checkers::is_space_or<','>
    > inputYLoader(data.m_y_input, '[', ']');
    in >> inputYLoader;

    in >> data.m_expected;

    ::checkers::skip_spaces<char, ::checkers::is_space> skipSpace;

    skipSpace(in);

    return in;
}

// Test Fixture Class
class BuyAndSellStockThreeFixture :
    public testing::TestWithParam<BuyAndSellStockThreeData> {
};

// Parameterized Test Definition
TEST_P(BuyAndSellStockThreeFixture, BuyAndSellStockThreeTests) {
    BuyAndSellStockThreeData data = GetParam();

    Solution solution;

    int actual = solution.findMaximumProfit(data.get_x_input(), data.get_y_input());

    ASSERT_EQ(actual, data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(BuyAndSellStockThreeTests, BuyAndSellStockThreeFixture, testing::ValuesIn(
    Loader<BuyAndSellStockThreeData>()(find_path("arrays/data/buy_and_sell_stock_three.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
