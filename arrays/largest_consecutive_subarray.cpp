/**
 * @file largest_consecutive_subarray.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This is the solution to the problem https://www.techiedelight.com/?problem=LargestConsecutiveSubarray
 * @version 0.1
 * @date 2023-01-25
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include <iostream>
#include <set>
#include <algorithm>

#include "largest_consecutive_subarray.h"

/*

Given an integer array, find the largest contiguous subarray formed by consecutive integers. The subarray should contain all distinct values.

Input : [2, 0, 2, 1, 4, 3, 1, 0]
Output: [0, 2, 1, 4, 3]

In case the multiple consecutive subarrays of maximum length exists, the solution can return any one of them.

Input : [-5, -1, 0, 2, 1, 6, 5, 8, 7]
Output: [-1, 0, 2, 1] or [6, 5, 8, 7]

*/
std::vector<int> valhalla::arrays::largest_consecutive_subarray::Solution::findLargestSubarray(std::vector<int> const &nums) {
    std::vector<int> largest;

    if (nums.empty()) {
        // there is nothing to do so just return
        return largest;
    } // if

    const size_t size = nums.size();
    int min, max;
    size_t idx = 0, start = 0;
    std::set<int> values;

    min = max = nums[idx];
    values.insert(nums[idx]);
    largest.push_back(nums[idx]);

    idx++; // increment the current index

    while (idx + largest.size() - values.size() < size) {
        const int value = nums[idx];
        // add the current entry to the set
        std::pair<std::set<int>::iterator,bool> result = values.insert(value);
        if (result.second == false) {
            // std::cout << "Value: " << value << " already part of values set" << std::endl;
            // std::cout << "Values Before: [";
            // for (int num : values)
            //     std::cout << " " << num;
            // std::cout << " ]" << std::endl;

            // The entry was already added so we need to determine where that entry was
            // found and start from that point.
            while (nums[start] != value) {
                values.erase(nums[start++]);
            } // while

            // std::cout << "Values After: [";
            // for (int num : values)
            //     std::cout << " " << num;
            // std::cout << " ]" << std::endl;

            // increment to next entry and reset the min and max values.
            start++;
            // determine the min and max values once again
            min = max = nums[start];
            for(size_t next = start + 1 ;  next < idx ; next++) {
                if (min > nums[next]) {
                    min = nums[next];
                } else if (max < nums[next]) {
                    max = nums[next];
                } // else if
            } // for
        } else {
            // compare the value to the min and max
            if (min > value) {
                min = value;
            } else if (max < value) {
                max = value;
            } // else if

            // determine if the current number of entries generate a sequence
            if (max - min == idx - start) {
                // std::cout << "Found Consecutive Sequence: [";
                // for (size_t i = start ; i <= idx ; i++)
                //     std::cout << " " << nums[i];
                // std::cout << " ]" << std::endl;
                // we have found a consecutive sequence
                if (largest.size() < values.size()) {
                    largest.clear();
                    largest.insert(largest.begin(), nums.begin() + start, nums.begin() + (idx + 1));
                    // std::cout << "Updated Largest: [";
                    // for (int num : largest)
                    //     std::cout << " " << num;
                    // std::cout << " ]" << std::endl;
                } // if
            } else if (start + max - min > size) {
                // std::cout << "Clearing values" << std::endl;
                // we don't have enough entries to find a consecutive sequence
                // we need to purge the entries to be able to find a consecutive sequence
                // remove all entries
                values.clear();
                // move up the start position
                start++;
                // set the index to the start position
                idx = start;
                // add the value from the start position to the values
                values.insert(nums[start]);
                // set the min and max values to the start entry
                min = max = nums[start];
            } // else if

        } // else
        idx++; // increment the index
        // std::cout << "Values size: " << values.size() << ", Largest size: " << largest.size() << std::endl;
    } // while

    // std::cout << "idx: " << idx << ", size: " << size << std::endl;

    // std::cout << "Largest: [";
    // for (int num : largest)
    //     std::cout << " " << num;
    // std::cout << " ]" << std::endl;

    return largest;
}
