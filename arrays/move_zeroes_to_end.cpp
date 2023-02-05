/**
 * @file move_zeroes_to_end.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This is a solution to the problem https://www.techiedelight.com/?problem=MoveZeroesToEnd
 * @version 0.1
 * @date 2023-02-04
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include "move_zeroes_to_end.h"

/*

Given an integer array, in-place move all zeros present in it to the end. The solution should maintain the relative order of items in the array and should not use constant space.

Input : [6, 0, 8, 2, 3, 0, 4, 0, 1]
Output: [6, 8, 2, 3, 4, 1, 0, 0, 0]

*/
void valhalla::arrays::move_zeroes_to_end::Solution::rearrange(std::vector<int>& nums) {
    size_t src = 0, dest = 0;

    while (src < nums.size()) {
        if (nums[src] == 0) {
            // skip zero entries
            src++;
        } else if (src == dest) {
            // increment counters since they are pointing to the same index
            src++; dest++;
        } else {
            // move source entry to destination entry and increment counters
            nums[dest++] = nums[src++];
        }
    }

    while (dest < nums.size()) nums[dest++] = 0;

}
