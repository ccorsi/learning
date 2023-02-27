/**
 * @file toeplitz_matrix.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This is a solution to the problem https://www.techiedelight.com/?problem=ToeplitzMatrix
 * @version 0.1
 * @date 2023-02-27
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include "toeplitz_matrix.h"

/*

Given an `M × N` integer matrix, check if it is a Toeplitz matrix or not. A Toeplitz
matrix or diagonal-constant matrix is a matrix with each descending diagonal from left
to right is constant.

Any `M × N` matrix `mat` is a Toeplitz matrix if mat(i, j) = mat(i+1, j+1) = mat(i+2, j+2),
and so on… Here, mat(i, j) denotes the element mat[i][j] in the matrix.

Input:

[
	[3, 7, 0, 9, 8],
	[5, 3, 7, 0, 9],
	[6, 5, 3, 7, 0],
	[4, 6, 5, 3, 7]
]

Output: true

Input:

[
	[3, 7, 0, 9, 8],
	[5, 3, 7, 0, 9],
	[6, 5, 3, 7, 0],
	[4, 5, 5, 3, 7]
]

Output: false

*/

bool valhalla::matrices::toeplitz_matrix::Solution::checkToeplitz(std::vector<std::vector<int>> const & mat) {
    if (mat.size() > 1 && mat[0].size() > 1) {
        std::vector<int>::size_type last = mat.size() - 1;

        for (std::vector<int>::size_type row = 0 ; row < last ; row++) {
            std::vector<int>::size_type crow, ccol = 1;
            int value = mat[row][0];
            crow = row + 1;
            while (crow < mat.size() && ccol < mat[0].size()) {
                if (mat[crow][ccol] != value) return false;
                crow++; ccol++;
            } // while
        } // for

        last = mat[0].size() - 1;

        for (std::vector<int>::size_type col = 1 ; col < last ; col++) {
            std::vector<int>::size_type crow = 1, ccol;
            int value = mat[0][col];
            ccol = col + 1;
            while (crow < mat.size() && ccol < mat[0].size()) {
                if (mat[crow][ccol] != value) return false;
                crow++; ccol++;
            } // while
        } // for
    } // if

    return true;
}
