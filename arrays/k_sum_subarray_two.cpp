/**
 * @file k_sum_subarray_two.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains a solution to the problem https://www.techiedelight.com/?problem=KSumSubarrayII
 * @version 0.1
 * @date 2023-03-15
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include "k_sum_subarray_two.h"

/*

Given an integer array, find all contiguous subarrays with a given sum `k`.

Input : nums[] = [3, 4, -7, 1, 3, 3, 1, -4], k = 7
Output: {[3, 4], [3, 4, -7, 1, 3, 3], [1, 3, 3], [3, 3, 1]}

Since the input can have multiple subarrays with sum `k`, the solution should return a set containing
all the distinct subarrays.

*/

void checkSubarray(std::vector<int> const & nums, const int k, std::set<std::vector<int>> & results, const int start) {
    int sum = 0;

    const int size = nums.size();

    for (int idx = start ; idx < size ; idx++) {
        sum += nums[idx];

        if (sum == k) {
            results.insert(std::vector<int>(nums.begin() + start, nums.begin() + idx + 1));
        } // if
    } // for
}

std::set<std::vector<int>> valhalla::arrays::k_sum_subarray_two::Solution::getAllSubarrays(std::vector<int> const & nums, int k) {
    std::set<std::vector<int>> results;

    const int size = nums.size();

    if (size > 0) {
        for (int start = 0 ; start < size ; start++) {
            checkSubarray(nums, k, results, start);
        } // for
    } // if

    return results;
}
