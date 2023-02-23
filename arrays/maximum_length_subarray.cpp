/**
 * @file maximum_length_subarray.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief 
 * @version 0.1
 * @date 2022-12-29
 * 
 * @copyright Copyright (c) 2022 Claudio Corsi
 * 
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */
#include <iostream>
#include <map>

#include "maximum_length_subarray.h"

/*

Given an integer array, find the maximum length contiguous subarray having a given sum.

Input : nums[] = [5, 6, -5, 5, 3, 5, 3, -2, 0], target = 8
Output: [-5, 5, 3, 5]
Explanation: The subarrays with sum 8 are [[-5, 5, 3, 5], [3, 5], [5, 3]]. The longest subarray is [-5, 5, 3, 5] having length 4.

Note: Since an input can contain several maximum length subarrays with given sum, the solution should return any one of the maximum length subarray.

*/

std::vector<int> valhalla::arrays::maximum_length_subarray::Solution::find_maximum_subarray(std::vector<int> const &values, int target) {
    std::vector<int> found;

    if (values.empty()) {
        // nothing to do
        return found;
    }

    // initialize sum value
    int sum = 0;

    // setup a targets tracker fields.
    std::vector<int> targets;
    std::vector<int>::size_type prior = 0;

    // setup a map that will be used to track sums to compare with for target
    std::map<int, std::vector<size_t>> results;

    // setup values used to determine the longest subarray
    std::vector<int>::size_type longest = 0;
    std::vector<int>::size_type start = 0;

    for(std::vector<int>::size_type idx = 0 ; idx < values.size() ; idx++) {
        // insert the current index for the this sum
        results[sum + target].push_back(idx);

        // std::vector<size_t> ranges = results[sum];
        
        int value = values[idx];

        sum += value;

        if (value == target) {
            if (prior + 1 != idx) {
                targets.clear();
            }
            // add the target to the targets
            targets.push_back(target);
            // compare to current longest subarray
            if (longest < targets.size()) {
                // update the longest subarray
                longest = targets.size();
                // reset the starting index of the subarray
                start = idx + 1 - longest;
            }
            // update the prior index
            prior = idx;
            // proceed to the next value in the array
            continue;
        } else {
            // we need to determine if we have any other arrays that need to be updated

            // get the subarray for the current sum
            std::vector<size_t> subarray = results[sum];

            if ( ! subarray.empty() ) {
                std::vector<int>::size_type length = idx + 1 - subarray[0];
                if (length > longest) {
                    longest = length;
                    start = subarray[0];
                } // if
            } // if
        } // else
    } // for

    if (longest > 0) {
        // we've found the longest subarray for target in the passed array
        for(std::vector<int>::size_type cnt = 0 ; cnt < longest ; cnt++) {
            found.push_back(values[start + cnt]);
        }
    } // if

    return found;
}
