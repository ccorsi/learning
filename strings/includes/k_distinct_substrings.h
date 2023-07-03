/**
 * @file k_distinct_substrings.h
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief
 * @version 0.1
 * @date 2023-07-03
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */
#ifndef __K_DISTINCT_SUBSTRINGS_H__
#define __K_DISTINCT_SUBSTRINGS_H__

#include <string>
#include <unordered_set>

namespace valhalla {
    namespace strings {
        namespace k_distinct_substrings {
            class Solution {
            public:
                std::unordered_set<std::string> findDistinctSubstrings(std::string, int);
            };
        }
    }
}

#endif
