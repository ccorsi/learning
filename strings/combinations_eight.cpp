/**
 * @file combinations_eight.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains a solution to the problem https://www.techiedelight.com/?problem=CombinationsVIII
 * @version 0.1
 * @date 2023-03-03
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include "combinations_eight.h"

/*

Given a string, return all combinations of non-overlapping substrings of it.

Input : "ABC"
Output: {["A", "B", "C"], ["A", "BC"], ["AB", "C"], ["ABC"]}

Input : "ABCD"
Output: {["A", "B", "C", "D"], ["A", "B", "CD"], ["A", "BC", "D"], ["A", "BCD"], ["AB", "C", "D"],
    ["AB", "CD"], ["ABC", "D"], ["ABCD"]}

*/

std::set<std::vector<std::string>> valhalla::strings::combinations_eight::Solution::findCombinations(std::string s) {
    std::set<std::vector<std::string>> combinations;

    const int size = s.length();

    for (int stop = 0 ; stop < size ; stop++) {
        std::string current = s.substr(0, stop + 1);
        std::vector<std::string> combination = { current };
        findCombination(combinations, combination, stop + 1, s);
    } // for

    return combinations;
}

void valhalla::strings::combinations_eight::Solution::findCombination(std::set<std::vector<std::string>> & combinations,
    std::vector<std::string> & combination, int start, std::string const & s) {

    if (start == s.length()) {
        combinations.insert(combination);
        return;
    } // if

    const int size = s.length();

    for (int from = start ; from < size ; from++) {
        std::vector<std::string> next = combination;
        next.push_back(s.substr(start, from + 1 - start)); // add the next substring
        findCombination(combinations, next, from + 1, s);
    } // for
}
