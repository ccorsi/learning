/**
 * @file missing_number_three.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains a solution to the problem https://www.techiedelight.com/?problem=MissingNumberIII
 * @version 0.1
 * @date 2025-04-08
 *
 * @copyright Copyright (c) 2025 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include "missing_number_three.h"

namespace valhalla {

namespace bit_manipulation {

namespace missing_number_three {

/*

Given a sequence of n numbers such that the difference between the consecutive terms is
constant, find the missing term in logarithmic time.

Input: [5, 7, 9, 11, 15]
Output: 13

Input: [1, 4, 7, 13, 16]
Output: 10

Input: [4, 8]
Output: 6

Assume valid input and n >= 2. Also, assume that the first and last elements are always
part of the input sequence and the missing number lies between index 1 to n-1.

*/

int Solution::findMissingNumber(std::vector<int> const & nums) {
    // determine gap between each entry of the sequence
    const int gap = ( nums.back() - nums.front() ) / static_cast<int>(nums.size());
    // store beginning of sequence
    const int start = nums.front();

    int missing = start + gap;

    if (nums.size() > 2) {
        int left =  0, right = static_cast<int>(nums.size() - 1), mid = ( left + right ) / 2;

        while (left < right) {
            if (nums[mid] == ( mid * gap + start )) {
                left = mid + 1;
                missing = nums[mid] + gap;
            } else {
                right = mid - 1;
                missing = nums[mid] - gap;
            } // if (nums[mid] == ( mid * gap + start ))
            mid = ( left + right ) / 2;
        } // while (left < right)

    } // if (nums.size() > 2)

    return missing;
} // findMissingNumber

} // namespace missing_number_three

} // namespace bit_manipulation

} // namespace valhalla
