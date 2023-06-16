/**
 * @file matrix_path_five.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains a solution to the problem https://www.techiedelight.com/?problem=MatrixPathV
 * @version 0.1
 * @date 2023-06-16
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include "matrix_path_five.h"

namespace valhalla {
    namespace matrices {
        namespace matrix_path_five {
            /*

            Given an `M × N` matrix of integers, count the number of different ways
            to reach the bottom-right corner of a matrix from its top-left corner
            with exactly `k` turn allowed and using only the directions right or down.

            A turn is defined as a down move immediately followed by a right move, or
            a right move immediately followed by a down move.

            Input : M = 3, N = 3, k = 1
            Output: 2
            Explanation: Total number of paths are 2, as shown below:

            (0, 0) —> (0, 1) —> (0, 2) —> (1, 2) —> (2, 2)
            (0, 0) —> (1, 0) —> (2, 0) —> (2, 1) —> (2, 2)


            Input : M = 3, N = 3, k = 2
            Output: 2
            Explanation: Total number of paths are 2, as shown below:

            (0, 0) —> (0, 1) —> (1, 1) —> (2, 1) —> (2, 2)
            (0, 0) —> (1, 0) —> (1, 1) —> (1, 2) —> (2, 2)


            Input : M = 3, N = 3, k = 4
            Output: 0

            */

            int Solution::findTotalWays(int M, int N, int k) {
                int ways = -1;



                return ways;
            } // findTotalWays
        }
    }
}
