/**
 * @file next_greater_element.h
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief
 * @version 0.1
 * @date 2023-05-03
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */
#ifndef __NEXT_GREATER_ELEMENT_H__
#define __NEXT_GREATER_ELEMENT_H__

#include <vector>

namespace valhalla {
    namespace arrays {
        namespace next_greater_element {
            class Solution {
            public:
                std::vector<int> findNextGreaterElements(std::vector<int> const &);
            };
        }
    }
}

#endif
