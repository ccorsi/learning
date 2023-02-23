/**
 * @file count_ones.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains a solution to the problem https://www.techiedelight.com/?problem=CountOnes
 * @version 0.1
 * @date 2023-02-21
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include <iostream>

#include "count_ones.h"

/*

Given a sorted binary array, efficiently count the total number of 1's in it.

Input: [0, 0, 0, 0, 1, 1, 1]
Output: 3

Input: [0, 0, 1, 1, 1, 1, 1]
Output: 5

*/

int valhalla::arrays::count_ones::Solution::countOnes(std::vector<int> const & nums) {
    if (nums.empty() || nums.back() == 0) return 0;

    if (nums.front() == 1) return nums.size();

    std::vector<int>::size_type start = 0, end = nums.size() - 1;
    const std::vector<int>::size_type size = nums.size();

    while (start < end && end < size) {
        std::vector<int>::size_type mid = (start + end) / 2;
        if (nums[mid] == 0) {
            start = mid + 1;
        } else {
            end = mid - 1;
        } // else
    } // while

    if (nums[start] == 0) start++;

    return size - start;
}
