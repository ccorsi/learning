/**
 * @file minimum_cost_path.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains a solution to the problem https://www.techiedelight.com/?problem=MinimumCostPath
 * @version 0.1
 * @date 2023-06-19
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include "minimum_cost_path.h"

namespace valhalla {
    namespace matrices {
        namespace minimum_cost_path {
            /*

            Given an `M × N` matrix of integers where each cell has a cost associated
            with it, find the minimum cost to reach the last cell (M-1, N-1) of the
            matrix from its first cell (0, 0). You can only move one unit right or
            one unit down from any cell, i.e., from cell (i, j), you can move to
            (i, j+1) or (i+1, j).

            Input:

            [
                [4, 7, 8, 6, 4],
                [6, 7, 3, 9, 2],
                [3, 8, 1, 2, 4],
                [7, 1, 7, 3, 7],
                [2, 9, 8, 9, 3]
            ]

            Output: 36

            Explanation: The highlighted path shows the minimum cost path having a cost
                         of 36.

                4   7   8   6   4
                |
                6 — 7 — 3   9   2
                        |
                3   8   1 — 2   4
                            |
                7   1   7   3 — 7
                                |
                2   9   8   9   3

            */

            int Solution::findMinCost(std::vector<std::vector<int>> const & cost) {
                int min = -1;



                return min;
            } // findMinCost
        }
    }
}
