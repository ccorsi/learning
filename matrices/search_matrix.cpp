/**
 * @file search_matrix.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains a solution to the problem https://www.techiedelight.com/?problem=SearchMatrix
 * @version 0.1
 * @date 2023-03-03
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include "search_matrix.h"

/*

Given an `M × N` integer matrix, which is row-wise and column-wise sorted (with all strictly increasing
elements in any row or column), report the coordinates of all occurrences of a given element in it in
linear time.

Input:

matrix =
[
	[-4, -3, -1, 3, 5],
	[-3, -2, 2, 4, 6],
	[-1, 1, 3, 5, 8],
	[3, 4, 7, 8, 9]
]

target = 3

Output: {(0, 3), (2, 2), (3, 0)}

*/

std::set<std::pair<int,int>> valhalla::matrices::search_matrix::Solution::findElement(std::vector<std::vector<int>> const & mat, int target) {
    std::set<std::pair<int,int>> points;

    if ( ! mat.empty() && ! mat[0].empty()) {
        std::vector<int>::size_type last = mat[0].size() - 1, row = 0;
        for ( ; row < mat.size() ; row++) {
            while (last > 0 && mat[row][last] > target) {
                last--;
            } // while
            if (mat[row][last] == target) {
                points.insert(std::pair(row,last));
            } // if
            // Only decrement last if it is greater than target
            if (mat[row][last] > target && last > 0) {
                // only decrement the last index if it is greater than the target
                last--;
            } // if
        } // for
    } // if

    return points;
}
