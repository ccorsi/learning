/**
 * @file combinations_two.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains a solution to the problem https://www.techiedelight.com/?problem=CombinationsII
 * @version 0.1
 * @date 2023-03-03
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include "combinations_two.h"

/*

Find all combinations of positive integers in increasing order that sum to a given positive number `N`.

Input : N = 3
Output: {[1, 1, 1], [1, 2], [3]}

Input : N = 4
Output: {[1, 1, 1, 1], [1, 1, 2], [1, 3], [2, 2], [4]}

Input : N = 5
Output: {[1, 1, 1, 1, 1], [1, 1, 1, 2], [1, 1, 3], [1, 2, 2], [1, 4], [2, 3], [5]}

*/

std::set<std::vector<int>> valhalla::arrays::combinations_two::Solution::findCombinations(int n) {
    std::set<std::vector<int>> combinations;

    if (n > 0) {
        for (int sum = 1 ; sum < n ; sum++) {
            std::vector<int> combination = { sum };
            findCombination(combinations, combination, sum, sum, n);
        } // for
        combinations.insert(std::vector<int>(1,n));
    } // if

    return combinations;
}

void valhalla::arrays::combinations_two::Solution::findCombination(std::set<std::vector<int>> & combinations, std::vector<int> & combination, int sum, int value, const int n) {
    if (sum + value <= n) {
        for ( ; value < n ; value++) {
            if (sum + value == n) {
                std::vector<int> updated = combination;
                updated.push_back(value);
                combinations.insert(updated);
            } else if (sum + value < n) {
                std::vector<int> updated = combination;
                updated.push_back(value);
                findCombination(combinations, updated, sum + value, value, n);
            } // else if
        } // for
    } // if
}
