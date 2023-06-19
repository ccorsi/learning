/**
 * @file minimum_cost_path.h
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief
 * @version 0.1
 * @date 2023-06-19
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */
#ifndef __MINIMUM_COST_PATH_H__
#define __MINIMUM_COST_PATH_H__

#include <vector>

namespace valhalla {
    namespace matrices {
        namespace minimum_cost_path {
            class Solution {
            public:
                int findMinCost(std::vector<std::vector<int>> const &);
            };
        }
    }
}

#endif
