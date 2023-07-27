/**
 * @file longest_distinct_substring.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains a solution to the problem https://www.techiedelight.com/?problem=LongestDistinctSubstring
 * @version 0.1
 * @date 2023-06-24
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include "longest_distinct_substring.h"

#include <iostream>
#include <map>
#include <set>

namespace valhalla {
    namespace strings {
        namespace longest_distinct_substring {
            /*

            Given a string and a positive number `k`, find the longest substring of the
            string containing `k` distinct characters. If `k` is more than the total
            number of distinct characters in the string, return the whole string.

            Input: s = "abcbdbdbbdcdabd", k = 2
            Output: "bdbdbbd"

            Input: s = "abcbdbdbbdcdabd", k = 3
            Output: "bcbdbdbbdcd"

            Input: s = "abcbdbdbbdcdabd", k = 5
            Output: "abcbdbdbbdcdabd"

            The longest distinct character substring is not guaranteed to be unique. If
            multiple longest distinct substring exists, the solution should return the
            one which appear first in the string.

            Input: s = "abcd", k = 3
            Output: "abc"
            Explanation: There are two longest distinct substrings in "abcd" having 3
            distinct characters, namely, "abc" and "bcd". The solution returns "abc" as
            it appears before "bcd" in the string.


            */

            std::string Solution::findLongestSubstring(std::string s, int k) {
                std::string longest;

                if (s.empty()) return longest;

                std::map<std::string::size_type,std::set<char>> counts;
                std::string::size_type start = 0, idx = 0, length = 0;

                for ( ; idx < s.size(); idx++) {
                    char chr = s[idx];
                    std::string::size_type current = idx;
                    while (counts[current].size() <= k) {
                        counts[current].insert(chr);
                        if (counts[current].size() <= k) {
                            if (idx - current + 1 > length) {
                                start = current;
                                length = idx - current + 1;
                            }
                        } else if (counts[current].size() > k) {
                            break;
                        }

                        if (current == 0) {
                            break;
                        }
                        current--;
                    }
                }

                if (length > 0) {
                    longest = s.substr(start, length);
                }

                return longest;
            } // findLongestSubstring
        }
    }
}
