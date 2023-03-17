/**
 * @file buy_n_sell_shares.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains a solution to the problem https://www.techiedelight.com/?problem=BuyNSellShares
 * @version 0.1
 * @date 2023-03-16
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include "buy_n_sell_shares.h"

/*

Given a list containing future prediction of share price, find the maximum profit earned by
buying and selling shares any number of times with the constraint, a new transaction can only
start after the previous transaction is complete, i.e., you can only hold at most one share
at a time.

Input : [1, 5, 2, 3, 7, 6, 4, 5]
Output: 10
Explanation: Total profit earned is 10

Buy on day 1 and sell on day 2
Buy on day 3 and sell on day 5
Buy on day 7 and sell on day 8


Input : [10, 8, 6, 5, 4, 2]
Output: 0

*/

int valhalla::arrays::buy_n_sell_shares::Solution::findMaxProfit(std::vector<int> const & price) {
    const int size = price.size();
    int max_profit = 0;

    for (int idx = 0 ; idx < size ; idx++) {
        findMaxSell(price, idx, 0, max_profit);
    } // for

    return max_profit;
}

void valhalla::arrays::buy_n_sell_shares::Solution::findMaxSell(std::vector<int> const & price, int b_idx, int sum, int & max_profit) {
    const int min = price[b_idx], size = price.size();

    for (int idx = b_idx + 1; idx < size ; idx++) {
        if (min < price[idx]) {
            findMinBuy(price, idx, sum + price[idx] - min, max_profit);
        } // if
    } // for

}

void valhalla::arrays::buy_n_sell_shares::Solution::findMinBuy(std::vector<int> const & price, int b_idx, int sum, int & max_profit) {
    if (sum > max_profit) {
        max_profit = sum;
    }

    const int max = price[b_idx], size = price.size();

    for (int idx = b_idx + 1; idx < size ; idx++) {
        if (price[idx] < max) {
            findMaxSell(price, idx, sum, max_profit);
        } // if
    } // for
}
