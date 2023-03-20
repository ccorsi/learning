/**
 * @file maximum_path_sum.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains a solution to the problem https://www.techiedelight.com/?problem=MaximumPathSum
 * @version 0.1
 * @date 2023-03-15
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include "maximum_path_sum.h"

#include <climits>

/*

Given two sorted arrays of integers, find a maximum sum path involving elements of both
arrays whose sum is maximum. You can start from either array, but can switch between
arrays only through its common elements.

Input:

X = [3, 6, 7, 8, 10, 12, 15, 18, 100]
Y = [1, 2, 3, 5, 7, 9, 10, 11, 15, 16, 18, 25, 50]

Output: The maximum sum is 199

Explanation: The maximum sum path is 1 —> 2 —> 3 —> 6 —> 7 —> 9 —> 10 —> 12 —> 15 —> 16 —> 18 —> 100

*/

int valhalla::arrays::maximum_path_sum::Solution::findMaxPathSum(std::vector<int> const & X, std::vector<int> const & Y) {
    const int xsize = X.size(), ysize = Y.size();
    int max_sum = 0;

    if (xsize == 0 || ysize == 0) {
        for (int value : X) {
            max_sum += value;
        } // for
        for (int value : Y) {
            max_sum += value;
        } // for
        return max_sum;
    } // if

    max_sum = INT_MIN;

    int start = 0;
    while (start < ysize && Y[start] < X[0]) {
        start++;
    } // while
    checkPath(X, Y, 0, start, 0, max_sum);

    start = 0;
    while (start < xsize && X[start] < Y[0]) {
        start++;
    } // while
    checkPath(Y, X, 0, start, 0, max_sum);

    return max_sum;
}

#include <iostream>

void valhalla::arrays::maximum_path_sum::Solution::checkPath(std::vector<int> const & lnums, std::vector<int> const & rnums, int l_idx, int r_idx, int sum, int & max_sum) {
    const int lsize = lnums.size(), rsize = rnums.size();

    if (l_idx == lsize) {
        l_idx--;
        if (l_idx > -1) {
            while (r_idx < rsize && rnums[r_idx] <= lnums[l_idx]) {
                r_idx++;
            } // while
            while (r_idx < rsize) {
                sum += rnums[r_idx++];
            } // while
        } // if
        if (sum > max_sum) {
            max_sum = sum;
        } // if
        // we are done
        return;
    } // if

    std::cout << "Adding " << lnums[l_idx] << " + " << sum;
    sum += lnums[l_idx];
    std::cout << " = " << sum << std::endl;

    if (r_idx < rsize && lnums[l_idx] == rnums[r_idx]) {
        checkPath(lnums, rnums, l_idx + 1, r_idx, sum, max_sum);
        checkPath(rnums, lnums, r_idx + 1, l_idx, sum, max_sum);
    } else {
        l_idx++; // move to next entry
        // look for the first value in rnums that is also contained within lnums
        while (l_idx < lsize && r_idx < rsize && lnums[l_idx] != rnums[r_idx]) {
            if (lnums[l_idx] < rnums[r_idx]) {
                sum += lnums[l_idx++];
            } else {
                r_idx++;
            } // else
        } // while

        if (l_idx == lsize) {
            std::cout << "Comparing sum " << sum << " to max sum " << max_sum << std::endl;
            if (sum > max_sum) {
                max_sum = sum;
            } // if
        } else {
            checkPath(lnums, rnums, l_idx, r_idx, sum, max_sum);
            checkPath(rnums, lnums, r_idx, l_idx, sum, max_sum);
        } // else
    } // else
}
