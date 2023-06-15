/**
 * @file shortest_path_three.h
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief
 * @version 0.1
 * @date 2023-06-15
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */
#ifndef __SHORTEST_PATH_THREE_H__
#define __SHORTEST_PATH_THREE_H__

#include <vector>

namespace valhalla {
    namespace matrices {
        namespace shortest_path_three {
            class Solution {
            public:
                std::vector<std::vector<int>>  updateShortestDistance(std::vector<std::vector<char>> const &);
            };
        }
    }
}

#endif
