/**
 * @file smallest_window_to_sort_array.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains a solution to the problem https://www.techiedelight.com/?problem=SmallestWindowToSortArray
 * @version 0.1
 * @date 2023-03-15
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include "smallest_window_to_sort_array.h"

/*

Given an integer array, find the smallest window sorting which will make the entire array
sorted in increasing order. The solution should return a pair consisting of the starting
and ending index of the smallest window.

Input : [1, 2, 3, 7, 5, 6, 4, 8]
Output: (3, 6)
Explanation: The array can be sorted from index 3 to 6 to get sorted version.

Input : [1, 3, 2, 7, 5, 6, 4, 8]
Output: (1, 6)
Explanation: The array can be sorted from index 1 to 6 to get sorted version.

If the array is already sorted, the solution should return pair (0, 0).

Input : [1, 2, 3, 4, 5]
Output: (0, 0)
Explanation: The array is already sorted.

*/

std::pair<int,int> valhalla::arrays::smallest_window_to_sort_array::Solution::findSmallestWindow(std::vector<int> const & nums) {
    std::pair<int,int> result(0,0);
    int start = 0;
    const int size = nums.size();
    const int last = size - 1;

    while (start < last && nums[start] < nums[start+1]) {
        start++;
    } // while

    if (start < last) {
        int end = start, idx = start;
        while (idx < last) {
            if (nums[idx] > nums[idx+1]) {
                end = idx + 1;
            } // if
            idx++;
        } // while
        result.first = start;
        result.second = (end < size) ? end : last;
    } // if

    return result;
}
