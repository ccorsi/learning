/**
 * @file longest_continuous_sequence_three.h
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief
 * @version 0.1
 * @date 2023-06-19
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */
#ifndef __LONGEST_CONTINUOUS_SEQUENCE_THREE_H__
#define __LONGEST_CONTINUOUS_SEQUENCE_THREE_H__

#include <vector>

namespace valhalla {
    namespace matrices {
        namespace longest_continuous_sequence_three {
            class Solution {
                void check(std::vector<std::vector<char>> const &, const int, const int,
                           const char, int, int &);
            public:
                int findMaxLength(std::vector<std::vector<char>> const &, char);
            };
        }
    }
}

#endif
