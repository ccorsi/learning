/**
 * @file frequency_map_two.h
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief
 * @version 0.1
 * @date 2023-03-28
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */
#ifndef __FREQUENT_MAP_TWO_H__
#define __FREQUENT_MAP_TWO_H__

#include <unordered_map>
#include <vector>

namespace valhalla {
    namespace arrays {
        namespace frequency_map_two {
            class Solution {
            public:
                std::unordered_map<int,int> findFrequency(std::vector<int> const &);
            };
        }
    }
}

#endif
