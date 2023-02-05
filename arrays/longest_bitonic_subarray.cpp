/**
 * @file longest_bitonic_subarray.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This is a solution to the problem https://www.techiedelight.com/?problem=LongestBitonicSubarray
 * @version 0.1
 * @date 2023-02-04
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include <iostream>

#include "longest_bitonic_subarray.h"

/*

The Longest Bitonic Subarray (LBS) problem is to find a contiguous subarray of a given sequence in which the subarray’s
elements are first sorted in increasing order, then in decreasing order, and the subarray is as long as possible.

Input : [3, 5, 8, 4, 5, 9, 10, 8, 5, 3, 4]
Output: [4, 5, 9, 10, 8, 5, 3]

In case the multiple bitonic subarrays of maximum length exists, the solution can return any one of them.

Input : [-5, -1, 0, 2, 1, 6, 5, 4, 2]
Output: [-5, -1, 0, 2, 1] or [1, 6, 5, 4, 2]

*/

std::vector<int> valhalla::arrays::longest_bitonic_subarray::Solution::findBitonicSubarray(std::vector<int> const & nums) {
    std::vector<int> longest;

    if (nums.size() < 2) {
        longest.insert(longest.begin(), nums.begin(), nums.end());
        return longest;
    }

    // std::cout << "Input: [";
    // for (int n : nums)
    //     std::cout << " " << n;
    // std::cout << " ]" << std::endl;

    const int START = 0, RISING = 1, DROPPING = 2;
    size_t start = 0, idx = 0;
    int state = START;
    int current = nums[start];
    size_t max_start, max_end;
    max_start = max_end = start;

    while (++idx < nums.size()) {
        int value = nums[idx];
        switch (state) {
            case START:
                if (value > current) {
                    // entries are rising as per condition move to next state
                    state = RISING;
                    // std::cout << "Start: " << start << " = " << nums[start] << std::endl;
                    if (max_end - max_start < idx - start) {
                        max_start = start;
                        max_end = idx;
                    } // if
                } else if (value < current) {
                    // entries are dropping as per condition move to next state
                    state = DROPPING;
                    if (max_end - max_start < idx - start) {
                        max_start = start;
                        max_end = idx;
                    } // if
                } else {
                    // reset the start position since entry is less than or equal
                    start = idx;
                    // std::cout << "Not rising start: " << start << std::endl;
                } // else
                break;
            case RISING:
                if (value > current) {
                    // the values are still rising so continue to look at next entry
                    if (max_end - max_start < idx - start) {
                        max_start = start;
                        max_end = idx;
                    } // if
                } else if (value < current) {
                    // the values just started to drop so update state
                    state = DROPPING;
                    // std::cout << "Dropping: " << idx << " = " << nums[idx - 1] << std::endl;
                    if (max_end - max_start < idx - start) {
                        max_start = start;
                        max_end = idx;
                    } // if
                } else {
                    // we are done here so let us compare the size of the current longest with this one
                    if (max_end - max_start < idx - start - 1) {
                        // we have a new longest bitonic subarray
                        max_start = start;
                        max_end = idx;
                    } // if
                    // invalid condition therefore start over again
                    state = START;
                    start = idx - 1;
                    // std::cout << "Not dropping start: " << start << std::endl;
                } // else
                break;
            case DROPPING:
                if (value < current) {
                    // the values are still dropping so continue to look at next entry
                    if (max_end - max_start < idx - start) {
                        max_start = start;
                        max_end = idx;
                    } // if
                } else {
                    // std::cout << "Bitonic: [";
                    // for (size_t i = start ; i < idx ; i++)
                    //     std::cout << " " << nums[i];
                    // std::cout << " ]" << std::endl;
                    // we are done here so let us compare the size of the current longest with this one
                    if (max_end - max_start < idx - start) {
                        max_start = start;
                        max_end = idx;
                    } // if
                    state = START;
                    start = idx - 1;
                } // else
                break;
        } // switch
        // update current value
        current = value;
    } // while

    if (max_end - max_start < idx - start) {
        max_start = start;
        max_end = idx;
    } // if

    longest.clear();
    longest.insert(longest.begin(), nums.begin() + max_start, nums.begin() + max_end);

    // std::cout << "Longest Bitonic: [";
    // for (int v : longest)
    //     std::cout << " " << v;
    // std::cout << " ]" << std::endl;

    return longest;
}
