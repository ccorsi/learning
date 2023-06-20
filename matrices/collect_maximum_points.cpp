/**
 * @file collect_maximum_points.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains a solution to the problem https://www.techiedelight.com/?problem=CollectMaximumPoints
 * @version 0.1
 * @date 2023-06-19
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include "collect_maximum_points.h"

namespace valhalla {
    namespace matrices {
        namespace collect_maximum_points {
            /*

            Given an `M × N` matrix where each cell can have a value of 1, 0, or -1, where -1
            denotes an unsafe cell, collect the maximum number of ones starting from the first
            cell and by visiting only safe cells (i.e., 0 or 1). If the row is odd, you are
            only allowed to go left or down from the current cell; if the row is even, you can
            go right or down.

            Input:

            [
                [ 1,  1, -1,  1,  1],
                [ 1,  0,  0, -1,  1],
                [ 1,  1,  1,  1, -1],
                [-1, -1,  1,  1,  1],
                [ 1,  1, -1, -1,  1]
            ]

            Output: 9

            Explanation: The maximum value that can be collected is 9, as marked below.


                1 — 1  -1   1   1
                    |
                1 — 0   0  -1   1
                |
                1 — 1 — 1 — 1  -1
                            |
            -1  -1   1 — 1   1

                1   1  -1  -1   1

            */

            int Solution::findMaximumPoints(std::vector<std::vector<int>> const & mat) {
                int points = -1;



                return points;
            } // findMaximumPoints
        }
    }
}
