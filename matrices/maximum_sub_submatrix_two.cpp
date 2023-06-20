/**
 * @file maximum_sub_submatrix_two.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains a solution to the problem https://www.techiedelight.com/?problem=MaximumSumSubmatrixII
 * @version 0.1
 * @date 2023-06-20
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include "maximum_sub_submatrix_two.h"

namespace valhalla {
    namespace matrices {
        namespace maximum_sub_submatrix_two {
            /*

            Given an `N × N` matrix, find the maximum sum submatrix present in it.

            Input:

            mat = [
                [-5, -6, 3, 1, 0],
                [9, 7, 8, 3, 7],
                [-6, -2, -1, 2, -4],
                [-7, 5, 5, 2, -6],
                [3, 2, 9, -5, 1]
            ]

            Output:

            [
                [7, 8, 3],
                [-2, -1, 2],
                [5, 5, 2],
                [2, 9, -5]
            ]

            In case the multiple maximum sum submatrix exists, the solution can return
            any one of them.

            */

            std::vector<std::vector<int>> Solution::findMaxSubSubmatrix(std::vector<std::vector<int>> const & mat) {
                std::vector<std::vector<int>> max;



                return max;
            } // findMaxSubSubmatrix
        }
    }
}
