/**
 * @file three_sum_two.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains a solution to the problem https://www.techiedelight.com/?problem=3SumII
 * @version 0.1
 * @date 2023-03-18
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include "three_sum_two.h"

/*

Given an unsorted integer array, find a triplet with a given sum `k` in it.

Input : [4, -1, 1, 2, -1], k = 0
Output: [-1, 2, -1]

Input : [4, 5, 4, -1, 3], k = 10
Output: []
Explanation: No triplet exists with sum 10.

If the input contains several triplets with sum `k`, the solution can return any one of them.

Input : nums[] = [2, 7, 4, 0, 9, 5, 1, 3], k = 6
Output: [0, 1, 5] or [0, 2, 4] or [1, 2, 3]

Note: The solution can return the triplet in any order, not necessarily as they appear in the array.

*/

std::vector<int> valhalla::arrays::three_sum_two::Solution::findTriplets(std::vector<int> & nums, int k) {
    std::vector<int> result;

    const int last = nums.size() - 2;

    for (int idx = 0 ; idx < last ; idx++) {
        if (isTriplets(nums, k, idx + 1, result, nums[idx], 1)) {
            result.push_back(nums[idx]); // add the first entry
            break;
        } // if
    } // for

    return result;
}

bool valhalla::arrays::three_sum_two::Solution::isTriplets(std::vector<int> & nums, const int k, const int start, std::vector<int> & result, const int sum, const int count) {
    if (count == 3) {
        return sum == k;
    } // if

    const int last = nums.size() - 2 + count;

    for (int idx = start ; idx < last ; idx++) {
        if (isTriplets(nums, k, idx + 1, result, sum + nums[idx], count + 1)) {
            result.push_back(nums[idx]); // add value to the list
            return true;
        } // if
    } // for

    return false;
}
