/**
 * @file equilibrium_index.h
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief
 * @version 0.1
 * @date 2023-01-25
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#ifndef __EQUILIBRIUM_INDEX_H__
#define __EQUILIBRIUM_INDEX_H__

#include <vector>
#include <unordered_set>

namespace valhalla {
    namespace arrays {
        namespace equilibrium_index {
            class Solution {
            public:
                std::unordered_set<int> find_index(std::vector<int> const &nums);
            };
        }
    }
}

#endif
