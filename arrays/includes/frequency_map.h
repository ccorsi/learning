/**
 * @file frequency_map.h
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief
 * @version 0.1
 * @date 2023-03-27
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#ifndef __FREQUENCY_MAP_H__
#define __FREQUENCY_MAP_H__

#include <unordered_map>
#include <vector>

namespace valhalla {
    namespace arrays {
        namespace frequency_map {
            class Solution {
            public:
                std::unordered_map<int,int> findFrequency(std::vector<int> &);
            };
        }
    }
}

#endif
