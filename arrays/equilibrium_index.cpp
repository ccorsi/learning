/**
 * @file equilibrium_index.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This is a solution to the problem https://www.techiedelight.com/?problem=EquilibriumIndex
 * @version 0.1
 * @date 2023-01-25
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include "equilibrium_index.h"

/*

Given an integer array, return all equilibrium index in it. For an array `A[0..n-1]`, index `i` is an equilibrium index if the sum of elements of subarray `A[0…i-1]` is equal to the sum of elements of subarray `A[i+1…n-1]`.

Input : [0, -3, 5, -4, -2, 3, 1, 0]
Output: {0, 3, 7}
Explanation: For each index `i` in the output, A[0] + A[1] + … + A[i-1] = A[i+1] + A[i+2] + … + A[n-1]

Input : [-7, 3, 7, -3, 1]
Output: {4}
Explanation: `n-1` is an equilibrium index if A[0] + A[1] + … + A[n-2] sums to 0.

Input : [1, 2, -4, 2]
Output: {0}
Explanation: 0 is an equilibrium index if A[1] + A[2] + … + A[n-1] sums to 0.

*/
std::unordered_set<int> valhalla::arrays::equilibrium_index::Solution::find_index(std::vector<int> const &nums) {
    std::unordered_set<int> indices;

    if (nums.empty()) return indices;

    // store the left side and right side sums
    long left = 0, right = 0;

    // sum up the right side of the calculation
    for (size_t idx = 1 ; idx < nums.size() ; idx++)
        right += nums[idx];

    // check if it is zero
    if (right == 0) {
        // add zero index to indices
        indices.insert(0);
    }

    for (size_t idx = 1 ; idx < nums.size() ; idx++) {
        // increment the prior value to the left...
        left += nums[idx - 1];
        // and decrement the current index value to the right
        right -= nums[idx];
        // check if they are equal
        if (left == right) {
            // add index to indicies
            indices.insert(idx);
        }
    }

    return indices;
}
