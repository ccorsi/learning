/**
 * @file group_anagrams.h
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief
 * @version 0.1
 * @date 2023-06-23
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */
#ifndef __GROUP_ANAGRAMS_H__
#define __GROUP_ANAGRAMS_H__

#include <set>
#include <string>
#include <vector>

namespace valhalla {
    namespace strings {
        namespace group_anagrams {
            class Solution {
            public:
                std::set<std::set<std::string>> groupAnagrams(std::vector<std::string> const &);
            };
        }
    }
}

#endif
