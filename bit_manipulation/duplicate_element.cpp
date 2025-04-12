/**
 * @file duplicate_element.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains a solution to the problem https://www.techiedelight.com/?problem=DuplicateElement
 * @version 0.1
 * @date 2025-04-12
 *
 * @copyright Copyright (c) 2025 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include "duplicate_element.h"

namespace valhalla {

namespace bit_manipulation {

namespace duplicate_element {

/*

Given an integer array of size `n` containing elements between 1 and `n-1`
with one element repeating, find the duplicate number in it using constant space.

Input: [1, 2, 3, 4, 4]
Output: 4

Input: [1, 2, 3, 4, 2]
Output: 2

Input: [1, 1]
Output: 1

Assume valid input.

*/

int solution_one(std::vector<int> const & nums) {
    const int size = static_cast<int>(nums.size());
    int remainder = ( size * ( size + 1 ) ) / 2; // assuming no overflow but that can be implemented using steps

    for (int num : nums) {
        remainder -= num;
    } // for (int num : nums)

    return size - remainder;
}

int solution_two(std::vector<int> const & nums) {
    const int size = static_cast<int>(nums.size());
    int n = 1;
    int duplicate = 0;

    for (int num : nums) {
        duplicate += n++;
        duplicate -= num;
    } // for (int num : nums)

    return size - duplicate;
}

int solution_three(std::vector<int> const & nums) {
    const int size = static_cast<int>(nums.size());
    int n = 1;
    int duplicate = 0;

    for (int num : nums) {
        duplicate += (n++ - num);
    } // for (int num : nums)

    return size - duplicate;
}

int Solution::findDuplicateElement(std::vector<int> const & nums) {
    return solution_three(nums);
} // findDuplicateElement

} // namespace duplicate_element

} // namespace bit_manipulation

} // namespace valhalla
