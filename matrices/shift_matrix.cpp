/**
 * @file shift_matrix.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief 
 * @version 0.1
 * @date 2023-01-01
 * 
 * @copyright Copyright (c) 2023 Claudio Corsi
 * 
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include "shift_matrix.h"

/*

Given an `M × N` integer matrix, shift all its elements by `1` in spiral order.

Input:

[
	[ 1,  2,  3,  4, 5],
	[16, 17, 18, 19, 6],
	[15, 24, 25, 20, 7],
	[14, 23, 22, 21, 8],
	[13, 12, 11, 10, 9]
]

Output:

[
	[25,  1,  2,  3, 4],
	[15, 16, 17, 18, 5],
	[14, 23, 24, 19, 6],
	[13, 22, 21, 20, 7],
	[12, 11, 10,  9, 8]
]

*/

#include <iostream>

template<typename E>
std::ostream& operator<<(std::ostream& out, const std::vector<E>& values) {
	out << "[";
	
	for(E value : values) {
		out << " " << value;
	}

	if (values.empty() == false)
		out << " ";
	out << "]";

	return out;
}

#include <assert.h>

/*
 0,0 -> 0,1 -> 0,2 -> 1,2 -> 2,2 -> 2,1 -> 2,0 -> 1,0 -> 1,1 -> 0,0
*/
void valhalla::matrices::shift_matrix::Solution::shift_matrix(std::vector<std::vector<int>> &values) {
	if (values.empty()) {
		// nothing to do thus return 
		return;
	}

	int next = values[0][0];
	std::vector<int>::size_type cols = values[0].size(), rows = values.size();
	std::vector<int>::size_type row = 0, col = 0;
	std::vector<int>::size_type rend, dend, lend, uend;
	rend = cols - 1;
	dend = rows - 1;
	lend = 0;
	uend = 1;

	std::vector<int>::size_type xend, yend;
	xend = rows / 2;
	yend = cols / 2 - (cols % 2 == 0) ? 1 : 0;

	std::vector<int>::size_type cnt = 1, size = rows * cols;

	std::cout << "Initial matrix" << std::endl;
	std::cout << values << std::endl;
	std::cout << "[rows,cols]: [" << rows << "," << cols << "]" << std::endl; 
	std::cout << "[rend,dend,lend,uend]: [" << rend << "," << dend << "," << lend << "," << uend << "]" << std::endl; 
	std::cout << "values[row][col]: " << values[row][col] << " [row,col]: [" << row << "," << col << "]" << std::endl; 
	next = values[row][col];
	// Go through the entries within the matrix
	while (cnt < size) {
		std::cout << "Phase 1 row: " << row << ", col: " << col << std::endl;
		// left to right
		while (col < rend) {
			col++;
			std::cout << "\tnext: " << next << " [row,col]: [" << row << "," << col << "]" << std::endl;
			int temp = next;
			assert( row < rows );
			assert( col < cols );
			next = values[row][col];
			values[row][col] = temp;
			cnt++;
		}
		col = rend;
		std::cout << "Phase 2 row: " << row << ", col: " << col << std::endl;
		if (cnt >= size) break;
		// decrement the rend
		rend--;
		// up to down
		while (row < dend) {
			row++;
			std::cout << "\tnext: " << next << " [row,col]: [" << row << "," << col << "]" << std::endl;
			int temp = next;
			assert( row < rows );
			assert( col < cols );
			next = values[row][col];
			values[row][col] = temp;
			cnt++;
		}
		row = dend;
		std::cout << "Phase 3 row: " << row << ", col: " << col << std::endl;
		if (cnt >= size) break;
		// decrement the dend
		dend--;
		// right to left
		while (col > lend) {
			col--;
			std::cout << "\tnext: " << next << " [row,col]: [" << row << "," << col << "]" << std::endl;
			int temp = next;
			assert( row < rows );
			assert( col < cols );
			next = values[row][col];
			values[row][col] = temp;
			cnt++;
		}
		col = lend;
		std::cout << "Phase 4 row: " << row << ", col: " << col << std::endl;
		if (cnt >= size) break;
		// increment the lend
		lend++;
		// down to up
		while (row > uend) {
			row--;
			std::cout << "\tnext: " << next << " [row,col]: [" << row << "," << col << "]" << std::endl;
			int temp = next;
			assert( row < rows );
			assert( col < cols );
			next = values[row][col];
			values[row][col] = temp;
			cnt++;
		}
		row = uend;
		// increment the uend
		uend++;
		std::cout << "Phase 5 row: " << row << ", col: " << col << std::endl;
	}
	std::cout << "\tnext: " << next << " [row,col]: [" << 0 << "," << 0 << "]" << std::endl;
	values[0][0] = next;
	std::cout << "Updated matrix" << std::endl;
	std::cout << values << std::endl;
}
 