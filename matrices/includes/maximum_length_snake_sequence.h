/**
 * @file maximum_length_snake_sequence.h
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief
 * @version 0.1
 * @date 2023-06-20
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */
#ifndef __MAXIMUM_LENGTH_SNAKE_SEQUENCE_H__
#define __MAXIMUM_LENGTH_SNAKE_SEQUENCE_H__

#include <vector>

namespace valhalla {
    namespace matrices {
        namespace maximum_length_snake_sequence {
            class Solution {
                void Solution::check(std::vector<std::vector<int>> const & grid, const size_t, const size_t,
                                     const size_t, const int, int &);
            public:
                int findMaxLengthSnakeSequence(std::vector<std::vector<int>> const &);
            };
        }
    }
}

#endif
