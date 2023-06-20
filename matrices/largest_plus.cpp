/**
 * @file largest_plus.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains a solution to the problem https://www.techiedelight.com/?problem=LargestPlus
 * @version 0.1
 * @date 2023-06-19
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include "largest_plus.h"

namespace valhalla {
    namespace matrices {
        namespace largest_plus {
            /*

            Given a square matrix of 0’s and 1’s, calculate the size of the largest plus
            formed by 1’s.

            Input:

            grid = [
                [1, 0, 1, 1, 1, 1, 0, 1, 1, 1],
                [1, 0, 1, 0, 1, 1, 1, 0, 1, 1],
                [1, 1, 1, 0, 1, 1, 0, 1, 0, 1],
                [0, 0, 0, 0, 1, 0, 0, 1, 0, 0],
                [1, 1, 1, 0, 1, 1, 1, 1, 1, 1],
                [1, 1, 1, 1, 1, 1, 1, 1, 1, 0],
                [1, 0, 0, 0, 1, 0, 0, 1, 0, 1],
                [1, 0, 1, 1, 1, 1, 0, 0, 1, 1],
                [1, 1, 0, 0, 1, 0, 1, 0, 0, 1],
                [1, 0, 1, 1, 1, 1, 0, 1, 0, 0]
            ]

            Output: 17

            Explanation: The largest plus of 1’s is marked below, having size 17.


                1  0  1  1  1  1  0  1  1  1
                1  0  1  0  |  1  1  0  1  1
                1  1  1  0  |  1  0  1  0  1
                0  0  0  0  |  0  0  1  0  0
                1  1  1  0  |  1  1  1  1  1
                –  –  –  –  |  –  –  –  –  0
                1  0  0  0  |  0  0  1  0  1
                1  0  1  1  |  1  0  0  1  1
                1  1  0  0  |  0  1  0  0  1
                1  0  1  1  |  1  0  1  0  0


            Input:

            [
                [1, 1, 1, 1, 1, 1],
                [1, 0, 1, 1, 0, 1],
                [0, 1, 1, 0, 0, 1],
                [1, 1, 1, 1, 1, 1],
                [1, 0, 0, 1, 0, 1],
                [1, 0, 1, 1, 0, 0]
            ]

            Output: 0

            Explanation: No largest plus of 1’s can be constructed.

            */

            int Solution::findLargestPlus(std::vector<std::vector<int>> const & grid) {
                int largest = -1;



                return largest;
            } // findLargestPlus
        }
    }
}
