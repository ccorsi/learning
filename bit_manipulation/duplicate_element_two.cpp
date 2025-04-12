/**
 * @file duplicate_element_two.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains a solution to the problem https://www.techiedelight.com/?problem=DuplicateElementII
 * @version 0.1
 * @date 2025-04-12
 *
 * @copyright Copyright (c) 2025 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include "duplicate_element_two.h"

#include <set>

namespace valhalla {

namespace bit_manipulation {

namespace duplicate_element_two {

/*

Given an integer array of size `n+2` containing elements between 1 and `n` with two
element repeating, find both duplicate elements without using any extra memory in linear time.

Input: [4, 3, 6, 5, 2, 4, 1, 1]
Output: (1, 4)

Input: [2, 1, 1, 2]
Output: (1, 2)

Note: The solution can return a pair of duplicate elements in any order. Assume valid input.

*/

std::pair<int,int> Solution::findDuplicateElements(std::vector<int> const & nums) {
    std::pair<int,int> duplicate(-1,-1);
    std::set<int> elements;
    bool first = true;

    for (int num : nums) {
        if (elements.insert(num).second == false) {
            elements.erase(num);
            if (first) {
                duplicate.first = num;
                first = false;
            } else {
                duplicate.second = num;
                break;
            }
        }
    }

    return duplicate;
} // findDuplicateElements

} // namespace duplicate_element_two

} // namespace bit_manipulation

} // namespace valhalla
