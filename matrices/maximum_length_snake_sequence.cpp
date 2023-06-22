/**
 * @file maximum_length_snake_sequence.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains a solution to the problem https://www.techiedelight.com/?problem=MaximumLengthSnakeSequence
 * @version 0.1
 * @date 2023-06-20
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include "maximum_length_snake_sequence.h"

namespace valhalla {
    namespace matrices {
        namespace maximum_length_snake_sequence {
            /*

            Given an integer square matrix, find the maximum length snake sequence in it and return
            its length. A snake sequence is defined as a sequence of numbers where each new number,
            which can only be located to the right or down of the current number, is either plus or
            minus one.

            You are only allowed to move either right or down from any cell in the matrix, provided
            that the new cell has value `±1` relative to the current cell.

            Input:

            grid = [
                [7, 5, 2, 3, 1],
                [3, 4, 1, 4, 4],
                [1, 5, 6, 7, 8],
                [3, 4, 5, 8, 9],
                [3, 2, 2, 7, 6]
            ]

            Output: 7

            Explanation: The maximum length snake sequence for the above matrix is
            [5, 4, 5, 6, 7, 8, 7, 6] or [3, 4, 5, 6, 7, 8, 7, 6].

            Note that the length of a snake sequence is one less than the count of numbers in it.

            */

            int Solution::findMaxLengthSnakeSequence(std::vector<std::vector<int>> const & grid) {
                int max = -1;



                return max;
            } // findMaxLengthSnakeSequence
        }
    }
}