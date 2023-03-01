/**
 * @file fill_matrix.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains a solution to the problem https://www.techiedelight.com/?problem=FillMatrix
 * @version 0.1
 * @date 2023-02-28
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include <algorithm>

#include "fill_matrix.h"

/*

Given an `M × N` binary matrix, fill it with alternating rectangles of 1’s and 0’s.

Input: 10 × 8 matrix
Output:

[
	[1, 1, 1, 1, 1, 1, 1, 1],
	[1, 0, 0, 0, 0, 0, 0, 1],
	[1, 0, 1, 1, 1, 1, 0, 1],
	[1, 0, 1, 0, 0, 1, 0, 1],
	[1, 0, 1, 0, 0, 1, 0, 1],
	[1, 0, 1, 0, 0, 1, 0, 1],
	[1, 0, 1, 0, 0, 1, 0, 1],
	[1, 0, 1, 1, 1, 1, 0, 1],
	[1, 0, 0, 0, 0, 0, 0, 1],
	[1, 1, 1, 1, 1, 1, 1, 1]
]


Input: 3 × 5 matrix
Output:

[
	[1, 1, 1, 1, 1],
	[1, 0, 0, 0, 1],
	[1, 1, 1, 1, 1]
]

*/

void valhalla::matrices::fill_matrix::Solution::fillMatrix(std::vector<std::vector<int>> & mat) {
    if ( ! mat.empty() && ! mat[0].empty() ) {
        const std::vector<int>::size_type rows = mat.size(), cols = mat[0].size(),
			lrow = mat.size() - 1, lcol = mat[0].size() - 1;
		std::vector<int>::size_type row, col;

		for( row = 0 ; row < rows ; row++ ) {
			for ( col = 0 ; col < cols ; col++ ) {
				mat[row][col] = (std::min(std::min(row, lrow - row),std::min(col, lcol - col)) + 1) % 2;
			} // for
		} // for
    } // if
}
