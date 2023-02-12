/**
 * @file spiral_matrix_two.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This is a solution to the problem https://www.techiedelight.com/?problem=SpiralMatrixII
 * @version 0.1
 * @date 2023-02-11
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include <iostream>

using std::cout;
using std::endl;

#include "spiral_matrix_two.h"

/*

Given a positive number `N`, return an `N × N` spiral matrix containing numbers from 1 to `N × N` in a counterclockwise direction.

Input: N = 5

Output:
[
	[25, 24, 23, 22, 21],
	[10, 9,  8,  7,  20],
	[11, 2,  1,  6,  19],
	[12, 3,  4,  5,  18],
	[13, 14, 15, 16, 17]
]

*/

std::vector<std::vector<int>> valhalla::matrices::spiral_matrix_two::Solution::spiralTraversal(int N) {
    std::vector<int> values(N);
    std::vector<std::vector<int>> spiral(N, values);

    int value = N * N;
    size_t top = 0, left = 0, right = N - 1, bottom = N - 1;

    while (value > 0) {
        // add to the top side of the matrix
        for (size_t idx = left; idx <= right; idx++)
        {
            spiral[top][idx] = value--;
        } // for
        if (value < 1) break;
        top++;

        // add to the right side of the matrix
        for (size_t idx = top; idx <= bottom; idx++)
        {
            spiral[idx][right] = value--;
        }
        right--;
        if (value < 1) break;

        // add to the bottom side of the matrix
        for (size_t idx = right; idx < N && idx >= left; idx--)
        {
            spiral[bottom][idx] = value--;
        }
        bottom--;
        if (value < 1) break;

        // add to the left side of the matrix
        for (size_t idx = bottom; idx < N && idx >= top; idx--)
        {
            spiral[idx][left] = value--;
        }
        left++;

    } // while

    return spiral;
}
