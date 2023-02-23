/**
 * @file search_sorted_array.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This is a solution to the problem https://www.techiedelight.com/?problem=SearchSortedArray
 * @version 0.1
 * @date 2023-02-20
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include <iostream>

#include "search_sorted_array.h"

/*

Given a sorted integer array and a target, determine if the target exists in the array in logarithmic time. If target exists in the array, the procedure should return the index of it.

Input: nums[] = [2, 3, 5, 7, 9], target = 7
Output: 3
Explanation: Element found at 4th (index 3) position

• If there are duplicate elements in the array, the procedure may return any index whose element is equal to the target.

Input: nums[] = [1, 2, 3, 4, 4, 5, 6, 7], target = 4
Output: 3 (or 4)
Explanation: Element found at the 4th (index 3) or 5th (index 4) position.

• If the target is not located, the procedure should return -1.

Input: nums[] = [1, 4, 5, 8, 9], target = 2
Output: -1

*/

int valhalla::arrays::search_sorted_array::Solution::findIndex(std::vector<int> const & nums, int target) {

    // we could cheat and just use one of the binary searches that are part of the C++ standard but we won't
    // here and use a binary search implementation.

    std::vector<int>::size_type start = 0, end = nums.size() - 1;
    const std::vector<int>::size_type size = nums.size(); // we require this to be able to deal with setting end to -1

    while (start <= end && end < size) {
        std::vector<int>::size_type mid = (end + start) / 2;
        if (nums[mid] == target) {
            return mid;
        }

        if (nums[mid] > target) {
            end = mid - 1;
            continue;
        } // if

        start = mid + 1;
    } // while

    return -1;
}
