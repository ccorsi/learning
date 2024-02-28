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

#include <climits>

#include "minimum_cost_path.h"

namespace valhalla {
    namespace matrices {
        namespace minimum_cost_path {

            void Solution::check(std::vector<std::vector<int>> const & cost, const int row,
                                 const int col, const int total, int & min) {
                const auto rows = cost.size(), cols = cost[0].size();

                if (row == rows - 1 && col == cols - 1) {
                    if (total < min) {
                        min = total;
                    } // if (total < min)
                    return;
                } // if (row == rows - 1 && col == cols - 1)

                // TODO: Calculate that moving to the next row is a valid path to the
                //       bottom right point.
                if (row + 1 < rows) {
                    check(cost, row+1, col, total + cost[row+1][col], min);
                } // if (row + 1 < rows)

                if (col + 1 < cols) {
                    check(cost, row, col+1, total + cost[row][col+1], min);
                } // if (col + 1 < cols)
            } // check

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
                if (cost.empty()) {
                    return 0;
                } // if (cost.empty())

                int min = INT_MAX;

                check(cost, 0, 0, cost[0][0], min);

                return min;
            } // findMinCost
        }
    }
}
