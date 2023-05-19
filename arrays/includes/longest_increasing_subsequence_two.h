/**
 * @file longest_increasing_subsequence_two.h
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief
 * @version 0.1
 * @date 2023-05-15
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#ifndef __LONGEST_INCREASING_SUBSEQUENCE_TWO_H__
#define __LONGEST_INCREASING_SUBSEQUENCE_TWO_H__

#include <vector>

namespace valhalla {
    namespace arrays {
        namespace longest_increasing_subsequence_two {
            class Solution {
                bool findNextValue(std::vector<int> const &, int, int, int, std::vector<int> &, int &);
            public:
                std::vector<int> findLIS(std::vector<int> const &);
            };
        }
    }
}

#endif
