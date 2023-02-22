/**
 * @file floor_and_ceil.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This is a solution to the problem https://www.techiedelight.com/?problem=FloorAndCeil
 * @version 0.1
 * @date 2023-02-21
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include <iostream>

#include "floor_and_ceil.h"

/*

Given a sorted integer array, find the floor and ceiling of a given number in it. For a given number x, floor(x) is the largest integer in the array less than or equal to x, and ceil(x) is the smallest integer in the array greater than or equal to x.

The solution should return the (floor, ceil) pair. If the floor or ceil doesn't exist, consider it to be -1.

Input: nums[] = [1, 4, 6, 8, 9], x = 2
Output: (1, 4)
Explanation: The floor is 1 and ceil is 4

Input: nums[] = [1, 4, 6, 8, 9], x = 6
Output: (6, 6)
Explanation: The floor is 6 and ceil is 6

Input: nums[] = [-2, 0, 1, 3], x = 4
Output: (3, -1)
Explanation: The floor is 3 and ceil doesn't exist

*/

std::pair<int,int> valhalla::arrays::floor_and_ceil::Solution::findFloorAndCeil(std::vector<int> const & nums, int x) {
    std::pair<int,int> result(-1,-1);
    std::pair<bool,bool> clear(true,true);

    for (int num : nums) {
        if (num <= x && (num > result.first || clear.first)) {
            result.first = num;
            clear.first = false;
        } // if
        if (num >= x && (num < result.second || clear.second)) {
            result.second = num;
            clear.second = false;
        } // if
    } // for

    return result;
}
