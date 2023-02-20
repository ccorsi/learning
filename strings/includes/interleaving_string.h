/**
 * @file interleaving_string.h
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief
 * @version 0.1
 * @date 2023-02-14
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#ifndef __INTERLEAVING_STRING_H__
#define __INTERLEAVING_STRING_H__

#include <string>
#include <unordered_set>

namespace valhalla {
    namespace strings {
        namespace interleaving_string {
            class Solution {
            public:
                std::unordered_set<std::string> findInterleavings(std::string, std::string);
            };
        }
    }
}

#endif
