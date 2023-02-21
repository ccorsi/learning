/**
 * @file smallest_missing_number_two.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This is a solution to the problem https://www.techiedelight.com/?problem=SmallestMissingNumberII
 * @version 0.1
 * @date 2023-02-21
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include <set>

#include "smallest_missing_number_two.h"

/*

Given an unsorted integer array, find the smallest missing positive integer in it.

Input: [1, 4, 2, -1, 6, 5]
Output: 3

Input: [1, 2, 3, 4]
Output: 5

*/

int valhalla::arrays::smallest_missing_number_two::Solution::findSmallestMissingNumber(std::vector<int> const & nums) {
    std::set<int> sorted;

    sorted.insert(nums.begin(), nums.end());

    auto itr = sorted.begin();

    while (itr != sorted.end() && *itr < 1) itr++;

    int value = 1;

    while (itr != sorted.end() && *itr == value) {
        value++;
        itr++;
    } // while

    return value;
}
