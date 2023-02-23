/**
 * @file largest_subarray.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief 
 * @version 0.1
 * @date 2023-01-01
 * 
 * @copyright Copyright (c) 2023 Claudio Corsi
 * 
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include "largest_subarray.h"

/*

Given a binary array containing 0’s and 1’s, find the largest contiguous subarray with equal numbers of 0’s and 1’s.

Input : [0, 0, 1, 0, 1, 0, 0]
Output: [0, 1, 0, 1] or [1, 0, 1, 0]

Input : [0, 0, 0, 0]
Output: []

Note: Since an input can contain several largest subarrays with equal numbers of 0’s and 1’s, the code should return any one of them.

*/

#include <map>
#include <iostream>

std::vector<int> valhalla::arrays::largest_subarray::Solution::find(std::vector<int> const &values) {
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
        results[sum].push_back(idx);

        int value = values[idx];

        sum += value == 0 ? -1 : value;

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
    } // for

    if (longest > 0) {
        // we've found the longest subarray for target in the passed array
        for(std::vector<int>::size_type cnt = 0 ; cnt < longest ; cnt++) {
            found.push_back(values[start + cnt]);
        }
    } // if

    return found;

    /*
    std::cout << "Processing: [";
    for (int value : values) 
        std::cout << " " << value;
    std::cout << (values.empty() ? "]" : " ]") << std::endl;

    std::vector<int> largestSubarray;

    std::map<int, std::vector<int>> ranges;

    int sum = 0;
    std::vector<int>::size_type longest =  0;
    int key = 0;

    for(std::vector<int>::size_type idx = 0 ; idx < values.size() ; idx++) {
        // determine the increment
        int value = ( values[idx] == 0 ) ? -1 : 1;

        // sum up the current total
        sum += value;

        // determine if a subarray was found
        std::vector<int> found = ranges[sum];

        // add the current index to the map
        ranges[sum].push_back(idx);

        if (found.empty() == false) {
            std::cout << "Subarray " << found[0] << " to " <<  idx << std::endl;
            // we found a subarray compare its size against the largest one we found already
            if (idx - found[0] + 1 > longest) {
                key = sum;
                longest = idx - found[0] + 1;
            }
        }
    }

    if (longest > 0) {
        std::vector<int> range = ranges[key];
        std::vector<int>::size_type end = range.back();
        for(std::vector<int>::size_type idx = range[0] ; idx <= end ; idx++) {
            largestSubarray.push_back(values[idx]);
        }
    }

    return largestSubarray;
    */
}