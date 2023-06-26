/**
 * @file balanced_parentheses.h
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief
 * @version 0.1
 * @date 2023-06-26
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */
#ifndef __BALANCED_PARENTHESES_H__
#define __BALANCED_PARENTHESES_H__

#include <string>
#include <unordered_set>

namespace valhalla {
    namespace strings {
        namespace balanced_parentheses {
            class Solution {
            public:
                std::unordered_set<std::string> findPalindromicPermutations(int);
            };
        }
    }
}

#endif
