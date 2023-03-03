/**
 * @file combinations.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains a solution to the problem https://www.techiedelight.com/?problem=Combinations
 * @version 0.1
 * @date 2023-03-03
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include "combinations.h"

/*

Given an integer array, find all distinct combinations of a given length `k`. The solution should
return a set containing all the distinct combinations, while preserving the relative order of
elements as they appear in the array.

Input : [2, 3, 4], k = 2
Output: {[2, 3], [2, 4], [3, 4]}

Input : [1, 2, 1], k = 2
Output: {[1, 2], [1, 1], [2, 1]}

Input : [1, 1, 1], k = 2
Output: {[1, 1]}

Input : [1, 2, 3], k = 4
Output: {}

Input : [1, 2], k = 0
Output: {[]}

*/

std::set<std::vector<int>> valhalla::arrays::combinations::Solution::findCombinations(std::vector<int> const & nums, int k) {
    std::set<std::vector<int>> combinations;

    if (k == 0) {
        if ( ! nums.empty() ) {
            combinations.insert(std::vector<int>());
        } // if
    } else if (static_cast<std::vector<int>::size_type>(k) <= nums.size()) {
        std::vector<int> combination;
        for (int col = 0 ; static_cast<std::vector<int>::size_type>(col) < nums.size() ; col++)
            findCombination(combinations, combination, col, nums, k);
    } // if

    return combinations;
}

void valhalla::arrays::combinations::Solution::findCombination(std::set<std::vector<int>> & combinations,
 std::vector<int> const & combination, int idx, std::vector<int> const & nums, const int k) {
    std::vector<int> updated = combination;
    updated.push_back(nums[idx]);

    if (updated.size() == k) {
        combinations.insert(updated);
    } else if (updated.size() + nums.size() - static_cast<std::vector<int>::size_type>(idx) >= static_cast<std::vector<int>::size_type>(k) ) {
        for (std::vector<int>::size_type col = idx + 1 ; static_cast<std::vector<int>::size_type>(col) < nums.size() ; col++) {
            findCombination(combinations, updated, col, nums, k);
        } // for
    } // else if
}
