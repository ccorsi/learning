/**
 * @file longest_increasing_subsequence.h
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief
 * @version 0.1
 * @date 2023-05-15
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#ifndef __LONGEST_INCREASING_SUBSEQUENCE_H__
#define __LONGEST_INCREASING_SUBSEQUENCE_H__

#include <vector>

namespace valhalla {
    namespace arrays {
        namespace longest_increasing_subsequence {
            class Solution {
                void findNextIncreasingValue(std::vector<int> const & nums, int value, int currentLength, int idx, const int size, int & longest);
            public:
                int findLISLength(std::vector<int> const &);
            };
        }
    }
}

#endif
