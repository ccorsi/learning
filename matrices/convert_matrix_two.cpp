/**
 * @file convert_matrix_two.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains a solution to the problem https://www.techiedelight.com/?problem=ConvertMatrixII
 * @version 0.1
 * @date 2023-02-23
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include "convert_matrix_two.h"
#include <iostream>
#include <set>

void display_matrix(std::vector<std::vector<int>> const & mat) {
	std::cout << "[" << std::endl;
	for (std::vector<int> const & values : mat) {
		std::cout << "[";
		for (int value : values)
			std::cout << " " << value;
		std::cout << " ]" << std::endl;
	} // for
	std::cout << "]" << std::endl;
}

/*

Given an `M × N` matrix of integers whose each cell can contain a negative, zero, or a
positive value, determine the minimum number of passes required to convert all negative
values in the matrix positive.

Only a non-zero positive value at cell (i, j) can convert negative values present at
its adjacent cells (i-1, j), (i+1, j), (i, j-1), and (i, j+1), i.e., up, down, left and
right.

Input:

mat = [
	[-1, -9,  0, -1,  0],
	[-8, -3, -2,  9, -7],
	[ 2,  0,  0, -6,  0],
	[ 0, -7, -3,  5, -4]
]

After pass 1:

	[-1, -9,  0,  1,  0],
	[ 8, -3,  2,  9,  7],
	[ 2,  0,  0,  6,  0],
	[ 0, -7,  3,  5,  4]

After pass 2:

	[ 1, -9,  0,  1,  0],
	[ 8,  3,  2,  9,  7],
	[ 2,  0,  0,  6,  0],
	[ 0,  7,  3,  5,  4]

After pass 3:

	[ 1,  9,  0,  1,  0],
	[ 8,  3,  2,  9,  7],
	[ 2,  0,  0,  6,  0],
	[ 0,  7,  3,  5,  4]

Output: 3


Input:

mat = [
	[1, 9, 1],
	[8, 3, 2],
	[7, 3, 4]
]

Output: 0


The solution should return -1 if conversion is not possible.

Input:

mat = [
	[-1, -9, -1],
	[-8, -3, -2],
	[-7, -3, -4]
]

Output: -1

*/

int valhalla::matrices::convert_matrix_two::Solution::findMinPasses(std::vector<std::vector<int>> & mat) {
    bool is_neg;
	std::set<std::pair<std::vector<int>::size_type, std::vector<int>::size_type>> change;
	int passes = -1;

	// std::cout << "Input: ";	display_matrix(mat);
	do {
	    is_neg = false; change.clear();
		const std::vector<std::vector<int>>::size_type row_size = mat.size();
		for (std::vector<std::vector<int>>::size_type row = 0 ; row < row_size ; row++) {
			const std::vector<int>::size_type col_size = mat[row].size();
			for (std::vector<int>::size_type col = 0 ; col < col_size ; col++) {
				const int value = mat[row][col];
				if (value > 0) {
					// update the surrounding values
					if (row > 0 && mat[row-1][col] < 0) {
						is_neg = true;
						change.insert(std::pair<std::vector<int>::size_type, std::vector<int>::size_type>(row-1,col));
					} // if
					if (row + 1 < row_size && mat[row+1][col] < 0) {
						is_neg = true;
						change.insert(std::pair<std::vector<int>::size_type, std::vector<int>::size_type>(row+1,col));
					} // if
					if (col > 0 && mat[row][col-1] < 0) {
						is_neg = true;
						change.insert(std::pair<std::vector<int>::size_type, std::vector<int>::size_type>(row,col-1));
					}
					if (col + 1 < col_size && mat[row][col+1] < 0) {
						is_neg = true;
						change.insert(std::pair<std::vector<int>::size_type, std::vector<int>::size_type>(row,col+1));
					}
				} else if (value < 0) {
					is_neg = true;
				} // else if
			} // for
		} // for
		for (std::pair<std::vector<int>::size_type, std::vector<int>::size_type> indices : change) {
			mat[indices.first][indices.second] *= -1;
		} // for
		// std::cout << "Updated: ";	display_matrix(mat);
		if (!change.empty() ||(!is_neg && change.empty())) passes++;
	} while (!change.empty() && is_neg);

    return passes;
}
