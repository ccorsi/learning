/**
 * @file smallest_missing_number.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This is a solution to the problem https://www.techiedelight.com/?problem=SmallestMissingNumber
 * @version 0.1
 * @date 2023-02-21
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include "smallest_missing_number.h"

/*

Given a sorted array of non-negative distinct integers, find the smallest missing non-negative element in it.

Input: [0, 1, 2, 6, 9, 11, 15]
Output: 3

Input: [1, 2, 3, 4, 6, 9, 11, 15]
Output: 0

Input: [0, 1, 2, 3, 4, 5, 6]
Output: 7

*/

int valhalla::arrays::smallest_missing_number::Solution::findSmallestMissingNumber(std::vector<int> const & nums) {
    std::vector<int>::size_type value = 0;

    while (value < nums.size() && nums[value] == value) value++;

    return value;
}
