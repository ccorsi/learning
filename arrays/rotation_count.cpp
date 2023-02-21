/**
 * @file rotation_count.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This is the solution to the problem https://www.techiedelight.com/?problem=RotationCount
 * @version 0.1
 * @date 2023-02-20
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include "rotation_count.h"

/*

Given a circularly sorted array of distinct integers, find the total number of times the array is rotated. You may assume that the rotation is in anti-clockwise direction.

Input: [8, 9, 10, 2, 5, 6]
Output: 3

Input: [2, 5, 6, 8, 9, 10]
Output: 0

*/

int valhalla::arrays::rotation_count::Solution::findRotationCount(std::vector<int> const & nums) {
    if (nums.size() < 2|| nums.front() < nums.back()) return 0;

    for (size_t pos = 1 ; pos < nums.size() ; pos++) {
        if (nums[pos] < nums[pos - 1]) return pos;
    } // for

    return -1;
}
