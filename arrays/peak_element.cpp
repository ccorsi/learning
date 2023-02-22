/**
 * @file peak_element.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This is a solution to the problem https://www.techiedelight.com/?problem=PeakElement
 * @version 0.1
 * @date 2023-02-21
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include "peak_element.h"

/*

Given an integer array `A`, find the peak element in it. An element `A[i]` is a peak element if it's greater than its neighbor(s). i.e.,

• A[i-1] <= A[i] >= A[i+1]	(for 0 < i < n-1)
• A[i-1] <= A[i]			(if i = n – 1)
• A[i] >= A[i+1]			(if i = 0)


Input: [8, 9, 10, 12, 15]
Output: 15

Input: [10, 8, 6, 5, 3, 2]
Output: 10

• There might be multiple peak elements in an array, the solution should report any peak element.

Input: [8, 9, 10, 2, 5, 6]
Output: 10 or 6

Input: [8, 9, 2, 5, 6, 3]
Output: 9 or 6

• If the peak element is not located, the procedure should return -1.

Input: []
Output: -1

*/

int valhalla::arrays::peak_element::Solution::findPeakElement(std::vector<int> const & nums) {
    if (nums.empty()) return -1;

    if (nums.size() == 1) return nums[0];

    if (nums[0] >= nums[1]) return nums[0];

    if (nums[nums.size() - 2] <= nums.back()) return nums.back();

    size_t last = nums.size() - 1;
    for (size_t pos = 1 ; pos < last ; pos++) {
        if (nums[pos-1] <= nums[pos] && nums[pos] >= nums[pos+1]) {
            return nums[pos];
        } // if
    } // for

    return -1;
}
