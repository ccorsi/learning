/**
 * @file largest_square_submatrix.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This is a solution to the problem https://www.techiedelight.com/?problem=LargestSquareSubmatrix
 * @version 0.1
 * @date 2023-06-01
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include "largest_square_submatrix.h"

namespace valhalla {
    namespace matrices {
        namespace largest_square_submatrix {
            /*

            Given a binary matrix, find size of the largest square submatrix, which is
            surrounded by all 1’s.

            Input:
            [
                [1, 1, 1, 1, 1, 1],
                [1, 0, 1, 1, 0, 1],
                [0, 1, 1, 0, 0, 1],
                [1, 1, 1, 1, 1, 1],
                [1, 0, 0, 1, 0, 1],
                [1, 0, 1, 1, 0, 0],
                [1, 0, 1, 0, 1, 1],
                [1, 1, 1, 0, 1, 1]
            ]

            Output: 4

            Explanation: The size of the largest square submatrix in the following binary
            matrix is 4. The largest square submatrix is formed by cells (0, 2), (3, 2),
            (0, 5), and (3, 5).

            */

            int Solution::findLargestSquareMatrix(std::vector<std::vector<int>> const & mat) {
                int largest = 0;

                return largest;
            } // findLargestSquareMatrix
        }
    }
}
