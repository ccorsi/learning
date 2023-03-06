/**
 * @file combinations_four.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains a solution to the problem https://www.techiedelight.com/?problem=CombinationsIV
 * @version 0.1
 * @date 2023-03-03
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include "combinations_four.h"

/*

Given an integer array, find all distinct combinations of a given length `k`, where the repetition of
elements is allowed.

Input : [1, 2, 3], k = 2
Output: {[1, 1], [1, 2], [1, 3], [2, 2], [2, 3], [3, 3]}

Input : [1, 1, 1], k = 2
Output: {[1, 1]}

Input : [1, 2], k = 0
Output: {[]}

Input : [], k = 1
Output: {}

The solution should consider only distinct combinations. For example, either [1, 1, 2] or [1, 2, 1] or [2, 1, 1]
should be considered for the below input. Same goes for [1, 2, 2] or [2, 1, 2] or [2, 2, 1].

Input : [1, 2, 1], k = 3
Output: {[1, 1, 1], [1, 1, 2], [1, 2, 2], [2, 2, 2]}

*/

std::set<std::vector<int>> valhalla::arrays::combinations_four::Solution::findCombinations(std::vector<int> & nums, int k) {
    std::set<std::vector<int>> combinations;

    if (k == 0) {
        combinations.insert(std::vector<int>());
        return combinations;
    } // if

    if ( ! nums.empty() && k > -1 ) {
        const int size = static_cast<int>(nums.size());
        // These will contain a vectors that contains entries less then k
        std::set<std::map<int,int>> visited;
        for (int from = 0 ; from < size ; from++) {
            int num = nums[from];
            std::vector<int> combination(k,0);
            combination[0] = num;
            std::map<int,int> visited_sofar;
            visited_sofar[num]++;
            if ( visited.insert(visited_sofar).second ) {
                if (1 == k) {
                    combinations.insert(combination);
                    continue;
                } // if
                findCombination(combinations, combination, 1, from, visited, visited_sofar, nums, k);
            } // if
        } // for
    } // if

    return combinations;
}

void valhalla::arrays::combinations_four::Solution::findCombination(std::set<std::vector<int>> & combinations, std::vector<int> const & combination, const int pos,
    const int start, std::set<std::map<int, int>> & visited, std::map<int, int> visited_sofar, std::vector<int> const & nums, const int k) {
    
    const int size = static_cast<int>(nums.size());
    for (int from = start ; from < size ; from++) {
        int num = nums[from];
        std::vector<int> next = combination;
        next[pos] = num;
        std::map<int,int> sofar = visited_sofar;
        sofar[num]++;
        if ( visited.insert(sofar).second ) {
            if (pos + 1 == k) {
                combinations.insert(next);
                continue;
            } // if
            findCombination(combinations, next, pos + 1, from, visited, sofar, nums, k);
        } // if
    }
}
