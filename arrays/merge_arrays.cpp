/**
 * @file merge_arrays.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief 
 * @version 0.1
 * @date 2023-01-04
 * 
 * @copyright Copyright (c) 2023 Claudio Corsi
 * 
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include "merge_arrays.h"

#include <iostream>

std::ostream& operator<<(std::ostream& out, const std::vector<int> &values) {
    out << "[";

    for(int value : values)
        out << " " << value;

    out << ((values.empty()) ? "]" : " ]" );

    return out;
}

/*

Given two sorted integer arrays, `X[]` and `Y[]` of size `m` and `n` each, in-place merge elements of `X[]` with elements of array `Y[]` by maintaining the sorted order, i.e., fill `X[]` with the first `m` smallest elements and fill `Y[]` with remaining elements.

Input :

X[] = [1, 4, 7, 8, 10]
Y[] = [2, 3, 9]

Output:

X[] = [1, 2, 3, 4, 7]
Y[] = [8, 9, 10]

*/

void valhalla::arrays::merge_arrays::Solution::merge(std::vector<int>& X, std::vector<int>& Y) {
    // std::cout << "X: " << X << std::endl;
    // std::cout << "Y: " << Y << std::endl;
    std::vector<int>::size_type xidx = 0, yidx = 0;

    while (xidx < X.size() && yidx < Y.size()) {
        // std::cout << "X[xidx]: " << X[xidx] << ", xidx: " << xidx << ", Y[yidx]: " << Y[yidx] << ", yidx: " << yidx << std::endl;
        
        if (Y[yidx] < X[xidx]) {
            // swap
            int temp = X[xidx];
            X[xidx] = Y[yidx];
            Y[yidx] = temp;

            // std::cout << "Updated X: " << X << std::endl;
            // std::cout << "Updated Y: " << Y << std::endl;

            std::vector<int>::size_type last = Y.size() - 1;

            for(std::vector<int>::size_type idx = yidx ; idx < last && Y[idx] > Y[idx+1]; idx++) {
                // std::cout << "idx: " << idx << ", last: " << last << std::endl;
                temp = Y[idx];
                Y[idx] = Y[idx+1];
                Y[idx+1] = temp;
                // std::cout << "Updated Y: " << Y << std::endl;
            } // for

            // std::cout << "Updated X: " << X << std::endl;
            // std::cout << "Updated Y: " << Y << std::endl;

        } else {
            // increment the x index
            xidx++;
        }
    } // while
}