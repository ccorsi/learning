/**
 * @file pattern_match.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains a solution to the problem https://www.techiedelight.com/?problem=PatternMatch
 * @version 0.1
 * @date 2023-07-03
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include "pattern_match.h"

namespace valhalla {

namespace strings {

namespace pattern_match {

/*

Given a list of words and a pattern, find all words in the list that follows the same order of characters as that of the pattern.

Input:

words = [leet, abcd, loot, geek, cool, for, peer, dear, seed, meet, noon, otto, mess, loss]
pattern = moon

Output: {leet, loot, geek, cool, peer, seed, meet}

Explanation: Pattern is 4 digits with distinct character at first and last index, and same character at 1st and 2nd index


Input:

words = [leet, abcd, loot, geek, cool, for, peer, dear, seed, meet, noon, otto, mess, loss]
pattern = pqrs

Output: {abcd, dear}

Explanation: Pattern is 4 digits and has all distinct characters

*/

std::unordered_set<std::string> Solution::patternMatch(std::unordered_set<std::string> const & words, std::string pattern) {
    std::unordered_set<std::string> matches;


    return matches;
} // patternMatch

} // namespace pattern_match

} // namespace strings

} // namespace valhalla
