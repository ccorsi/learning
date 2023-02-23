/**
 * @file max_continuous_sequence.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This is the solution to the problem https://www.techiedelight.com/?problem=MaximumContinuousSequence
 * @version 0.1
 * @date 2023-01-21
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include "max_continuous_sequence.h"

/*

Given a binary array, find the index of 0 to be replaced with 1 to get the maximum length sequence of continuous ones. The solution should return the index of first occurence of 0, when multiple continuous sequence of maximum length is possible.

Input : [0, 0, 1, 0, 1, 1, 1, 0, 1, 1]
Output: 7
Explanation: Replace index 7 to get the continuous sequence of length 6 containing all 1’s.

Input : [0, 1, 1, 0, 0]
Output: 0
Explanation: Replace index 0 or 3 to get the continuous sequence of length 3 containing all 1’s. The solution should return the first occurence.

Input : [1, 1]
Output: -1
Explanation: Invalid Input (all 1’s)

*/
int valhalla::arrays::maximum_continuous_sequence::Solution::findIndexOfZero(std::vector<int> const &nums) {
    // check for empty array
    if (nums.empty()) return -1;

    std::vector<int>::size_type zero_idx = 0;

    // find first zero entry
    while (zero_idx < nums.size() && nums[zero_idx] == 1) zero_idx++;

    // no zero found then we are done
    if (zero_idx == nums.size()) return -1;

    int idx = -1;
    int max_len = 0;
    int left = 0, right = 0;

    while (zero_idx < nums.size()) {
        // assign the right index to the left index
        left = right;

        // save the prior zero_idx
        std::vector<int>::size_type last = zero_idx;

        // increment the zero_idx.
        zero_idx++;

        // find next zero entry
        while (zero_idx < nums.size() && nums[zero_idx] == 1) zero_idx++;

        // update the right index
        right = zero_idx - last - 1;

        // compare between the current max and this length
        if (max_len < (left + right + 1)) {
            idx = last;
            max_len = left + right + 1;
        } // if
    } // while

    return idx;
}
