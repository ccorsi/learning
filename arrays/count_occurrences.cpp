/**
 * @file count_occurrences.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This is a solution to the problem https://www.techiedelight.com/?problem=CountOccurrences
 * @version 0.1
 * @date 2023-02-21
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include "count_occurrences.h"

/*

Given a sorted integer array containing duplicates, return the count of occurrences of a given number.

Input: nums[] = [2, 5, 5, 5, 6, 6, 8, 9, 9, 9], target = 5
Output: 3
Explanation: Target 5 occurs 3 times

Input: nums[] = [2, 5, 5, 5, 6, 6, 8, 9, 9, 9], target = 6
Output: 2
Explanation: Target 6 occurs 2 times

Input: nums[] = [5, 4, 3, 2, 1], target = 6
Output: 0
Explanation: Target 6 occurs 0 times

*/

int valhalla::arrays::count_occurrences::Solution::countOccurrences(std::vector<int> const & nums, int target) {
    size_t pos = 0;

    while (pos < nums.size() && nums[pos] != target) pos++;

    if (pos < nums.size() && nums[pos] == target) {
        int cnt = 0;
        while (pos < nums.size() && nums[pos] == target) {
            cnt++; pos++;
        } // while
        return cnt;
    } // if

    return 0;
}
