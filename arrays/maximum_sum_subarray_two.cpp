/**
 * @file maximum_sum_subarray_two.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This is a solution to the problem https://www.techiedelight.com/?problem=MaximumSumSubarrayII
 * @version 0.1
 * @date 2023-02-05
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include "maximum_sum_subarray_two.h"

/*

Given an integer array, find a contiguous subarray within it that has the maximum sum.

Input : [-2, 1, -3, 4, -1, 2, 1, -5, 4]
Output: [4, -1, 2, 1]

Input : [-7, -3, -2, -4]
Output: [-2]

In case multiple subarrays exists with the largest sum, the solution can return any one of them.

Input : [-2, 2, -1, 2, 1, 6, -10, 6, 4, -8]
Output: [2, -1, 2, 1, 6] or [6, 4] or [2, -1, 2, 1, 6, -10, 6, 4]

*/

std::vector<int> valhalla::arrays::maximum_sum_subarray_two::Solution::findMaxSumSubarray(std::vector<int> const & nums) {
    std::vector<int> sum;

    const size_t size = nums.size();

    if (size < 2) return (size == 1) ? nums : sum;

    int max_sum = nums[0]; // set an initial max sum
    size_t max_start = 0, max_end = 0;

    for (size_t idx = 0 ; idx < size ; idx++) {
        int current_max = nums[idx];
        if (current_max > max_sum) {
            max_sum = current_max;
            max_start = max_end = idx;
        } // if
        for (size_t i = idx + 1 ; i < size ; i++) {
            current_max += nums[i];
            if (current_max > max_sum) {
                max_sum = current_max;
                max_start = idx;
                max_end = i;
            } // if
        } // for
    } // for

    sum.insert(sum.begin(), nums.begin() + max_start, nums.begin() + max_end + 1);

    return sum;
}
