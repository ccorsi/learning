/**
 * @file maximum_sum_subarray.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This is a solution to the problem https://www.techiedelight.com/?problem=MaximumSumSubarray
 * @version 0.1
 * @date 2023-02-05
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include "maximum_sum_subarray.h"

/*

Given an integer array, find the maximum sum among all its subarrays.

Input : [-2, 1, -3, 4, -1, 2, 1, -5, 4]
Output: 6
Explanation: The maximum sum subarray is [4, -1, 2, 1]

Input : [-7, -3, -2, -4]
Output: -2
Explanation: The maximum sum subarray is [-2]

Input : [-2, 2, -1, 2, 1, 6, -10, 6, 4, -8]
Output: 10
Explanation: The maximum sum subarray is [2, -1, 2, 1, 6] or [6, 4] or [2, -1, 2, 1, 6, -10, 6, 4]

*/

int valhalla::arrays::maximum_sum_subarray::Solution::findMaxSubarraySum(std::vector<int> const &nums) {
    int max_sum = 0;
    const std::vector<int>::size_type size = nums.size();

    if (size < 2) return (size == 1) ? nums[0] : max_sum;

    max_sum = nums[0]; // set an initial max sum

    for (std::vector<int>::size_type idx = 0 ; idx < size ; idx++) {
        int current_max = nums[idx];
        if (current_max > max_sum) {
            max_sum = current_max;
        } // if
        for (std::vector<int>::size_type i = idx + 1 ; i < size ; i++) {
            current_max += nums[i];
            if (current_max > max_sum) {
                max_sum = current_max;
            } // if
        } // for
    } // for

    return max_sum;
}
