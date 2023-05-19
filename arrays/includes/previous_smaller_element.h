/**
 * @file previous_smaller_element.h
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief
 * @version 0.1
 * @date 2023-05-14
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#ifndef __PREVIOUS_SMALLER_ELEMENT_H__
#define __PREVIOUS_SMALLER_ELEMENT_H__

#include <vector>

namespace valhalla {
    namespace arrays {
        namespace previous_smaller_element {
            class Solution {
                int findNextGreaterElement(std::vector<int> const &, int, int);
            public:
                std::vector<int> findNextGreaterElements(std::vector<int> const &);
            };
        }
    }
}

#endif
