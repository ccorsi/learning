/**
 * @file submatrix_sum.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains a solution to the problem https://www.techiedelight.com/?problem=SubmatrixSum
 * @version 0.1
 * @date 2023-06-20
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include "submatrix_sum.h"

namespace valhalla {
    namespace matrices {
        namespace submatrix_sum {
            /*

            Given an `M × N` integer matrix and two coordinates (p, q) and (r, s) representing
            top-left and bottom-right coordinates of a submatrix of it, calculate the sum of
            all elements present in the submatrix.

            Input:

            mat =
            [
                [0, 2, 5, 4, 1],
                [4, 8, 2, 3, 7],
                [6, 3, 4, 6, 2],
                [7, 3, 1, 8, 3],
                [1, 5, 7, 9, 4]
            ]

            (p, q) = (1, 1)
            (r, s) = (3, 3)

            Output: 38

            Explanation: The submatrix formed by coordinates (p, q), (p, s), (r, q), and (r, s)
            is shown below, having the sum of elements equal to 38.

            8  2  3
            3  4  6
            3  1  8

            Assume that `m` lookup calls are made to the matrix; the task is to achieve constant
            time lookups.

            */

            int Solution::findSubmatrixSum(std::vector<std::vector<int>> const & mat, int p, int q, int r, int s) {
                int sum = -1;



                return sum;
            } // findSubmatrixSum
        }
    }
}
