/**
 * @file first_k_non_repeating.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains a solution to the problem https://www.techiedelight.com/?problem=FirstKNonRepeating
 * @version 0.1
 * @date 2025-02-22
 *
 * @copyright Copyright (c) 2025 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include "first_k_non_repeating.h"
#include <map>
#include <iostream>

namespace valhalla {

namespace strings {

namespace first_k_non_repeating {

/*

Given a string, find first `k` non-repeating characters in it by doing only a single traversal of it.

Input: s = "ABCDBAGHCHFAC", k = 3
Output: ['D', 'G', 'F']

Input: s = "ABBCDAB", k = 3
Output: ['C', 'D']

If `k` is more than the non-repeating characters count, return all possible non-repeating characters.

Input: s = "YYXBYX", k = 2
Output: ['B']

Input: s = "YYXBYXB", k = 3
Output: []

Note: The solution should return non-repeating characters in the same order as they appear in the string.

*/

std::vector<char> solution_one(std::string s, int k) {
    // TODO: I don't think this is a really good solution even thou it is correct
    std::vector<char> results;
    std::map<char,int> counts;

    for (char chr : s) {
        counts[chr]++;
        if (counts[chr] == 1) {
            results.push_back(chr);
        } else {
            for (std::vector<char>::const_iterator itr = results.begin() ; itr != results.end() ; itr++) {
                if (*itr == chr) {
                    results.erase(itr);
                    break;
                }
            } // for (std::vector<char>::const_iterator itr = results.begin() ; itr != results.end() ; itr++)
        } // if (counts[chr] == 1)
    } // for (char chr : s)

    if (results.size() > k) {
        results.resize(k);
    } // if (results.size() > k)

    return results;
} // solution_one

std::vector<char> Solution::findFirstKNonRepeating(std::string s, int k) {
    return solution_one(s, k);
} // findFirstKNonRepeating

} // namespace first_k_non_repeating

} // namespace strings

} // namespace valhalla
