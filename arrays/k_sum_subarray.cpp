/**
 * @file k_sum_subarray.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains a solution to the problem https://www.techiedelight.com/?problem=KSumSubarray
 * @version 0.1
 * @date 2023-03-15
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include "k_sum_subarray.h"

/*

Given an integer array, find a contiguous subarray having sum `k` in it where `k` is an integer.

Input : nums[] = [2, 6, 0, 9, 7, 3, 1, 4, 1, 10], k = 15
Output: [6, 0, 9]

Input : nums[] = [0, 5, -7, 1, -4, 7, 6, 1, 4, 1, 10], k = -3
Output: [1, -4] or [-7, 1, -4, 7]

Note: Since an input can contain several subarrays having sum `k`, the solution can return any one of them.

Input : nums[] = [0, 5, -7, 1, -4, 7, 6, 1, 4, 1, 10], k = 15
Output: [1, -4, 7, 6, 1, 4] or [4, 1, 10]

*/

std::vector<int> valhalla::arrays::k_sum_subarray::Solution::findSubarray(std::vector<int> const & nums, int k) {
    std::vector<int> results;

    const int size = nums.size();

    if (size > 0) {
        for (int start = 0 ; start < size ; start++) {
            checkSubArray(nums, k, results, nums[start], start);
        } // for
    } // if

    return results;
}

void valhalla::arrays::k_sum_subarray::Solution::checkSubArray(std::vector<int> const & nums, const int k, std::vector<int> & results, int sum, int start) {
    if (results.empty()) {
        if (sum == k) {
            results.push_back(nums[start]);
            return;
        } // if

        const int size = nums.size();

        for ( int end = start + 1 ;  end < size ; end++) {
            sum += nums[end];
            if (sum == k) {
                for (int idx = start ; idx <= end ; idx++)
                    results.push_back(nums[idx]);
                return;
            } // if
        } // for
    } // if
}
