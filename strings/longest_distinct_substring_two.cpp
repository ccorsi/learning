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



                return longest;
            } // findLongestSubstring
        }
    }
}
