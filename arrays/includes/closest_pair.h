/**
 * @file closest_pair.h
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief
 * @version 0.1
 * @date 2023-03-23
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#ifndef __CLOSEST_PAIR_H__
#define __CLOSEST_PAIR_H__

#include <utility>
#include <vector>

namespace valhalla {
    namespace arrays {
        namespace closest_pair {
            class Solution {
            public:
                std::pair<int,int> findClosestPair(std::vector<int> const &, std::vector<int> const &, int);
            };
        }
    }
}

#endif
