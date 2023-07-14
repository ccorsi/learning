/**
 * @file pattern_match_two.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains a solution to the problem https://www.techiedelight.com/?problem=PatternMatchII
 * @version 0.1
 * @date 2023-07-04
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include "pattern_match_two.h"

namespace valhalla {

namespace strings {

namespace pattern_match_two {

/*

Given a string and a pattern, determine whether the string characters follow the
specific order defined by the pattern’s characters. You may assume that the
pattern contains all distinct characters.

Input: word = "Techie Delight", pattern = "el"
Output: true
Explanation: The pattern characters follow the order [e, e, e, l] in the input string. All e’s appear before 'l'.

Input: word = "Techie Delight", pattern = "ei"
Output: false
Explanation: The pattern characters follow the order [e, i, e, e, i] in the input string. All e’s doesn’t appear before all i’s.

*/

bool Solution::checkPattern(std::string word, std::string pattern) {

    if ( ! pattern.empty() ) {
        std::string::size_type idx = 0;
        const std::string::size_type psize = pattern.size(), wsize = word.size();
        char chr;
        while (idx < psize) {
            chr = pattern[idx];
            std::string::size_type pos = word.find_last_of(chr);
            if (pos == word.npos) return false;
            idx++;
            if (idx == psize) return true;
            chr = pattern[idx];
            if (word.find_first_of(chr) <= pos) return false;
            // start_at = pos + 1;
            // if (start_at == wsize) return false;
        } // while
    }

    return true;
} // checkPattern

} // namespace pattern_match_two

} // namespace strings

} // namespace valhalla
