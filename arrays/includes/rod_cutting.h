/**
 * @file rod_cutting.h
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief
 * @version 0.1
 * @date 2023-05-20
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#ifndef __ROD_CUTTING_H__
#define __ROD_CUTTING_H__

#include <vector>

namespace valhalla {
    namespace arrays {
        namespace rod_cutting {
            class Solution {
            public:
                int findMaxProfit(std::vector<int> const &, int);
            };
        }
    }
}

#endif
