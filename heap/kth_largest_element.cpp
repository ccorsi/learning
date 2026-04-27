/**
 * @file kth_largest_element.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This is an implementation of the problem https://www.techiedelight.com/?problem=KthLargestElement
 * @version 0.1
 * @date 2026-04-23
 * 
 * @copyright Copyright (c) 2026 Claudio Corsi
 * 
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */


#include "kth_largest_element.h"

namespace valhalla {

namespace heap {

namespace kth_largest_element {

/*

Given an integer array, find k'th largest element in the array where k is a positive integer less than or equal to the length of array.

Input : [7, 4, 6, 3, 9, 1], k = 2
Output: 7
Explanation: The 2nd largest array element is 7

Input : [1, 5, 2, 2, 2, 5, 5, 4], k = 4
Output: 4
Explanation: The 4th largest array element is 4

*/
int Solution::findKthLargest(std::vector<int> const & nums, int k) {
    std::vector<int>::size_type iidx = 0;
    int ith_largest = nums[iidx];

    // find the largest initial element
    for (auto i = 1 ;  i < nums.size() ; i++) {
        if (nums[i] > ith_largest) {
            ith_largest = nums[i];
            iidx = i;
        } // if (nums[i] > ith_largest)
    } // for (auto i = 1 ;  i < nums.size() ; i++)

    while (--k > 0) {
        const int largest = ith_largest;
        const std::vector<int>::size_type lidx = iidx;

        for (auto i = 0 ; i < nums.size() ; i++) {
            // skip all values that are larger than what I already have
            if (nums[i] > largest) {
                continue;
            } // if (nums[i] > ith_largest)

            // skip all duplicate elements that were found before the similar value
            if (nums[i] == largest && i <= lidx) {
                continue;
            } // if (nums[i] == largest && i <= lidx)

            // determine if this is a duplicate value
            if (nums[i] == largest) {
                ith_largest = largest;
                iidx = i;
                break;
            } // if (nums[i] == largest)

            // determine if this is first entry that we are comparing with
            if (ith_largest == largest) {
                ith_largest = nums[i];
                iidx = i;
                continue;
            } // if (ith_largest == largest)

            // determine if the value is larger than the one we've assigned
            if (nums[i] > ith_largest) {
                ith_largest = nums[i];
                iidx = i;
                continue;
            } // if (nums[i] > ith_largest)
        } // for (auto i = 0 ; i < nums.size() ; i++)
    } // while (--k > 0)

    return ith_largest;
} // findKthLargest

} // namespace kth_largest_element

} // namespace heap

} // namespace valhalla
