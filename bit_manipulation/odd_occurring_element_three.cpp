/**
 * @file odd_occurring_element_three.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains a solution to the problem https://www.techiedelight.com/?problem=OddOccurringElementIII
 * @version 0.1
 * @date 2025-04-11
 *
 * @copyright Copyright (c) 2025 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include "odd_occurring_element_three.h"

namespace valhalla {

namespace bit_manipulation {

namespace odd_occurring_element_three {

/*

Given an array having elements between 0 and 31, find elements that occur an odd number of times using constant space.

Input : [5, 8, 2, 5, 8, 2, 8, 5, 1, 8, 2]
Output: {5, 2, 1}

Explanation:

1 occurs once.
2 and 5 occurs thrice.
8 occurs four times.

Assume valid input.

*/

std::unordered_set<int> Solution::findOddOccurringElements(std::vector<int> const & nums) {
    const int size = sizeof(int) * 8;
    int masks[size];
    std::vector<int> odds(size, 0);

    for (int mask = 0 ; mask < size ; mask++) {
        masks[mask] = 1 << mask;
    }

    for (int num : nums)
        odds[num] ^= masks[num];

    std::unordered_set<int> results;

    for (int idx = 0 ; idx < size ; idx++)
        if (odds[idx])
            results.insert(idx);

    return results;
} // findOddOccurringElements

} // namespace odd_occurring_element_three

} // namespace bit_manipulation

} // namespace valhalla
