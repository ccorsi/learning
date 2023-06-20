/**
 * @file tiles_problem.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains a solution to the problem https://www.techiedelight.com/?problem=TilesProblem
 * @version 0.1
 * @date 2023-06-19
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include "tiles_problem.h"

namespace valhalla {
    namespace matrices {
        namespace tiles_problem {
            /*

            Given an `n × 4` matrix where `n` is a positive number, find the number of ways to
            fill the matrix with `1 × 4` tiles.

            Input: n = 5
            Output: 3
            Explanation: There are three ways to place `1 × 4` tiles in a `5 × 4` matrix:

            • Place all 5 tiles horizontally.
            • Place 4 tiles vertically in the first four rows and 1 tile horizontally in the
                last row.
            • Place 1 tile horizontally in the first row and adjust 4 tiles vertically in
                the remaining rows.

            Input: n = 6
            Output: 4
            Explanation: There are 4 ways to place `1 × 4` tiles in a `6 × 4` matrix:

            • Place all 6 tiles horizontally.
            • Place 4 tiles vertically in the first four rows and the remaining 2 tiles
                horizontally in the last two rows.
            • Place 2 tiles horizontally in the first two rows, and adjust the remaining
                4 tiles vertically in the remaining rows.
            • Place 2 tiles horizontally in the first and last row, and adjust the
                remaining 4 tiles vertically in the middle rows.

            */

            long Solution::findTotalWays(int n) {
                long total = -1;



                return total;
            } // findTotalWays
        }
    }
}
