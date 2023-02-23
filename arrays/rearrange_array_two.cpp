/**
 * @file rearrange_array_two.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This is a solution to the problem https://www.techiedelight.com/?problem=RearrangeArrayII
 * @version 0.1
 * @date 2023-02-06
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include <iostream>

#include "rearrange_array_two.h"

/*

Given an integer array, in-place rearrange it such that it contains positive and negative numbers at alternate positions. Assume that all values in the array are non-zero.

• In case the multiple rearrangement exists, the solution can return any one of them.

Input : [9, -3, 5, -2, -8, -6, 1, 3]
Output: [9, -3, 5, -2, 1, -8, 3, -6] or [5, -2, 9, -6, 1, -8, 3, -3] or any other valid combination..

• If the array contains more positive or negative elements, the solution should move them to the end of the array.

Input : [9, -3, 5, -2, -8, -6]
Output: [5, -2, 9, -6, -3, -8] or [-2, 5, -6, 9, -3, -8] or any other valid combination..

Input : [5, 4, 6, -1, 3]
Output: [5, -1, 4, 6, 3] or [-1, 5, 4, 6, 3] or any other valid combination..

*/

void valhalla::arrays::rearrange_array_two::Solution::rearrange(std::vector<int> & nums) {
    std::vector<int>::size_type dest = 0, src = 0;
    const std::vector<int>::size_type size = nums.size();

    while (dest < size) {
        if ((dest % 2) == 0) {
            // this is an positve entry
            if (nums[dest] < 0) {
                src = dest + 1;
                while (src < size && nums[src] < 0) {
                    src++;
                } // while
                if (src < size) {
                    int temp = nums[src];
                    nums[src] = nums[dest];
                    nums[dest] = temp;
                } // if
            } // if
        } else {
            // this is an odd entry
            if (nums[dest] > 0) {
                src = dest + 1;
                while (src < size && nums[src] > 0) {
                    src++;
                } // while
                if (src < size) {
                    int temp = nums[src];
                    nums[src] = nums[dest];
                    nums[dest] = temp;
                } // if
            } // if
        } // else
        dest++; // increment the destination index
    } // while
}
