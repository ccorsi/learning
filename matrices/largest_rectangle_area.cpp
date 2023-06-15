/**
 * @file largest_rectangle_area.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains a solution to the problem https://www.techiedelight.com/?problem=LargestRectangleArea
 * @version 0.1
 * @date 2023-06-13
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include "largest_rectangle_area.h"

namespace valhalla {
    namespace matrices {
        namespace largest_rectangle_area {
            /*

            Given a rectangular binary matrix, calculate the area of the largest rectangle of 1’s in it.
            Assume that a rectangle can be formed by swapping any number of columns with each other.

            Input:

            [
                [0, 1, 0, 1, 1],
                [1, 1, 0, 0, 1],
                [1, 1, 0, 1, 1],
                [1, 1, 1, 1, 1]
            ]

            Output: 9

            Explanation: The area of the largest rectangle of 1’s is 9. The largest rectangle of 1’s can
            be formed by swapping column 3 with column 5.

            [0, 1, 1, 1, 0]
            [1, 1, 1, 0, 0]
            [1, 1, 1, 1, 0]
            [1, 1, 1, 1, 1]


            Input:

            [
                [0, 1, 1, 0],
                [1, 0, 0, 1],
                [1, 1, 0, 1],
                [1, 1, 1, 1]
            ]

            Output: 6

            Explanation: The area of the largest rectangle of 1’s is 6. The largest rectangle of 1’s can
            be formed by swapping column 2 with column 4 or swapping column 3 with column 4.

            [0, 0, 1, 1]
            [1, 1, 0, 0]
            [1, 1, 0, 1]
            [1, 1, 1, 1]

            OR

            [0, 1, 0, 1]
            [1, 0, 1, 0]
            [1, 1, 1, 0]
            [1, 1, 1, 1]

            */

            int Solution::findLargestRectangleArea(std::vector<std::vector<int>> & mat) {
                int largest = -1;



                return largest;
            } // findLargestRectangleArea
        }
    }
}
