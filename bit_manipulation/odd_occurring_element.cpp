/**
 * @file odd_occurring_element.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This is a solution to the problem https://www.techiedelight.com/?problem=OddOccurringElement
 * @version 0.1
 * @date 2025-04-08
 *
 * @copyright Copyright (c) 2025 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include "odd_occurring_element.h"

#include <set>

namespace valhalla {

namespace bit_manipulation {

namespace odd_occurring_element {

/*

Given an integer array, duplicates are present in it in a way that all duplicates
appear an even number of times except one which appears an odd number of times.
Find that odd appearing element in linear time and without using any extra memory.

Input: [4, 3, 6, 2, 6, 4, 2, 3, 4, 3, 3]
Output: 4

Assume valid input.

*/

int Solution::findOddOccurringElement(std::vector<int> const & nums) {
    std::set<int> odd;

    for (int value : nums) {
        if (odd.insert(value).second == false)
            odd.erase(value);
    }

    return *(odd.begin());
} // findOddOccurringElement

} // namespace odd_occurring_element

} // namespace bit_manipulation

} // namespace valhalla
