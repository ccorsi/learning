/**
 * @file smallest_subarray.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains a solution to the problem https://www.techiedelight.com/?problem=SmallestSubarray
 * @version 0.1
 * @date 2023-03-15
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include "smallest_subarray.h"

/*

Given an array of positive integers and a positive integer k, find the smallest contiguous
subarray length whose sum of elements is greater than k.

Input : [1, 2, 3, 4, 5, 6, 7, 8], k = 7
Output: 1
Explanation: The smallest subarray with sum > 20 is [8]

Input : [1, 2, 3, 4, 5, 6, 7, 8], k = 20
Output: 3
Explanation: The smallest subarray with sum > 20 is [6, 7, 8]

Input : [1, 2, 3, 4, 5, 6, 7, 8], k = 21
Output: 4
Explanation: The smallest subarray with sum > 20 is [4, 5, 6, 7]

Input : [1, 2, 3, 4, 5, 6, 7, 8], k = 40
Output: 0
Explanation: No subarray exists

*/

void checkSmallestSubarray(std::vector<int> const & nums, const int k, const int start, int & shortest) {
    const int size = nums.size();
    int sum = 0;

    for (int end = start ; end < size ; end++) {
        sum += nums[end];

        if (sum > k) {
            const int length = end - start + 1;
            if (shortest == 0 || (shortest > 0 && shortest > length)) {
                shortest = length;
                return;
            } // if
        } // if
    } // for
}

int valhalla::arrays::smallest_subarray::Solution::findSmallestSubarray(std::vector<int> const & nums, int k) {
    int shortest = 0;

    const int size = nums.size();

    if (size > 0) {
        for (int start = 0 ; start < size ; start++) {
            checkSmallestSubarray(nums, k, start, shortest);
        }
    } // if

    return shortest;
}
