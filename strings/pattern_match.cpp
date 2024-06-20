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

#include <map>
#include <set>

namespace valhalla {

namespace strings {

namespace pattern_match {

/*

Given a list of words and a pattern, find all words in the list that follows the same order
of characters as that of the pattern.

Input:

words = [leet, abcd, loot, geek, cool, for, peer, dear, seed, meet, noon, otto, mess, loss]
pattern = moon

Output: {leet, loot, geek, cool, peer, seed, meet}

Explanation: Pattern is 4 digits with distinct character at first and last index, and same
character at 1st and 2nd index


Input:

words = [leet, abcd, loot, geek, cool, for, peer, dear, seed, meet, noon, otto, mess, loss]
pattern = pqrs

Output: {abcd, dear}

Explanation: Pattern is 4 digits and has all distinct characters

*/

std::unordered_set<std::string> Solution::patternMatch(std::unordered_set<std::string> const & words, std::string pattern) {
    std::unordered_set<std::string> matches;

    if ( ! pattern.empty() ) {
        const std::string::size_type size = pattern.size();

        for(std::string word : words) {
            if (word.size() != size) continue;
            std::map<char,char> match;
            std::set<char> processed;
            std::string::iterator witr = word.begin();

            for (std::string::iterator pitr = pattern.begin() ; witr != word.end() ; witr++, pitr++) {
                char chr = *pitr;
                if (match.end() != match.find(chr)) {
                    if (match[chr] != *witr) break;
                } else {
                    if (processed.find(*witr) != processed.end()) break;
                    match[chr] = *witr;
                    processed.insert(*witr);
                } // else
            } // for

            if (witr == word.end()) matches.insert(word);
        } // for
    } // if

    return matches;
} // patternMatch

} // namespace pattern_match

} // namespace strings

} // namespace valhalla