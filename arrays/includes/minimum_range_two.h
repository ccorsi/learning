/**
 * @file minimum_range_two.h
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief
 * @version 0.1
 * @date 2023-04-01
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#ifndef __MINIMUM_RANGE_TWO_H__
#define __MINIMUM_RANGE_TWO_H__

#include <utility>
#include <vector>

namespace valhalla {
    namespace arrays {
        namespace minimum_range_two {
            class Solution {
            public:
                std::pair<int,int> findMinimumRange(std::vector<std::vector<int>> const &);
            };
        }
    }
}

#endif
