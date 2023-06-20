/**
 * @file collect_coins.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains a solution to the problem https://www.techiedelight.com/?problem=CollectCoins
 * @version 0.1
 * @date 2023-06-20
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include "collect_coins.h"

namespace valhalla {
    namespace matrices {
        namespace collect_coins {
            /*

            Given an `M × N` matrix of non-negative integers where each cell contains a coin of some denomination, collect the maximum value of coins by traversing the grid.

            The first traversal starts from the top-left corner of the matrix and ends in the bottom-left corner, and the second traversal starts from the top-right corner and ends in the bottom-right corner. From any cell (i, j) in the matrix, you are allowed to move to cell (i+1, j+1) or (i+1, j-1) or (i+1, j). If both traversals pass through the same cell, only one can collect coins from that cell.

            Input:

            [
                [0, 2, 4, 1],
                [4, 8, 3, 7],
                [2, 3, 6, 2],
                [9, 7, 8, 3],
                [1, 5, 9, 4]
            ]

            Output: 47

            Explanation:

            First traversal : [0, 8, 3, 9, 1]
            Second traversal: [1, 7, 6, 8, 4]

            */

            int Solution::getMaxCoins(std::vector<std::vector<int>> const & mat) {
                int max = -1;



                return max;
            } // getMaxCoins
        }
    }
}
