/**
 * @file floor_and_ceil.h
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief
 * @version 0.1
 * @date 2023-02-21
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#ifndef __FLOOR_AND_CELL_H__
#define __FLOOR_AND_CELL_H__

#include <vector>
#include <map>

namespace valhalla {
    namespace arrays {
        namespace floor_and_ceil {
            class Solution {
            public:
                std::pair<int,int> findFloorAndCeil(std::vector<int> const &, int);
            };
        }
    }
}

#endif
