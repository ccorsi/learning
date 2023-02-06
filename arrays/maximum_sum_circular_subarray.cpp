/**
 * @file maximum_sum_circular_subarray.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This is a solution to the problem https://www.techiedelight.com/?problem=MaximumSumCircularSubarray
 * @version 0.1
 * @date 2023-02-05
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include "maximum_sum_circular_subarray.h"

/*

Given a circular integer array, find a contiguous subarray with the largest sum in it.

Input : [2, 1, -5, 4, -3, 1, -3, 4, -1]
Output: 6
Explanation: Subarray with the largest sum is [4, -1, 2, 1] with sum 6.

Input : [8, -7, -3, 5, 6, -2, 3, -4, 2]
Output: 18
Explanation: Subarray with the largest sum is [5, 6, -2, 3, -4, 2, 8] with sum 18.

*/

int valhalla::arrays::maximum_sum_circular_subarray::Solution::findMaxSubarray(std::vector<int> & nums) {
    int max_sum = 0;
    const size_t size = nums.size();

    if (size < 2) return (size == 1) ? nums[0] : max_sum;

    max_sum = nums[0]; // set an initial max sum

    for (size_t idx = 0 ; idx < size ; idx++) {
        int current_max = nums[idx];
        if (current_max > max_sum) {
            max_sum = current_max;
        } // if
        for (size_t i = (idx + 1) % size ; i != idx ; i = (i + 1) % size) {
            current_max += nums[i];
            if (current_max > max_sum) {
                max_sum = current_max;
            } // if
        } // for
    } // for

    return max_sum;
}
