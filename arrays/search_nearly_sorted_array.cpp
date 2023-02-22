/**
 * @file search_nearly_sorted_array.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This is a solution to the problem https://www.techiedelight.com/?problem=SearchNearlySortedArray
 * @version 0.1
 * @date 2023-02-21
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include <iostream>

#include "search_nearly_sorted_array.h"

/*

Given a nearly sorted array such that each of its elements may be misplaced by no more
than one position from the correct sorted order, efficiently search a given element in
it and return its index.

An element at index `i` in a correctly sorted order can be misplaced by the ±1 position,
i.e., it can be present at index `i-1` or `i` or `i+1` in the input array.

Input: nums[] = [2, 1, 3, 5, 4, 7, 6, 8, 9], target = 5
Output: 3
Explanation: Target 5 found at index 3

• If there are duplicate elements in the array, the procedure may return any index whose element is equal to the target.

Input: nums[] = [2, 1, 3, 5, 4, 5, 6, 8, 9], target = 5
Output: 3 (or 5)
Explanation: Target 5 found at index 3 and 5

• If the target is not located, the procedure should return -1.

Input: nums[] = [2, 1, 3, 5, 4, 7, 6, 8, 9], target = 10
Output: -1

*/

int valhalla::arrays::search_nearly_sorted_array::Solution::findIndex(std::vector<int> const & nums, int target) {
    std::cout << "input [";
    for (int num : nums)
        std::cout << " " << num;
    std::cout << " ]" << std::endl;
    // check the special case of size 1
    if (nums.size() == 1 && nums[0] == target) return 0;

    size_t start = 0, end = nums.size() - 1;
    const size_t size = nums.size();

    while (start < end && end < size) {
        size_t mid = (start + end) / 2;

        if (nums[mid] == target) {
            return mid;
        } else if (mid > start && nums[mid-1] == target) {
            return mid - 1;
        } else if (mid < end && nums[mid+1] == target) {
            return mid + 1;
        } // else if

        std::cout << "start: " << start << " end: " << end << " mid: " << mid << " nums[mid]: " << nums[mid];
        int max = nums[mid];
        if (mid > start && nums[mid-1] > max) {
            max = nums[mid-1];
            std::cout << " nums[mid-1]: " << max;
        } // if
        if (mid < end && nums[mid+1] < max) {
            max = nums[mid+1];
            std::cout << " nums[mid+1]: " << max;
        } // if

        std::cout << " max: " << max << " target: " << target;
        if (max > target) {
            end = mid - 1;
        } else {
            start = mid + 1;
        } // if
        std::cout << " start: " << start << "  end: " << end << std::endl;
    } // while

    return -1;
}
