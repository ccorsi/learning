/**
 * @file longest_distinct_substring_two.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains a solution to the problem https://www.techiedelight.com/?problem=LongestDistinctSubstringII
 * @version 0.1
 * @date 2023-06-24
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */


#include "longest_distinct_substring_two.h"

#include <iostream>
#include <map>
#include <set>

namespace valhalla {
    namespace strings {
        namespace longest_distinct_substring_two {
            /*

            Given a string, find the longest substring containing distinct characters.

            Input : "longestsubstr"
            Output: "longest"

            Input : "abbcdafeegh"
            Output: "bcdafe"

            Input : "aaaaaa"
            Output: "a"

            The longest distinct character substring is not guaranteed to be unique.
            If multiple longest distinct substring exists, the solution should return
            the one which appear first in the string.

            Input: "cbabc"
            Output: "cba"
            Explanation: There are two longest distinct substrings in "cbaabc" of
            length 3, namely, "cba" and "abc". The solution returns "cba" as it appears
            before "abc" in the string.

            */

            std::string Solution::findLongestSubstring(std::string s) {
                std::string longest;
                std::map<std::string::size_type, std::set<char>> counts;
                std::string::size_type start = 0, length = 0;

                for(std::string::size_type idx = 0 ; idx < s.size() ; idx++ ) {
                    const char chr = s[idx];
                    std::string::size_type current = idx;
                    while ( current >= 0 ) {
                        if (counts[current].insert(chr).second == false) {
                            break;
                        }
                        const std::string::size_type size = counts[current].size();
                        if (size == idx - current + 1 && size > length) {
                            start = current;
                            length = idx - current + 1;
                        }
                        if (current == 0) {
                            break;
                        }
                        current--;
                    } // while
                } // for

                if (length > 0) {
                    longest = s.substr(start,length);
                } // if

                return longest;
            } // findLongestSubstring
        }
    }
}
