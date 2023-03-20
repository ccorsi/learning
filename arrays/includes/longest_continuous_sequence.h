/**
 * @file longest_continuous_sequence.h
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief
 * @version 0.1
 * @date 2023-03-19
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#ifndef __LONGEST_CONTINUOUS_SEQUENCE_H__
#define __LONGEST_CONTINUOUS_SEQUENCE_H__

#include <vector>

namespace valhalla {
    namespace arrays {
        namespace longest_continuous_sequence {
            class Solution {
            public:
                int findMaxSubarrayLength(std::vector<int> const &, std::vector<int> const &);
            };
        }
    }
}

#endif
