/**
 * @file four_sum.h
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief
 * @version 0.1
 * @date 2023-03-20
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#ifndef __FOUR_SUM_H__
#define __FOUR_SUM_H__

#include <set>
#include <vector>

namespace valhalla {
    namespace arrays {
        namespace four_sum {
            class Solution {
            public:
                std::set<std::vector<int>> findQuadruplets(std::vector<int> const &, int);
            };
        }
    }
}

#endif
