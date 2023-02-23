/**
 * @file spiral_matrix.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This is the solution of the problem https://www.techiedelight.com/?problem=SpiralMatrix
 * @version 0.1
 * @date 2023-02-11
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include <iostream>

#include "spiral_matrix.h"

/*

Given an `M × N` integer matrix, return its elements in spiral order.

Input:

[
	[ 1   2   3   4  5],
	[16  17  18  19  6],
	[15  24  25  20  7],
	[14  23  22  21  8],
	[13  12  11  10  9]
]

Output: [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25]

*/

std::vector<int> valhalla::matrices::spiral_matrix::Solution::spiralTraversal(std::vector<std::vector<int>> const & mat) {
    std::vector<int> spiral;

    if (mat.empty()) return spiral;

    std::vector<int>::size_type top = 0, right = mat[0].size() - 1, bottom = mat.size() - 1, left = 0;
    const std::vector<int>::size_type size = mat.size() * mat[0].size();

    while (spiral.size() < size) {
        // copy entries from top to right into spiral
        for (std::vector<int>::size_type idx = left ; idx <= right ; idx++) {
            // std::cout << "top: " << top << ", idx: " << idx << ", size: " << ( spiral.size() + 1 ) << ", entry: " <<  mat[top][idx] << std::endl;
            spiral.push_back(mat[top][idx]);
        } // for
        if (spiral.size() >= size) break;
        top++;

        // copy entries from right top to right bottom
        for (std::vector<int>::size_type idx = top; idx <= bottom; idx++)
        {
            // std::cout << "right: " << right << ", idx: " << idx << ", size: " << ( spiral.size() + 1 ) << ", entry: " <<  mat[idx][right] << std::endl;
            spiral.push_back(mat[idx][right]);
        } // for
        if (spiral.size() >= size) break;
        right--;

        // copy entries from bottom right to bottom left
        for (std::vector<int>::size_type idx = right; idx < mat.size() && left <= idx; idx--)
        {
            // std::cout << "bottom: " << bottom << ", idx: " << idx << ", size: " << ( spiral.size() + 1 ) << ", entry: " <<  mat[bottom][idx] << std::endl;
            spiral.push_back(mat[bottom][idx]);
        } // for
        if (spiral.size() >= size) break;
        bottom--;

        // copy entries from bottom left to top left
        for (std::vector<int>::size_type idx = bottom; idx >= top; idx--)
        {
            // std::cout << "left: " << left << ", idx: " << idx << ", size: " << ( spiral.size() + 1 ) << ", entry: " <<  mat[left][idx] << std::endl;
            spiral.push_back(mat[idx][left]);
        } // for
        left++;

    } // while

    return spiral;
}
