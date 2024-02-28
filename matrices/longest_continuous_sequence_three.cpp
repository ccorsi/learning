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

            void Solution::check(std::vector<std::vector<char>> const & mat, const int row,
                                 const int col, const char ch, int len, int & max) {
                const char next = ch + 1;
                bool found = false;

                if (row > 0) {
                    if (col > 0 && mat[row-1][col-1] == next) {
                        check(mat, row-1, col-1, next, len+1, max);
                        found = true;
                    } // if (col > 0 && mat[row-1][col-1] == next)

                    if (mat[row-1][col] == next) {
                        check(mat, row-1, col, next, len+1, max);
                        found = true;
                    } // if (mat[row-1][col] == next)

                    if (col + 1 < mat[row].size() &&  mat[row-1][col+1] == next) {
                        check(mat, row-1, col+1, next, len+1, max);
                        found = true;
                    } // if (col + 1 < mat[row].size() &&  mat[row-1][col+1] == next)
                } // if (row > 0)

                if (col > 0 && mat[row][col-1] == next) {
                    check(mat, row, col-1, next, len+1, max);
                    found = true;
                } // if (col > 0 && mat[row][col-1] == next)

                if (col + 1 < mat[row].size() && mat[row][col+1] == next) {
                    check(mat, row, col+1, next, len+1, max);
                    found = true;
                } // if (col + 1 < mat[row].size() && mat[row][col+1] == next)

                if (row + 1 < mat.size()) {
                    if (col > 0 && mat[row+1][col-1] == next) {
                        check(mat, row+1, col-1, next, len+1, max);
                        found = true;
                    } // if (col > 0 && mat[row+1][col-1] == next)

                    if (mat[row+1][col] == next) {
                        check(mat, row+1, col, next, len+1, max);
                        found = true;
                    } // if (mat[row+1][col] == next)

                    if (col + 1 < mat[row+1].size() && mat[row+1][col+1] == next) {
                        check(mat, row+1, col+1, next, len+1, max);
                        found;
                    } // if (col + 1 < mat[row+1].size() && mat[row+1][col+1] == next)
                } // if (row + 1 < mat.size())

                if (found == false && len > max) {
                    max = len;
                } // if (found == false && len > max)
            } // check

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
                int max = 0;

                if (mat.empty()) {
                    return max;
                }

                const auto rows = mat.size(), cols = mat[0].size();

                for (auto row = 0 ; row < rows ; row++) {
                    for (auto col = 0 ; col < cols ; col++) {
                        if (mat[row][col] == ch) {
                            check(mat, row, col, ch, 1, max);
                        } // if (mat[row][col] == ch)
                    } // for (auto col = 0 ; col < cols ; col++)
                } // for (auto row = 0 ; row < rows ; row++)

                return max;
            } // findMaxLength
        }
    }
}
