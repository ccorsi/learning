/**
 * @file odd_occurring_element_two.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This is a solution to the problem https://www.techiedelight.com/?problem=OddOccurringElementII
 * @version 0.1
 * @date 2025-04-09
 *
 * @copyright Copyright (c) 2025 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include "odd_occurring_element_two.h"

#include <set>

namespace valhalla {

namespace bit_manipulation {

namespace odd_occurring_element_two {

/*

Given an integer array, duplicates appear in it an even number of times except for two elements,
which appear an odd number of times. Find both odd appearing elements without using any extra memory.

Input: [4, 3, 6, 2, 4, 2, 3, 4, 3, 3]
Output: (4, 6)
Explanation: The odd occurring elements are 4 and 6 as

6 appears once.
2 appears twice.
4 appears thrice.
3 appears 4 times.

Note: The solution can return a pair of odd appearing elements in any order. Assume valid input.

*/

std::pair<int,int> Solution::findOddOccurringElements(std::vector<int> const & nums) {
    std::pair<int,int> odd(-1,-1);
    std::set<int> odds;

    for (int num : nums) {
        if (odds.insert(num).second == false)
            odds.erase(num);
    }

    std::set<int>::iterator itr = odds.begin();

    odd.first = *itr++;
    odd.second = *itr;

    return odd;
} // findOddOccurringElements

} // namespace odd_occurring_element_two

} // namespace bit_manipulation

} // namespace valhalla
