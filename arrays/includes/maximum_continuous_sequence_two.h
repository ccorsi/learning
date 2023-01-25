/**
 * @file maximum_continuous_sequence_two.h
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief
 * @version 0.1
 * @date 2023-01-22
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#ifndef __MAXIMUM_CONTINUOUS_SEQUENCE_TWO_H__
#define __MAXIMUM_CONTINUOUS_SEQUENCE_TWO_H__

#include<vector>

namespace valhalla {
    namespace arrays {
        namespace maximum_continuous_sequence_two {
            class Solution {
            public:
                std::pair<int,int> findLongestSequence(std::vector<int> const &, int);
            };
        }
    }
}

#endif
