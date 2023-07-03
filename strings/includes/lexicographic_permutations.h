/**
 * @file lexicographic_permutations.h
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief
 * @version 0.1
 * @date 2023-07-02
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */
#ifndef __LEXICOGRAPHIC_PERMUTATIONS_H__
#define __LEXICOGRAPHIC_PERMUTATIONS_H__

#include <string>
#include <unordered_set>

namespace valhalla {
    namespace strings {
        namespace lexicographic_permutations {
            class Solution {
            public:
                std::unordered_set<std::string> findLexicographicPermutations(std::string);
            };
        }
    }
}

#endif
