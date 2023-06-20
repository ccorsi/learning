/**
 * @file collect_maximum_points.h
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief
 * @version 0.1
 * @date 2023-06-19
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */
#ifndef __COLLECT_MAXIMUM_POINTS_H__
#define __COLLECT_MAXIMUM_POINTS_H__

#include <vector>

namespace valhalla {
    namespace matrices {
        namespace collect_maximum_points {
            class Solution {
            public:
                int findMaximumPoints(std::vector<std::vector<int>> const &);
            };
        }
    }
}

#endif
