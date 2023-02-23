/**
 * @file sorted_merge_arrays.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This is a solution to the problem 
 * @version 0.1
 * @date 2023-02-11
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include "sorted_merge_arrays.h"

/*

Given two integer arrays, each of which is sorted in increasing order, merge them into a single array in increasing order, and return it.

Input: X = [1, 3, 5, 7], Y = [2, 4, 6]
Output: [1, 2, 3, 4, 5, 6, 7]

*/

std::vector<int> valhalla::arrays::sorted_merge_arrays::Solution::merge(std::vector<int> const & X, std::vector<int> const & Y) {
    std::vector<int> combined;

    std::vector<int>::size_type x_idx = 0, y_idx = 0;
    const std::vector<int>::size_type x_size = X.size(), y_size = Y.size();

    while (x_idx < x_size && y_idx < y_size) {
        if (X[x_idx] < Y[y_idx]) {
            combined.push_back(X[x_idx++]);
        } else {
            combined.push_back(Y[y_idx++]);
        } // else
    } // while

    while (x_idx < x_size) combined.push_back(X[x_idx++]);

    while (y_idx < y_size) combined.push_back(Y[y_idx++]);

    return combined;
}
