/**
 * @file zero_sum.h
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief 
 * @version 0.1
 * @date 2022-12-26
 * 
 * @copyright Copyright (c) 2022 Claudio Corsi
 * 
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */
#ifndef __ZERO_SUM_H__
#define __ZERO_SUM_H__

// always include the required libraries and use the fully namespace defined names
#include <vector>

namespace valhalla {
    namespace arrays {
        namespace zero_sum {
            class Solution {
            public:
                bool has_zero_sum(const std::vector<int>&);
            };
        }
    }
}
#endif
