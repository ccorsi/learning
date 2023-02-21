/**
 * @file first_and_last_occurrence.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This is a solution to the problem https://www.techiedelight.com/?problem=FirstAndLastOccurrence
 * @version 0.1
 * @date 2023-02-20
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include "first_and_last_occurrence.h"

/*

Given a sorted integer array, find the index of a given number's first and last occurrence.

Input: nums[] = [2, 5, 5, 5, 6, 6, 8, 9, 9, 9], target = 5
Output: (1, 3)
Explanation: The first and last occurrence of element 5 is located at index 1 and 3, respectively.

• If the target is not present in the array, the solution should return the pair (-1, -1).

Input: nums[] = [2, 5, 5, 5, 6, 6, 8, 9, 9, 9], target = 4
Output: (-1, -1)

*/

std::pair<int,int> valhalla::arrays::first_and_last_occurrence::Solution::findPair(std::vector<int> const & nums, int target) {
    std::pair<int,int> p(-1,-1);

    size_t pos = 0;

    while (pos < nums.size() && nums[pos] != target && nums[pos] < target) pos++;

    if (pos != nums.size() && nums[pos] == target) {
        p.first = pos;
        while (pos != nums.size() && nums[pos] == target) pos++;
        p.second = pos - 1;
    } // if

    return p;
}
