/**
 * @file common_elements.h
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief
 * @version 0.1
 * @date 2023-03-01
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#ifndef __COMMON_ELMENTS_H__
#define __COMMON_ELMENTS_H__

#include <vector>
#include <unordered_set>

namespace valhalla {
    namespace matrices {
        namespace common_elements {
            class Solution {
            public:
                std::unordered_set<int> findCommonElements(std::vector<std::vector<int>> const &);
            };
        }
    }
}

#endif
