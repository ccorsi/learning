/**
 * @file reverse_consecutive_elements.h
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief
 * @version 0.1
 * @date 2023-03-20
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#ifndef __REVERSE_CONSECUTIVE_ELEMENTS_H__
#define __REVERSE_CONSECUTIVE_ELEMENTS_H__

#include <vector>

namespace valhalla {
    namespace arrays {
        namespace reverse_consecutive_elements {
            class Solution {
            public:
                void reverseInGroup(std::vector<int> &, int, int, int);
            };
        }
    }
}

#endif
