/**
 * @file buy_and_sell_stock_two.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains a solution to the problem https://www.techiedelight.com/?problem=BuyAndSellStockII
 * @version 0.1
 * @date 2023-03-21
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */


#include "buy_and_sell_stock_two.h"

#include <utility>
#include <algorithm>
#include <iostream>

namespace valhalla {
    namespace arrays {
        namespace buy_and_sell_stock_two {
            /*

            Given a list containing future predictions of share prices, find the maximum profit
            earned by buying and selling shares at most twice with a constraint that a new
            transaction can only start after the previous transaction complete, i.e., we can
            only hold at most one share at a time.

            Input: [2, 4, 7, 5, 4, 3, 5]
            Output: 7
            Explanation: The maximum profit is 7. You can buy at a price 2 and sell at a price 7.
            Then, buy at a price 3 and sell at a price 5.

            Input: [10, 6, 8, 4, 2]
            Output: 2
            Explanation: The maximum profit is 2. You can buy at a price 6 and sell at a price 8.

            Input: [8, 7, 6, 4]
            Output: 0
            Explanation: The maximum profit is 0 as buying and selling stock will result in loss.

            */

            int Solution::findMaximumProfit(std::vector<int> const & price) {
                const int k = 2;
                int max = 0;
                int idx = 0;
                const int size = price.size(), last = price.size() - 1;
                std::vector<std::pair<int,int>> profits;

                // We are looking to valleys and peaks that will define the
                // buying and selling of the different shares.
                while ( idx  < size) {

                    // look for a valley
                    while (idx < last && price[idx] >= price[idx+1]) idx++;

                    // if none exist exit while loop
                    if (idx == last) break;

                    // store bought price
                    const int bought = price[idx];

                    // look for a peak
                    while (idx < last && price[idx] <= price[idx+1]) idx++;

                    if (idx == last) {
                        // we know that last entry is the best sell price
                        // and is larger than the bought price
                        if (bought < price[last]) {
                            profits.push_back(std::pair(price[last], bought));
                        }
                        break;
                    } else {
                        // we've found a valley and peak so we store it and look
                        // for the next one.
                        profits.push_back(std::pair(price[idx], bought));
                    } // else
                } // while

                int profits_size = profits.size();

                if (profits_size < k) {
                    // This can't be reduced any more than it has already been
                    // reduced so we just need to sum up the profit
                    for (std::pair<int,int> & sale : profits) {
                        max += sale.first - sale.second;
                    } // for
                } else {
                    std::vector<int> sales;

                    for (std::pair<int,int> & sale : profits) {
                        sales.push_back(sale.first - sale.second);
                    } // for

                    std::sort(sales.begin(), sales.end(), [](const int & lhs, const int & rhs) { return lhs > rhs; });

                    // initially define the max using the top type sales
                    for (int idx = 0 ; idx < k ; idx++) {
                        max += sales[idx];
                    } // for

                    std::cout << "Sales [";
                    for (std::pair<int,int> & sale : profits)
                        std::cout << " (" << sale.second << "," << sale.first << ")";
                    std::cout << " ] max = " << max << std::endl;

                    /*
                        How does one go about solving the issue that we can only use two sales that provide the
                        greatest profit.  The issue is that it is possible that one or more of the different
                        sales can be combined into a single sale that could provide more profit than the
                        initial max profit.

                        We then need to determine if we can purge two consecutive sales into a single sale.
                        We keep doing this until we've reduced the number of sales to 2 or less.  The issue
                        that after each reduction we need to determine the current profit for those sets of
                        sales.

                        While the above algorithm makes sense.  The question is if we should consider continuing
                        to combine the sales until we can't any longer?  It could be possible that we might be
                        able to generate a greater profit with one sale.
                    */

                    // Used to determine where to start the next set of purging
                    int start = 0;

                    // used to indicate if we were able to combine one or more sale
                    bool wasPurged = false;

                    while (wasPurged || start < profits_size) {

                        if ( ! wasPurged ) {
                            // No sales were combined therefore increment start;
                            start++;
                        } // if

                        // reset wasPurged to false
                        wasPurged = false;

                        // This is used to store the currently processed sale that have or haven't been combined
                        std::vector<std::pair<int,int>> purged;

                        for (int idx = 0 ; idx < start ; idx++)
                            purged.push_back(profits[idx]);

                        for (int idx = start ; idx < profits_size ; idx++) {
                            std::pair<int,int> & sale = profits[idx];
                            std::pair<int,int> & last = purged.back();
                            if (last.first <= sale.first && last.second < sale.second) {
                                last.first = sale.first;
                                wasPurged = true;
                                // We need to stop as soon as we've purged two k
                                if (purged.size() + profits_size - idx - 1 <= k) {
                                    while (++idx < profits_size) {
                                        purged.push_back(profits[idx]);
                                    } // while
                                    continue;
                                } // if
                            } else {
                                purged.push_back(sale);
                            } // else
                        } // for

                        if (wasPurged) {
                            sales.clear();

                            for (std::pair<int,int> & sale : purged) {
                                sales.push_back(sale.first - sale.second);
                            } // for

                            std::sort(sales.begin(), sales.end(), [](const int & lhs, const int & rhs) { return lhs > rhs; });

                            // This is used to total the current purge of the sales that is then compared to the 
                            // current max.
                            int total = 0;

                            // used to determine if we've read the required amount of sales
                            int count = 0;

                            // initially define the max using the top type sales
                            for (int sale : sales) {
                                if (count++ >= k) {
                                    // we've added the k top sales
                                    break;
                                } // if
                                total += sale;
                            } // for

                            if (total > max) {
                                max = total;
                            } // if

                            // copy purged entries to profits
                            profits = purged;

                            // update profits size
                            profits_size = profits.size();
                            std::cout << "Purged sales [";
                            for (std::pair<int,int> & sale : profits)
                                std::cout << " (" << sale.second << "," << sale.first << ")";
                            std::cout << " ] max = " << max << std::endl;
                        } // if

                    } // while
                } // else

                return max;
            } // findMaximumProfit
        }
    }
}
