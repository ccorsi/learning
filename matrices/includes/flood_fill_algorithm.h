/**
 * @file flood_fill_algorithm.h
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief
 * @version 0.1
 * @date 2023-06-20
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */
#ifndef __FLOOD_FILL_ALGORITHM_H__
#define __FLOOD_FILL_ALGORITHM_H__

#include <vector>

namespace valhalla {
    namespace matrices {
        namespace flood_fill_algorithm {
            class Solution {
            public:
                void floodfill(std::vector<std::vector<char>> &, int, int, char);
            };
        }
    }
}

#endif
