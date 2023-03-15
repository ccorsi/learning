/**
 * @file minimum_sum_subarray.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains a solution to the problem https://www.techiedelight.com/?problem=MinimumSumSubarray
 * @version 0.1
 * @date 2023-03-14
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include "minimum_sum_subarray.h"

/*

Given an integer array and a positive integer `k`, find the minimum sum contiguous subarray of size `k`.

Input : nums[] = [10, 4, 2, 5, 6, 3, 8, 1], k = 3
Output: [4, 2, 5]

Input : nums[] = [1, 4, 5, 3, 8], k = 6
Output: [1, 4, 5, 3, 8]

Note: Since an input can contain several minimum sum subarrays of size `k`, the solution can return any one of them.

*/

std::vector<int> valhalla::arrays::minimum_sum_subarray::Solution::findMinSumSubarray(std::vector<int> const & nums, int k) {
    if (static_cast<int>(nums.size()) <= k) {
        return nums;
    } // if

    int sum = 0, idx = 0;

    for ( ; idx < k ; idx++ ) {
        sum += nums[idx];
    } // for

    int min_sum = sum, end = k - 1;

    const int size = nums.size();

    for ( ; idx < size ; idx++) {
        sum += nums[idx];
        sum -= nums[idx-k];
        if (min_sum > sum) {
            min_sum = sum;
            end = idx;
        } // if
    } // for

    std::vector<int> minSumSubarray;

    end -= k; end++;

    while (k-- > 0)
        minSumSubarray.push_back(nums[end++]);

    return minSumSubarray;
}
