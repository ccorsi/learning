/**
 * @file combinations_three.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains a solution to the problem https://www.techiedelight.com/?problem=CombinationsIII
 * @version 0.1
 * @date 2023-03-03
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include "combinations_three.h"

/*

Given a positive number `n`, find all combinations of `2×n` elements such that every element from 1 to `n`
appears exactly twice and the distance between its two appearances is exactly equal to the value of the
element.

Input : n = 3
Output: {[3, 1, 2, 1, 3, 2], [2, 3, 1, 2, 1, 3]}

Input : n = 4
Output: {[4, 1, 3, 1, 2, 4, 3, 2], [2, 3, 4, 2, 1, 3, 1, 4]}

Input : n = 5
Output: {}

*/

std::set<std::vector<int>> valhalla::arrays::combinations_three::Solution::findCombinations(int n) {
    std::set<std::vector<int>> combinations;

    if (n > 2) {
        const int size = 2 * n;

        for (int value = 1 ; value <= n ; value++) {
            const int end = (value > 1) ? value - 1 : n;
            const int span = value + 1;
 
            for( int idx = 0 ; idx + span < size ; idx++) {
                std::vector<int> combination(size,0);
                combination[idx] = combination[idx+span] = value;
                findCombination(combinations, combination, value, end, n, size);
            } // for
        } // for
    } // if

    return combinations;
}

void valhalla::arrays::combinations_three::Solution::findCombination(std::set<std::vector<int>> & combinations, std::vector<int> & combination, int value, const int end, const int n, const int size) {
    value = (value < n) ? value + 1 : 1; // set the next value to check

    for (int idx = 0 ; idx + value + 1 < size ; idx++) {
        const int span = value + 1;
 
        if (combination[idx] == 0 && combination[idx+span] == 0) {
            std::vector<int> next = combination;
            next[idx] = next[idx+span] = value;
 
            if (value == end) {
                combinations.insert(next);
                continue;
            } // if
 
            findCombination(combinations, next, value, end, n, size);
        } // if
    } // for
}
