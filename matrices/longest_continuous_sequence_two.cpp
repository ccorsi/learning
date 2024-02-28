/**
 * @file longest_continuous_sequence_two.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains a solution to the problem https://www.techiedelight.com/?problem=LongestContinuousSequenceII
 * @version 0.1
 * @date 2023-06-19
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include "longest_continuous_sequence_two.h"

namespace valhalla {
    namespace matrices {
        namespace longest_continuous_sequence_two {
            /*

            Given an `N × N` matrix where each cell has a distinct value in the 1 to `N × N`.
            Find the longest sequence formed by adjacent numbers in the matrix such that for
            each number, the number on the adjacent neighbor is +1 in its value.

            From the location (x, y) in the matrix, you can move to (x, y+1), (x, y-1),
            (x+1, y), or (x-1, y) if the value at the destination cell is one more than
            the value at source cell.

            Input:

            [
                [10, 13, 14, 21, 23],
                [11, 9,  22, 2,  3],
                [12, 8,  1,  5,  4],
                [15, 24, 7,  6,  20],
                [16, 17, 18, 19, 25]
            ]

            Output: [2, 3, 4, 5, 6, 7]

            Note: Assume that the input contains a single longest sequence.

            */

            void Solution::check(std::vector<std::vector<int>> const & mat, const int row,
                                 const int col, std::vector<int> & current, std::vector<int> & path) {
                bool found = false;
                const int next = mat[row][col] + 1;

                if (col + 1 < mat.size() && next == mat[row][col+1]) {
                    found = true;
                    current.push_back(next);
                    check(mat, row, col+1, current, path);
                    current.pop_back();
                } // if (col + 1 < mat.size() && next == mat[row][col+1])

                if (col > 0 && next == mat[row][col-1]) {
                    found = true;
                    current.push_back(next);
                    check(mat, row, col-1, current, path);
                    current.pop_back();
                } // if (col > 0 && next == mat[row][col-1])

                if (row > 0 && next == mat[row-1][col]) {
                    found = true;
                    current.push_back(next);
                    check(mat, row-1, col, current, path);
                    current.pop_back();
                } // if (row > 0 && next == mat[row-1][col])

                if (row + 1 < mat.size() && next == mat[row+1][col]) {
                    found = true;
                    current.push_back(next);
                    check(mat, row+1, col, current, path);
                    current.pop_back();
                } // if (row + 1 < mat.size() && next == mat[row+1][col])

                if (found == false) {
                    if (current.size() > path.size()) {
                        path = current;
                    } // if (current.size() > path.size())
                } // if (found == false)
            } // check

            std::vector<int> Solution::findLongestPath(std::vector<std::vector<int>> const & mat) {
                std::vector<int> path;

                if (mat.empty()) {
                    return path;
                } // if (mat.empty())

                const auto size = mat.size();
                std::vector<int> current;

                for (auto row = 0 ; row < size ; row++) {
                    for (auto col = 0 ; col < size ; col++) {
                        current.push_back(mat[row][col]);
                        check(mat, row, col, current, path);
                        current.pop_back();
                    } // for (auto col = 0 ; col < size ; col++)
                } // for (auto row = 0 ; row < size ; row++)

                return path;
            } // findLongestPath
        }
    }
}
