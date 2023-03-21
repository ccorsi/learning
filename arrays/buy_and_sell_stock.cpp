/**
 * @file buy_and_sell_stock.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains a solution to the problem https://www.techiedelight.com/?problem=BuyAndSellStock
 * @version 0.1
 * @date 2023-03-20
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include <iostream>
#include <algorithm>
#include <utility>

#include "buy_and_sell_stock.h"

namespace valhalla {
    namespace arrays {
        namespace buy_and_sell_stock {
            /*

            Given a list containing future predictions of share prices and a
            positive integer `k`, find the maximum profit earned by buying and
            selling shares at most `k` times with a constraint that a new
            transaction can only start after the previous transaction is
            complete, i.e., you can only hold at most one share at a time.

            Input: price[]: [2, 4, 7, 5, 4, 3, 5], k = 2
            Output: 7
            Explanation: The maximum profit is 7 (sum of 5 and 2)

            • Buy at a price 2 and sell at a price 7
            • Buy at a price 3 and sell at a price 5


            Input: price[]: [1, 5, 2, 3, 7, 6, 4, 5], k = 3
            Output: 10
            Explanation: The maximum profit is 10 (sum of 4, 5, and 1).

            • Buy at a price 1 and sell at a price 5
            • Buy at a price 2 and sell at a price 7
            • Buy at a price 4 and sell at a price 5


            Input: price[]: [10, 6, 8, 4, 2], k = 2
            Output: 2
            Explanation: The maximum profit is 2. Buy at a price 6 and sell at a price 8.


            Input: price[]: [10, 8, 6, 5, 4, 2], k = 1
            Output: 0
            Explanation: Prices are given in descending order.

            */

            int Solution::findMaximumProfit(std::vector<int> const & price, int k) {
                int max = 0;

                if (k > 0) {
                    int idx = 0;
                    const int size = price.size(), last = price.size() - 1;
                    std::vector<std::pair<int,int>> profits;

                    while ( idx  < size) {

                        while (idx < last && price[idx] >= price[idx+1]) idx++;

                        if (idx == last) break;

                        const int bought = price[idx];

                        while (idx < last && price[idx] <= price[idx+1]) idx++;

                        if (idx == last) {
                            if (bought < price[last]) {
                                profits.push_back(std::pair(price[last], bought));
                            }
                            break;
                        } else {
                            profits.push_back(std::pair(price[idx], bought));
                        } // else
                    } // while

                    int profits_size = profits.size();

                    if (k >= profits_size) {
                        for (int idx = 0 ; idx < profits_size ; idx++) {
                            max += profits[idx].first - profits[idx].second;
                        } // for
                    } else {
                        // We combined the current profits and then find the k largest profits

                        std::vector<std::pair<int,int>> purged(profits);

                        // Calculate the max profit for the current set of values

                        std::cout << "Before Profits [";
                        for (std::pair<int,int> profit : profits)
                            std::cout << " (" << profit.second << "," << profit.first << ")";
                        std::cout << " ]" << std::endl;
                        int current_max = 0;

                        std::sort(profits.begin(), profits.end(), [](const std::pair<int,int> & lhs, const std::pair<int,int> & rhs) {
                            return ( lhs.first - lhs.second ) > ( rhs.first - rhs.second );
                        });

                        std::cout << "After Profits [";
                        for (std::pair<int,int> profit : profits)
                            std::cout << " (" << profit.second << "," << profit.first << ")";
                        std::cout << " ]" << std::endl;
                        for (int i = 0 ; i < k ; i++) {
                            current_max += profits[i].first - profits[i].second;
                        } // for

                        do {
                            profits = purged;
                            purged.clear();

                            profits_size = profits.size();

                            purged.push_back(profits[0]);

                            std::cout << "Profits [";
                            for (std::pair<int,int> profit : profits)
                                std::cout << " (" << profit.second << "," << profit.first << ")";
                            std::cout << " ]" << std::endl;
                            for (int idx = 1 ; idx < profits_size ; idx++) {
                                std::pair<int,int> & back = purged.back();

                                if (back.first < profits[idx].first && back.second <= profits[idx].second) {
                                    back.first = profits[idx].first;
                                    continue;
                                }

                                purged.push_back(profits[idx]);
                            } // for
                            std::cout << "Purged [";
                            for (std::pair<int,int> profit : purged)
                                std::cout << " (" << profit.second << "," << profit.first << ")";
                            std::cout << " ]" << std::endl;
                        } while (purged.size() < profits.size());

                        if (static_cast<int>(purged.size()) <= k) {
                            for (std::pair<int,int> profit : purged) {
                                max += profit.first - profit.second;
                            } // for
                        } else {
                            std::vector<int> all_profits;

                            for (std::pair<int,int> profite : purged) {
                                all_profits.push_back(profite.first - profite.second);
                            } // for

                            std::sort(all_profits.begin(), all_profits.end(), std::greater<int>());

                            for (int idx = 0 ; idx < k ; idx++) {
                                max += all_profits[idx];
                            } // for
                        } // else

                        if (current_max > max) {
                            max = current_max;
                        } // if

                    } // else
                } // if

                return max;
            } // findMaximumProfit
        }
    }
}
