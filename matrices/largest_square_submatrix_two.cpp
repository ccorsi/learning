/**
 * @file largest_square_submatrix_two.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This is a solution to the problem https://www.techiedelight.com/?problem=LargestSquareSubmatrixII
 * @version 0.1
 * @date 2023-06-01
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include "largest_square_submatrix_two.h"

namespace valhalla {
    namespace matrices {
        namespace largest_square_submatrix_two {
            /*

            Given an `M × N` binary matrix, find the size of the largest square submatrix of 1’s in it.

            Input:

            [
                [0, 0, 1, 0, 1, 1],
                [0, 1, 1, 1, 0, 0],
                [0, 0, 1, 1, 1, 1],
                [1, 1, 0, 1, 1, 1],
                [1, 1, 1, 1, 1, 1],
                [1, 1, 0, 1, 0, 1],
                [1, 0, 1, 1, 1, 1],
                [1, 1, 1, 0, 1, 1]
            ]

            Output: 3

            Explanation: The largest square submatrix of 1’s is marked below by `x`.

                0  0  1  0  1  1
                0  1  1  1  0  0
                0  0  1  x  x  x
                1  1  0  x  x  x
                1  1  1  x  x  x
                1  1  0  1  0  1
                1  0  1  1  1  1
                1  1  1  0  1  1

            */

            int Solution::findLargestSquareSubmatrix(std::vector<std::vector<int>> const & mat) {
                int largest = 0;

                return largest;
            } // findLargestSquareSubmatrix
        }
    }
}
