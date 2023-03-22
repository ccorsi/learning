/**
 * @file buy_and_sell_stock_three.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains a solution to the problem https://www.techiedelight.com/?problem=BuyAndSellStockIII
 * @version 0.1
 * @date 2023-03-21
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */


#include "buy_and_sell_stock_three.h"

namespace valhalla {
    namespace arrays {
        namespace buy_and_sell_stock_three {
            /*

            Given a list containing future price predictions of two different stocks for the
            next n–days, find the maximum profit earned by selling the stocks with a
            constraint that the second stock can be sold, only if no transaction happened on
            the previous day for any of the stock.

            Assume that the given prices are relative to the buying price. Each day, we can
            either sell a single share of the first stock or a single share of the second
            stock or sell nothing.

            Input: X = [5, 3, 4, 6, 3], Y = [8, 4, 3, 5, 10]

            Day	 Price(X)  Price(Y)
            1		5		 8
            2		3		 4
            3		4		 3
            4		6		 5
            5		3		 10

            Output: 25

            Explanation:

            Day 1: Sell stock Y at a price of 8
            Day 2: Sell stock X at a price of 3
            Day 3: Sell stock X at a price of 4
            Day 4: Don't sell anything
            Day 5: Sell stock Y at a price of 10

            */

            int Solution::findMaximumProfit(std::vector<int> const & X, std::vector<int> const & Y) {
                int max = 0;
                const int size = X.size();

                checkMaximumProfit(X, 0, Y, 0, size, 0, 0, max);

                return max;
            } // findMaximumProfit

            void Solution::checkMaximumProfit(std::vector<int> const & X, const int x_sales,
                                              std::vector<int> const & Y, const int y_sales,
                                              const int size, int idx, int total, int & max) {
                if (total > max) {
                    max = total;
                } // if

                if (idx >= size) {
                    // We are done
                    return;
                } // if

                // We need to look at what possible combinations that we can perform on the given conditions

                // sell X
                checkMaximumProfit(X, x_sales + 1, Y, y_sales, size, idx + 1, total + X[idx], max);

                // Can we sell Y?
                if (x_sales == 0 && y_sales == 0) {
                    checkMaximumProfit(X, x_sales, Y, y_sales + 1, size, idx + 1, total + Y[idx], max);
                } // if

                // Can we sell none?
                checkMaximumProfit(X, 0, Y, 0, size, idx + 1, total, max);

            } // checkMaximumProfit
        }
    }
}
