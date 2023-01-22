/**
 * @file max_continuous_sequence.h
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief
 * @version 0.1
 * @date 2023-01-21
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */
#ifndef __MAXIMUM_CONTINUOUS_SEQUENCE_H__
#define __MAXIMUM_CONTINUOUS_SEQUENCE_H__

#include <vector>

namespace valhalla {
    namespace arrays {
        namespace maximum_continuous_sequence {
            class Solution {
            public:
                int findIndexOfZero(std::vector<int> const &nums);
            };
        }
    }
}

#endif
