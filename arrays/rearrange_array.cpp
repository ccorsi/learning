/**
 * @file rearrange_array.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This is a solution to the problem https://www.techiedelight.com/?problem=RearrangeArray
 * @version 0.1
 * @date 2023-02-05
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include "rearrange_array.h"

/*

Given an integer array, in-place rearrange it such that every second element becomes greater than its left and right elements.

• Assume that no duplicate elements are present in the input array.
• The solution should perform single traveral of the array.
• In case the multiple rearrangement exists, the solution can return any one of them.

Input : [1, 2, 3, 4, 5, 6, 7]
Output: [1, 3, 2, 5, 4, 7, 6] or [1, 5, 2, 6, 3, 7, 4], or any other valid combination..

Input : [6, 9, 2, 5, 1, 4]
Output: [6, 9, 2, 5, 1, 4] or [1, 5, 2, 6, 4, 9], or any other valid combination..

*/

void valhalla::arrays::rearrange_array::Solution::rearrange(std::vector<int> & nums) {
    for (std::vector<int>::size_type idx = 1 ; idx < nums.size() ; idx += 2) {
        if (nums[idx - 1] > nums[idx]) {
            int temp = nums[idx - 1];
            nums[idx - 1] = nums[idx];
            nums[idx] = temp;
        } // if
        if (idx + 1 < nums.size() && nums[idx] < nums[idx + 1]) {
            int temp = nums[idx];
            nums[idx] = nums[idx + 1];
            nums[idx + 1] = temp;
        } // if
    } // for
}
