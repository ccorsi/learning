/**
 * @file longest_continuous_sequence_three.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains a solution to the problem https://www.techiedelight.com/?problem=LongestContinuousSequenceIII
 * @version 0.1
 * @date 2023-06-19
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include "longest_continuous_sequence_three.h"

namespace valhalla {
    namespace matrices {
        namespace longest_continuous_sequence_three {
            /*

            Given an `M × N` matrix of characters, find the length of the longest path in
            the matrix starting from a given character. All characters in the longest path
            should be increasing and consecutive to each other in alphabetical order.

            You are allowed to search the string in all eight possible directions, i.e.,
            North, West, South, East, North-East, North-West, South-East, South-West.

            Input:

            mat = [
                ['D', 'E', 'H', 'X', 'B'],
                ['A', 'O', 'G', 'P', 'E'],
                ['D', 'D', 'C', 'F', 'D'],
                ['E', 'B', 'E', 'A', 'S'],
                ['C', 'D', 'Y', 'E', 'N']
            ]
            ch = 'C'

            Output: 6

            Explanation: The longest path with consecutive characters starting from character
            `C` is: C(2, 2) —> D(2, 1) —> E(3, 2) —> F(2, 3) —> G(1, 2) —> H(0, 2)


            Input:

            mat = [
                ['A', 'B', 'C'],
                ['D', 'E', 'F']
            ]
            ch = 'I'

            Output: 0

            */

            int Solution::findMaxLength(std::vector<std::vector<char>> const & mat, char ch) {
                int max = -1;



                return max = -1;
            } // findMaxLength
        }
    }
}
