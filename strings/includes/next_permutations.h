/**
 * @file next_permutations.h
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief
 * @version 0.1
 * @date 2023-06-26
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */
#ifndef __NEXT_PERMUTATIONS_H__
#define __NEXT_PERMUTATIONS_H__

#include <string>
#include <vector>

namespace valhalla {
    namespace strings {
        namespace next_permutations {
            class Solution {
            public:
                std::vector<std::string> findPermutations(std::string);
            };
        }
    }
}

#endif
