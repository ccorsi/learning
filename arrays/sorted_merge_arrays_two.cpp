/**
 * @file sorted_merge_arrays_two.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This is a solution to the problem https://www.techiedelight.com/?problem=SortedMergeArraysII
 * @version 0.1
 * @date 2023-02-11
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include "sorted_merge_arrays_two.h"

/*

Given two sorted integer arrays, merge them into a single array in decreasing order, and return it. In other words, merge two sorted arrays from their end.

Input : X = [1, 3, 5], Y = [2, 6, 7, 10]
Output: [10, 7, 6, 5, 3, 2, 1]

*/

std::vector<int> valhalla::arrays::sorted_merge_arrays_two::Solution::merge(std::vector<int> const & X, std::vector<int> const & Y) {
    std::vector<int> combined;

    const size_t x_size = X.size(), y_size = Y.size();
    size_t x_idx = x_size - 1, y_idx = y_size - 1;

    while (x_idx < x_size && y_idx < y_size) {
        if (X[x_idx] > Y[y_idx]) {
            combined.push_back(X[x_idx--]);
        } else {
            combined.push_back(Y[y_idx--]);
        } // else
    } // while

    while (x_idx < x_size) combined.push_back(X[x_idx--]);

    while (y_idx < y_size) combined.push_back(Y[y_idx--]);

    return combined;
}
