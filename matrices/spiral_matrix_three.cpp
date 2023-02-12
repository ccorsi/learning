/**
 * @file spiral_matrix_three.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This is a solution to the problem https://www.techiedelight.com/?problem=SpiralMatrixIII
 * @version 0.1
 * @date 2023-02-11
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include "spiral_matrix_three.h"

/*

Given an integer array containing `N × N` elements, construct an `N × N` matrix from it in spiral order.

Input: [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25]

Output:

[
	[ 1   2   3   4  5],
	[16  17  18  19  6],
	[15  24  25  20  7],
	[14  23  22  21  8],
	[13  12  11  10  9]
]

*/
std::vector<std::vector<int>> valhalla::matrices::spiral_matrix_three::Solution::createSpiralMatrix(std::vector<int> const & nums) {
    const size_t size = nums.size();
    const size_t N = static_cast<size_t>(sqrt(size));
    const size_t max  = N * N;

    std::vector<int> values(N);
    std::vector<std::vector<int>> spiral(N, values);

    size_t top = 0, left = 0, right = N - 1, bottom = N - 1, cnt = 0;

    while (cnt < max) {
        // process the top entries
        for (size_t idx = left; idx <= right; idx++) {
            spiral[top][idx] = nums[cnt++];
        } // for
        if (cnt >= max) break;
        top++;

        // process the right entries
        for (size_t idx = top; idx <= bottom; idx++) {
            spiral[idx][right] = nums[cnt++];
        } // for
        if (cnt >= max) break;
        right--;

        // process the bottom entries
        for (size_t idx = right; idx < N && idx >= left; idx--) {
            spiral[bottom][idx] = nums[cnt++];
        } // for
        if (cnt >= max) break;
        bottom--;

        // process the left entries
        for (size_t idx = bottom; idx >= top; idx--) {
            spiral[idx][left] = nums[cnt++];
        } // for
        left++;

    } // while

    return spiral;
}
