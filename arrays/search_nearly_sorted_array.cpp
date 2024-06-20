/**
 * @file search_nearly_sorted_array.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This is a solution to the problem https://www.techiedelight.com/?problem=SearchNearlySortedArray
 * @version 0.2
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
    // std::cout << "input [";
    // for (int num : nums)
    //     std::cout << " " << num;
    // std::cout << " ]" << std::endl;
    // check the special case of size 1
    if (nums.size() == 1 && nums[0] == target) return 0;

    std::vector<int>::size_type start = 0, end = nums.size() - 1;
    const std::vector<int>::size_type size = nums.size();

    return findIndex(nums, target, 0, end, size);

    /*
        Version 1:  This version is almost correct but it doesn't handle all of the cases
                    that were used to test this solution.  It limits itself when determining
                    the pivot.

    while (start < end && end < size) {
        std::vector<int>::size_type mid = (start + end) / 2;

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
    */
}

int valhalla::arrays::search_nearly_sorted_array::Solution::findIndex(std::vector<int> const & nums, int target,
    std::vector<int>::size_type start, std::vector<int>::size_type end, std::vector<int>::size_type size) {

    if (start >= end || end >= size) return -1;

    std::vector<int>::size_type mid = (start + end) / 2;
    int value = nums[mid];

    int min = value, max = value;

    if (value == target) return mid;

    /*
        Version 2:  This solution takes the concept of a binary search a little further by using the
                    surrounding values to determine where to look next.  Since, the array is nearly
                    sorted then the values will be sorted closely together.  We then also include the
                    value to the left and right of the mid point as checks.  This will then result
                    with performing the search for three different cases. The two usual ones and the
                    possibility of performing the search on both halfs.  This will still take only
                    log(n) steps to find the solution.
    */

    // Check surrounding values of mid

    if (mid > start) {
        value = nums[mid-1];
        if (value == target) {
            return mid-1;
        }
        if (value < min) {
            min = value;
        } else if (value > max) {
            max = value;
        }
    }

    if (mid < end) {
        value = nums[mid+1];
        if (value == target) {
            return mid+1;
        }
        if (value < min) {
            min = value;
        } else if (value > max) {
            max = value;
        }
    }

    int index = -1;

    if (target < min) {
        index = findIndex(nums, target, start, mid - 1, size);
    }

    if (index > -1) return index;

    if (target > max) {
        index = findIndex(nums, target, mid + 1, end, size);
    }

    if (index > -1) return index;

    if (min < target && target < max) {
        index = findIndex(nums, target, start, mid - 1, size);

        if (index > -1) return index;

        index = findIndex(nums, target, mid + 1, end, size);
    }

    return index;
}