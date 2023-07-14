/**
 * @file k_distinct_substrings.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains a solution to the problem https://www.techiedelight.com/?problem=KDistinctSubstrings
 * @version 0.1
 * @date 2023-07-03
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include "k_distinct_substrings.h"

#include <set>

namespace valhalla {
    namespace strings {
        namespace k_distinct_substrings {
            /*

            Given a string and a positive integer k, find all distinct substrings of any
            length containing exactly k distinct characters.

            Input:  str = "abcbd", k = 3
            Output: {"abc", "abcb", "bcbd", "cbd"}

            Input:  str = "abcadce", k = 4
            Output: {"abcad", "abcadc", "bcad", "bcadc", "cadce", "adce"}

            Input:  str = "aa", k = 1
            Output: {"a", "aa"}

            */

            std::unordered_set<std::string> Solution::findDistinctSubstrings(std::string s, int k) {
                std::unordered_set<std::string> substrings;

                if (s.size() >= k) {
                    const std::string::size_type size = s.size(), last = s.size() - k + 1;
                    for (std::string::size_type start = 0 ; start < last ; start++) {
                        std::set<char> distinct;
                        for (std::string::size_type idx = start ; idx < size ; idx++) {
                            distinct.insert(s[idx]);
                            if (distinct.size() == k) {
                                substrings.insert(s.substr(start, idx - start + 1));
                            } else if (distinct.size() > k) {
                                break;
                            }
                        } // for
                    } // for
                } // if

                return substrings;
            } // findDistinctSubstrings
        }
    }
}
