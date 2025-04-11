/**
 * @file missing_number.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains a solution to the problem https://www.techiedelight.com/?problem=MissingNumber
 * @version 0.1
 * @date 2025-04-04
 *
 * @copyright Copyright (c) 2025 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include "missing_number.h"

#include <set>

namespace valhalla {

namespace bit_manipulation {

namespace missing_number {

int solution_one(const std::vector<int> &nums) {
    const int length = static_cast<int>(nums.size()) + 1;
    int missing = 0;

    if (length % 2 == 0) {
        missing = (length / 2) * (length + 1);
    } else {
        missing = ((length + 1) / 2) * length;
    } // if (length % 2 == 0)

    for (int value : nums) {
        missing -= value;
    } // for (int value : nums)

    return missing;
} // solution_one

int solution_two(std::vector<int> const & nums) {
    std::set<int> missing;
    for (int value = static_cast<int>(nums.size()) + 1 ; value > 0 ; value--) {
        missing.insert(value);
    } // for (int value = nums.size() + 1 ; value > 0 ; value--)

    for (int value : nums) {
        missing.erase(value);
    } // for (int value : nums)

    return *(missing.begin());
} // solution_two

/*

Given an array of `n-1` distinct integers in the range of 1 to `n`, find the missing number in it in linear time.

Input: [1, 2, 3, 4, 5, 7, 8, 9, 10]
Output: 6
Explanation: All elements are in the range 1 to 10. The missing number is 6.

Input: [1, 2, 3, 4]
Output: 5

Assume valid input.

*/

int Solution::findMissingNumber(std::vector<int> const & nums) {
    return solution_one(nums);
} // findMissingNumber

} // namespace missing_number

} // namespace bit_manipulation

} // namespace valhalla
