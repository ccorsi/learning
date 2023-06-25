/**
 * @file anagram_substring.h
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief
 * @version 0.1
 * @date 2023-06-24
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */
#ifndef __ANAGRAM_SUBSTRING_H__
#define __ANAGRAM_SUBSTRING_H__

#include <string>
#include <vector>

namespace valhalla {
    namespace strings {
        namespace anagram_substring {
            class Solution {
            public:
                std::vector<int> findAllAnagrams(std::string, std::string);
            };
        }
    }
}

#endif
