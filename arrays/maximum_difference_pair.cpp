/**
 * @file maximum_difference_pair.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This is a solution to the problem https://www.techiedelight.com/?problem=MaximumDifferencePair
 * @version 0.1
 * @date 2023-02-04
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include "maximum_difference_pair.h"

/*

Given an integer array, find the maximum difference between two elements in it such that the smaller
element appears before the larger element. If no such pair exists, return any negative number.

Input : [2, 7, 9, 5, 1, 3, 5]
Output: 7
Explanation: The pair with the maximum difference is (2, 9).

Input : [5, 4, 3, 2, 1]
Output: -1 (or any other negative number)
Explanation: No pair with the maximum difference exists.

*/

int valhalla::arrays::maximum_difference_pair::Solution::findMaxDiff(std::vector<int> &nums) {
    int result = -1;

    if (nums.size() < 2) {
        // nothing to do
        return result;
    } // if

    int min, max;

    min = max = nums[0];

    for (std::vector<int>::size_type idx = 1 ; idx < nums.size() ; idx++) {
        int value = nums[idx];

        if (value > max) {
            max = value;
            if (max - min > result)
                result = max - min;
        } else if (value < min) {
            // we need to reset everything
            min = max = value;
        } // else
    } // for

    return result;
}
