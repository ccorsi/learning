/**
 * @file rearrange_array_four.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This is a solution to the problem https://www.techiedelight.com/?problem=RearrangeArrayIV
 * @version 0.1
 * @date 2023-02-10
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include <iostream>

#include "rearrange_array_four.h"

/*

Given an array of positive and negative integers, in-place segregate them in linear time and constant space. The output should contain all negative numbers, followed by all positive numbers.

Input : [9, -3, 5, -2, -8, -6, 1, 3]
Output: [-3, -2, -8, -6, 9, 5, 1, 3] or [-3, -2, -8, -6, 9, 5, 1, 3] or any other valid combination.

Input : [-4, -2, -7, -9]
Output: [-4, -2, -7, -9] or any other valid combination.

Input : [2, 4, 3, 1, 5]
Output: [2, 4, 3, 1, 5] or any other valid combination.

*/

void valhalla::arrays::rearrange_array_four::Solution::rearrange(std::vector<int> & nums) {
    if (nums.empty()) return;

    size_t left = 0, right = nums.size() - 1;
    const size_t size = nums.size();

    // find the first positive entry
    while (left < size && nums[left] < 0) left++;

    // find the first negative entry starting from the end
    while (right < size && nums[right] > 0) right--;

    while (left < right && right < size) {
        // swap the entries
        int temp = nums[left];
        nums[left] = nums[right];
        nums[right] = temp;

        // find the next positive entry
        while (left < size && nums[left] < 0) left++;

        // find the next negative entry
        while (right < size && nums[right] > 0) right--;
    } // while
}
