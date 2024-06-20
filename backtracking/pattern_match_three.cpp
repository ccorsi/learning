/**
 * @file pattern_match_three.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains a solution to the problem https://www.techiedelight.com/?problem=PatternMatchIII
 * @version 0.1
 * @date 2023-07-04
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include <cstddef>
#include <map>
#include <iostream>

#include "pattern_match_three.h"

namespace valhalla {

namespace backtracking {

namespace pattern_match_three {

/*

Given a string and a pattern, determine whether a string matches with a given pattern.

Input: word = "codesleepcode", pattern = "XYX"
Output: true
Explanation: 'X' can be mapped to "code" and 'Y' can be mapped to "sleep"

Input: word = "codecodecode", pattern = "XXX"
Output: true
Explanation: 'X' can be mapped to "code"

*/

void Solution::compare(std::string & word, std::string & pattern, const std::size_t widx,
                       const std::size_t pidx, std::map<char,std::string> & words, bool & matches) {
    if (pidx == pattern.size()) {
        if (word.size() == widx) {
            matches = true;
        } // if (word.size() == widx)
        return;
    } // if (pidx == pattern.size())

    char key = pattern[pidx];
    std::string & current = words[key];

    if (current.empty()) {
        const auto padding = pattern.length() - pidx - 1;
        for (auto next = 0 ; widx + next + padding < word.length() ; ) {
            // Append the next character to the current string for the given pattern
            current += word[widx + next++];
            // std::cout << "current: '" << current << "' widx " << ( widx + next ) << " pidx " << pidx << "\n";
            compare(word, pattern, widx + next, pidx + 1, words, matches);
            if (matches) {
                // std::cout << "We found a match\n";
                // we are done thus return
                return;
            } // if (matches)
        }
        // reset the current string???
        current.clear();
    } else {
        // std::cout << "current: '" << current << "' widx " << widx << " pidx " << pidx << "\n";
        if (current.length() + widx > word.length()) {
            // std::cout << "current length + widx is greater than word length [" << (current.length() + widx) << "," << word.length() << "]\n";
            // we are done
            return;
        } // if (current.length() + widx >= word.length())
        std::string str = word.substr(widx, current.length());
        // std::cout << "Compare current: '" << current << "' with str '" << str << "'" << " with key '" << key << "'\n";
        if (current != str) {
            // we are done
            // std::cout << "current != str '" << current << "' '" << str << "'\n";
            return;
        } // if (current.length() + widx >= word.length() || current != word.substr(widx, current.length()))
        // std::cout << "current == str '" << current << "' '" << str << "'\n";
        compare(word, pattern, widx + current.length(), pidx + 1, words, matches);
    } // if (current.empty())
} // compare

bool Solution::checkPattern(std::string word, std::string pattern) {
    bool matches = false;

    // determine the number of words that need to be found and how many
    // instances of each word and in which order they are expected to be
    // found.
    std::map<char,std::string> words;

    compare(word, pattern, 0, 0, words, matches);

    return matches;
} // checkPattern

} // namespace pattern_match_three

} // namespace backtracking

} // namespace valhalla
