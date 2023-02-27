/**
 * @file diagonal_matrix_traversal.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains a solution to the problem https://www.techiedelight.com/?problem=DiagonalMatrixTraversal
 * @version 0.1
 * @date 2023-02-24
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include "diagonal_matrix_traversal.h"

/*

Given an `M × N` integer matrix, return all its diagonal elements having a positive slope.

Input:

[
	[1, 2, 3, 4, 5],
	[2, 3, 4, 5, 6],
	[3, 4, 5, 6, 7],
	[4, 5, 6, 7, 8],
	[5, 6, 7, 8, 9]
]

Output:

[
	[1]
	[2, 2],
	[3, 3, 3],
	[4, 4, 4, 4],
	[5, 5, 5, 5, 5],
	[6, 6, 6, 6],
	[7, 7, 7],
	[8, 8],
	[9]
]

*/

std::vector<std::vector<int>> valhalla::matrices::diagonal_matrix_traversal::Solution::diagonalTraversal(std::vector<std::vector<int>> const & mat) {
    std::vector<std::vector<int>> result;

    if (mat.empty()) return result;

    const std::vector<int>::size_type rows = mat.size(), cols = mat[0].size(), tots = rows + cols;

    for (std::vector<int>::size_type value = 1 ; value < tots ; value++) {
        // determine the starting point
        std::vector<int>::size_type row, col;

        if (value > rows) {
            row = rows - 1;
            col = value - rows;
        } else {
            row = value - 1;
            col = 0;
        } // if

        result.push_back(std::vector<int>()); // add a new vector to the result

        std::vector<int> & entries = result.back(); // get a reference to newly added vector

        do {
            entries.push_back(mat[row][col]); // add the entry

            if (row == 0) break;

            col++; // increment the col
            row--; // decrement the row

            if (col == cols) break;
        } while(true); // while
    } // for

    return result;
}
