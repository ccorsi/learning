/**
 * @file two_sum.h
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This is the include file associated to the two_sum solition
 * @version 0.1
 * @date 2022-12-26
 * 
 * @copyright Copyright (c) 2022 Claudio Corsi
 * 
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#ifndef __TWO_SUM_H__
#define __TWO_SUM_H__

// always include the required implementations and reference them using the fully qualified
// namespace names.
#include <vector>

namespace valhalla {
    namespace arrays {
        namespace two_sum {
            class Solution {
            public:
                std::pair<int,int> find_pair(const std::vector<int> &values, const int target);
            };
        }
    }
}

#endif