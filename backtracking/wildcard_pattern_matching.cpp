/**
 * @file wildcard_pattern_matching.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This is a solution to the problem https://www.techiedelight.com/?problem=WildcardPatternMatching
 * @version 0.1
 * @date 2025-02-03
 *
 * @copyright Copyright (c) 2025 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include "wildcard_pattern_matching.h"
#include <vector>

namespace valhalla {

namespace backtracking {

namespace wildcard_pattern_matching {

/*

Given a binary pattern containing '?' wildcard character at a few positions, return all
possible combinations of binary strings that can be formed by replacing the wildcard
character by either '0' or '1'.

Input: "1?11?00?1?"
Output: { "1011000010", "1011000011", "1011000110", "1011000111", "1011100010", "1011100011",
    "1011100110", "1011100111", "1111000010", "1111000011", "1111000110", "1111000111",
    "1111100010", "1111100011", "1111100110", "1111100111"
}

*/

std::unordered_set<std::string> solution_two(std::string s) {
    std::unordered_set<std::string> results;

    if (s.empty()) {
        return results;
    }

    std::vector<std::string> processing;

    processing.push_back(s);

    for (std::size_t idx = 0; idx < s.size() ; idx++) {
        if (s[idx] == '?') {
            const std::size_t end = processing.size();
            for (std::size_t curr = 0 ; curr < end ; curr++) {
                processing[curr][idx] = '0';
                std::string copy(processing[curr]);
                copy[idx] = '1';
                processing.push_back(copy);
            }
        }
    }

    results.insert(processing.begin(), processing.end());

    return results;
}

std::unordered_set<std::string> solution_one(std::string s) {
    std::unordered_set<std::string> results;

    if (s.empty()) {
        return results;
    }

    std::vector<std::string> processing;

    processing.push_back(s);

    for (std::size_t idx = 0; idx < s.size() ; idx++) {
        if (s[idx] == '?') {
            const std::size_t end = processing.size();
            for (std::size_t curr = 0 ; curr < end ; curr++) {
                std::string& str = processing[curr];
                str[idx] = '0';
                std::string copy(str);
                copy[idx] = '1';
                processing.push_back(copy);
            }
        }
    }

    results.insert(processing.begin(), processing.end());

    return results;
}

std::unordered_set<std::string> Solution::findCombinations(std::string s) {
    return solution_two(s);
} // findCombinations

} // namespace wildcard_pattern_matching

} // namespace backtracking

} // namespace valhalla
