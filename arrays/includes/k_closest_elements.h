/**
 * @file k_closest_elements.h
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief
 * @version 0.1
 * @date 2023-02-21
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#ifndef __K_CLOSEST_ELEMENTS_H__
#define __K_CLOSEST_ELEMENTS_H__

#include <vector>

namespace valhalla {
    namespace arrays {
        namespace k_closest_elements {
            class Solution {
            public:
                std::vector<int> kClosestElements(std::vector<int> const &, int, int);
            };
        }
    }
}

#endif
