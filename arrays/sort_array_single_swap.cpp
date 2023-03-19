/**
 * @file sort_array_single_swap.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains a solution to the problem https://www.techiedelight.com/?problem=SortArraySingleSwap
 * @version 0.1
 * @date 2023-03-18
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include "sort_array_single_swap.h"

/*

Given an integer array where all its elements are sorted in increasing order except two
swapped elements, in-place sort it in linear time. Assume there are no duplicates in
the array.

Input : [3, 8, 6, 7, 5, 9] or [3, 5, 6, 9, 8, 7] or [3, 5, 7, 6, 8, 9]
Output: [3, 5, 6, 7, 8, 9]

*/

void valhalla::arrays::sort_array_single_swap::Solution::sortArray(std::vector<int> & nums) {
    const int size = nums.size();

    if (size > 1) {
        // first find an entry that is greater than the next entry
        int left = 1;

        while (left < size && nums[left - 1] < nums[left]) left++;

        if (left == size) return;

        // next find an entry that is less than the next entry
        int right = left;
        int min = nums[left];

        for (int idx = left + 1 ; idx < size ; idx++) {
            if (nums[idx] < min) {
                min = nums[idx];
                right = idx;
            } // if
        } // for

        int temp = nums[right];
        nums[right] = nums[left - 1];
        nums[left - 1] = temp;
    } // if
}
