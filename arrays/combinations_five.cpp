/**
 * @file combinations_five.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains a solution to the problem https://www.techiedelight.com/?problem=CombinationsV
 * @version 0.1
 * @date 2023-03-03
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include "combinations_five.h"

/*

Given a positive integer `n`, find all combinations of numbers between 1 and `n` having sum `n`.

Input : n = 4
Output: {[4], [1, 3], [2, 2], [1, 1, 2], [1, 1, 1, 1]}

Input : n = 5
Output: {[5], [1, 4], [2, 3], [1, 1, 3], [1, 2, 2], [1, 1, 1, 2], [1, 1, 1, 1, 1]}

The solution should return a set containing all the distinct combinations in increasing order.

*/

std::set<std::vector<int>> valhalla::arrays::combinations_five::Solution::findCombinations(int n) {
    std::set<std::vector<int>> combinations;

    std::set<std::map<int,int>> visited;

    for (int num = 1 ; num <= n ; num++) {
        std::vector<int> combination = { num };

        if (num != n) {
            std::map<int,int> visited_sofar;

            visited_sofar[num]++;

            findCombination(combinations, combination, visited, visited_sofar, num, n);

            continue;
        } // if

        combinations.insert(combination);
    } // for

    return combinations;
}

void valhalla::arrays::combinations_five::Solution::findCombination(std::set<std::vector<int>> & combinations, std::vector<int> const & combination,
    std::set<std::map<int,int>> & visited, std::map<int,int> const & visited_sofar, const int sum, const int n) {

    // add the entry to the visited
    visited.insert(visited_sofar);

    for (int num = 1 ; num + sum <= n && num <= n ; num++) {
        std::vector<int> next = combination;
        std::map<int,int> sofar = visited_sofar;

        next.push_back(num);
        sofar[num]++;

        if (visited.insert(sofar).second) {
            if (num + sum == n) {
                combinations.insert(next);
                continue;
            } // if
            findCombination(combinations, next, visited, sofar, num + sum, n);
        } // if
    } // for
}
