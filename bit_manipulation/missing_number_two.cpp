/**
 * @file missing_number_two.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This is a solution to the problem https://www.techiedelight.com/?problem=MissingNumberII
 * @version 0.1
 * @date 2025-04-08
 *
 * @copyright Copyright (c) 2025 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include "missing_number_two.h"

namespace valhalla {

namespace bit_manipulation {

namespace missing_number_two {

int solution_one(std::vector<int> const & nums) {
    // Solution One: while the following works and is fast, it does
    //		have an issue with the fact that if n is large enough there is an overflow
    //		value that will make this algorithm fail

    const int length = static_cast<int>(nums.size()) + 1;
    int missing = 0;
    if (length % 2 == 0) {
        missing = (length / 2) * (length + 1);
    } else {
        missing = ((length + 1) / 2) * length;
    }

    for (int value : nums)
        missing -= value;

    return missing;
} // solution_one

/*

Given an integer array of size `n` and containing elements between 1 and `n+1`
with one element missing, find the missing number using constant space.

Input: [3, 2, 4, 6, 1]
Output: 5

Input: [3, 2, 4, 5, 6]
Output: 1

Input: [3, 2, 4, 5, 1]
Output: 6

Assume valid input.

*/

int Solution::findMissingNumber(std::vector<int> const & nums) {
    return solution_one(nums);
} // findMissingNumber

} // namespace missing_number_two

} // namespace bit_manipulation

} // namespace valhalla
