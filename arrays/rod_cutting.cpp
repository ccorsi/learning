/**
 * @file rod_cutting.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This is a solution to the problem https://www.techiedelight.com/?problem=RodCutting
 * @version 0.1
 * @date 2023-05-20
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include "rod_cutting.h"

namespace valhalla {
    namespace arrays {
        namespace rod_cutting {
            /*

            Given a rod of length `n` and a list of rod prices of length `i`,
            where `1 <= i <= n`, find the optimal way to cut the rod into
            smaller rods to maximize profit.

            Input:

            n = 4 									(Rod length)
            price = [1, 5, 8, 9, 10, 17, 17, 20]	(Rod of length `i` has a cost price[i-1])

            Output: 10
            Explanation: Cut the rod into two pieces of length 2 each to gain
            revenue of 5 + 5 = 10

            Cut		   	 	Profit

            4				9
            1, 3			(1 + 8) = 9
            2, 2			(5 + 5) = 10	  <-- optimal way
            3, 1			(8 + 1) = 9
            1, 1, 2			(1 + 1 + 5) = 7
            1, 2, 1			(1 + 5 + 1) = 7
            2, 1, 1			(5 + 1 + 1) = 7
            1, 1, 1, 1		(1 + 1 + 1 + 1) = 4

            */

            int Solution::findMaxProfit(std::vector<int> const & price, int n) {
                int profit = 0;

                return profit;
            } // findMaxProfit
        }
    }
}
