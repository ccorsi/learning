/**
 * @file maximum_ones_row.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains a solution to the problem https://www.techiedelight.com/?problem=MaximumOnesRow
 * @version 0.1
 * @date 2023-03-01
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include "maximum_ones_row.h"

/*

Given a binary `M × N` row-wise sorted matrix, find a row that contains the maximum number of 1’s in linear time.

Input:
[
	[0, 0, 0, 1, 1],
	[0, 0, 1, 1, 1],
	[0, 0, 0, 0, 0],
	[0, 1, 1, 1, 1],
	[0, 0, 0, 0, 1]
]

Output: 4
Explanation: The maximum 1’s are present in row 4


If multiple rows have same maximum number of 1’s, the solution should return the first row number. If no 1’s are
present in the matrix, the solution should return 0.

Input:
[
	[1, 1, 1, 1],
	[1, 1, 1, 1],
	[1, 1, 1, 1],
]

Output: 1

*/

int valhalla::matrices::maximum_ones_row::Solution::findRow(std::vector<std::vector<int>> const & mat) {
    int max_row = 0;

    if ( ! mat.empty() && ! mat[0].empty()) {
        std::vector<std::vector<int>>::size_type max_row_idx = mat[0].size();
        for (std::vector<std::vector<int>>::size_type row = 0 ; row < mat.size() ; row++) {
            if (mat[row][max_row_idx - 1] == 1) {
                while (max_row_idx > 0 && mat[row][max_row_idx - 1] == 1)
                    max_row_idx--;
                if (max_row_idx == 0)
                    return row + 1;
                max_row = row + 1;
            } // if
        } // for
    } // if

    return max_row;
}
