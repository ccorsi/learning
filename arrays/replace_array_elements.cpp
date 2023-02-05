/**
 * @file replace_array_elements.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This is a solution to the problem https://www.techiedelight.com/?problem=ReplaceArrayElements
 * @version 0.1
 * @date 2023-02-04
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include "replace_array_elements.h"

/*

Given an integer array, in-place replace each element with the product of every other element without using the division operator.

Input : [1, 2, 3, 4, 5]
Output: [120, 60, 40, 30, 24]

Input : [5, 3, 4, 2, 6, 8]
Output: [1152, 1920, 1440, 2880, 960, 720]

*/
void valhalla::arrays::replace_array_elements::Solution::rearrange(std::vector<int>& nums) {
    if (nums.size() < 2) {
        if (nums.size() == 1) {
            nums[0] = 1;
        }
        // there is nothing to do so just return
        return;
    }

    // we need to be able to iterate through the array without division....
    int tot = 1;

    for (size_t idx = 0; idx < nums.size() ; idx++) {
        int value = tot;
        for (size_t i = idx + 1 ; i < nums.size() ; i++) {
            value *= nums[i];
        } // for
        tot *= nums[idx];
        nums[idx] = value;
    } // for
}
