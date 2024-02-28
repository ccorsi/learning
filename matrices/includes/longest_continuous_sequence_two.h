/**
 * @file longest_continuous_sequence_two.h
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief
 * @version 0.1
 * @date 2023-06-19
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */
#ifndef __LONGEST_CONTINUOUS_SEQUENCE_TWO_H__
#define __LONGEST_CONTINUOUS_SEQUENCE_TWO_H__

#include <vector>

namespace valhalla {
    namespace matrices {
        namespace longest_continuous_sequence_two {
            class Solution {
                void check(std::vector<std::vector<int>> const &, const int, const int,
                           std::vector<int> &, std::vector<int> &);
            public:
                std::vector<int> findLongestPath(std::vector<std::vector<int>> const &);
            };
        }
    }
}

#endif
