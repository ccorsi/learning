/**
 * @file replace_element_in_young_tableau.h
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief
 * @version 0.1
 * @date 2023-06-21
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */
#ifndef __REPLACE_ELEMENT_IN_YOUNG_TABLEAU_H__
#define __REPLACE_ELEMENT_IN_YOUNG_TABLEAU_H__

#include <vector>

namespace valhalla {
    namespace matrices {
        namespace replace_element_in_young_tableau {
            class Solution {
            public:
                void replaceInYoungTableau(std::vector<std::vector<int>> &, int, int);
            };
        }
    }
}

#endif
