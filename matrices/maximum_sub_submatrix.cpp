/**
 * @file maximum_sub_submatrix.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains a solution to the problem https://www.techiedelight.com/?problem=MaximumSumSubmatrix
 * @version 0.1
 * @date 2023-06-20
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include "maximum_sub_submatrix.h"

namespace valhalla {
    namespace matrices {
        namespace maximum_sub_submatrix {
            /*

            Given an `M × N` integer matrix, calculate the maximum sum submatrix of size `k × k` in it.

            Input:

            mat = [
                [ 3, -4,  6, -5,  1],
                [ 1, -2,  8, -4, -2],
                [ 3, -8,  9,  3,  1],
                [-7,  3,  4,  2,  7],
                [-3,  7, -5,  7, -6]
            ]

            • If k = 2, then

            Output:
            [
                [9, 3],
                [4, 2]
            ]

            • If k = 3, then

            Output:
            [
                [8, -4, -2],
                [9,  3,  1],
                [4,  2,  7]
            ]

            In case the multiple `k × k` submatrix exists with the maximum sum, the solution can return
            any one of them.

            */

            std::vector<std::vector<int>> Solution::findMaxSubSubmatrix(std::vector<std::vector<int>> const & mat, int k) {
                std::vector<std::vector<int>> max;



                return max;
            } // findMaxSubSubmatrix
        }
    }
}
