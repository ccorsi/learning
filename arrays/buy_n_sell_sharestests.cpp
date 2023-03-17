/**
 * @file buy_n_sell_sharestests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains tests to the problem https://www.techiedelight.com/?problem=BuyNSellShares
 * @version 0.1
 * @date 2023-03-16
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
#include "buy_n_sell_shares.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::utils;
using namespace valhalla::arrays::buy_n_sell_shares;

// Test Fixture Data Class
class BuyNSellSharesData {
    std::vector<int> m_input;
    int m_expected;
public:
    BuyNSellSharesData() = default;

    std::vector<int> const & get_input() { return m_input; }
    int get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const BuyNSellSharesData &);
    friend std::istream& operator>>(std::istream&, BuyNSellSharesData &);

};

std::ostream& operator<<(std::ostream& out, const BuyNSellSharesData & data) {
    out << "BuyNSellSharesData [ input=[";
    for (int value : data.m_input)
        out << " " << value;
    out << " ] expected=" << data.m_expected << " ]";

    return out;
}

std::istream& operator>>(std::istream& in, BuyNSellSharesData &data) {
    ::loaders::vectors::vectorLoader<
        int,
        std::vector<int>,
        char,
        ::checkers::is_space_or<','>
    > loader(data.m_input, '[', ']');
    in >> loader;

    in >> data.m_expected;
    std::string line;
    std::getline(in, line); // read end of line

    return in;
}

// Test Fixture Class
class BuyNSellSharesFixture :
    public testing::TestWithParam<BuyNSellSharesData> {
};

// Parameterized Test Definition
TEST_P(BuyNSellSharesFixture, BuyNSellSharesTests) {
    BuyNSellSharesData data = GetParam();

    Solution solution;

    int actual = solution.findMaxProfit(data.get_input());

    ASSERT_EQ(actual, data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(BuyNSellSharesTests, BuyNSellSharesFixture, testing::ValuesIn(
    Loader<BuyNSellSharesData>()(find_path("arrays/data/buy_n_sell_shares.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
