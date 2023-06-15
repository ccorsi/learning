/**
 * @file maximum_difference_pair_two.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains a solution to the problem https://www.techiedelight.com/?problem=MaximumDifferencePairII
 * @version 0.1
 * @date 2023-06-14
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */


#include "maximum_difference_pair_two.h"

namespace valhalla {
    namespace matrices {
        namespace maximum_difference_pair_two {
            /*

            Given a square matrix of integers, find the maximum value of `M[c][d] - M[a][b]` over
            every choice of indexes such that `c > a` and `d > b` in a single traversal of the matrix.

            Input:

            [
                [ 1,  2, -1, -4, -20],
                [-8, -3,  4,  2,  1],
                [ 3,  8,  6,  1,  3],
                [-4, -1,  1,  7, -6],
                [ 0, -4, 10, -5,  1]
            ]

            Output: 18

            Explanation: The maximum value is 18 as M[4][2] – M[1][0] has maximum difference.

            Assume: matrix size > 1

            */

            int Solution::findMaxDiff(std::vector<std::vector<int>> & mat) {
                int max = -1;



                return max;
            } // findMaxDiff
        }
    }
}
