/**
 * @file greater_elements.h
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief
 * @version 0.1
 * @date 2023-04-05
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#ifndef __GREATER_ELEMENTS_H__
#define __GREATER_ELEMENTS_H__

#include <vector>

namespace valhalla {
    namespace arrays {
        namespace greater_elements {
            class Solution {
                // void is_greater(std::vector<int> &, std::vector<int> const &, int, int);
            public:
                std::vector<int> findGreaterElements(std::vector<int> const &);
            };
        }
    }
}

#endif
