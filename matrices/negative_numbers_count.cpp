/**
 * @file negative_numbers_count.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains a solution to the problem https://www.techiedelight.com/?problem=NegativeNumbersCount
 * @version 0.1
 * @date 2023-02-27
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include "negative_numbers_count.h"

/*

Given an `M × N` row-wise and column-wise sorted integer matrix, find the total number of negative numbers in it in linear time.

Input:

[
	[-7, -3, -1, 3, 5],
	[-3, -2,  2, 4, 6],
	[-1,  1,  3, 5, 8],
	[ 3,  4,  7, 8, 9]
]

Output: 6

*/

int valhalla::matrices::negative_numbers_count::Solution::negativeCount(std::vector<std::vector<int>> const & mat) {
    int count = 0;

    if (mat.empty() || mat[0].empty()) return count;

    std::vector<int>::size_type last = mat[0].size(), col;

    for (std::vector<int>::size_type row = 0 ; last > 0 && row < mat.size() ; row++) {
        for (col = 0 ; col < last ; col++) {
            if (mat[row][col] > -1) break;
            count++;
        } // for
        last = col;
    } // for

    return count;
}
