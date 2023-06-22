/**
 * @file palindromic_substrings.h
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief
 * @version 0.1
 * @date 2023-06-22
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */
#ifndef __PALINDROMIC_SUBSTRINGS_H__
#define __PALINDROMIC_SUBSTRINGS_H__

#include <string>
#include <unordered_set>

namespace valhalla {
    namespace strings {
        namespace palindromic_substrings {
            class Solution {
            public:
                std::unordered_set<std::string> findPalindromicSubstrings(std::string);
            };
        }
    }
}

#endif
