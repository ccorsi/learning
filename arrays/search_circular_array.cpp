/**
 * @file search_circular_array.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This is a solution to the problem https://www.techiedelight.com/?problem=SearchCircularArray
 * @version 0.1
 * @date 2023-02-20
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include "search_circular_array.h"

/*

Given a circularly sorted integer array, search a target element in it. If the target exists in the array, the procedure should return the index of it. If the target is not located, the procedure should return -1. You may assume there are no duplicates in the array, and the rotation is in the anti-clockwise direction.

Input: nums[] = [8, 9, 10, 2, 5, 6], target = 10
Output: 2
Explanation: Element found at 3rd (index 2) position.

Input: nums[] = [9, 10, 2, 5, 6, 8], target = 5
Output: 3
Explanation: Element found at 4th (index 3) position.

Input: nums[] = [8, 9, 1, 4, 5], target = 2
Output: -1
Explanation: Target not found

*/

int valhalla::arrays::search_circular_array::Solution::findIndex(std::vector<int> const & nums, int target) {
    size_t pos = 0;

    while (pos < nums.size() && nums[pos] != target) pos++;

    return (pos != nums.size()) ? pos : -1;
}
