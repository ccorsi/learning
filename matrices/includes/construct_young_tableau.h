/**
 * @file construct_young_tableau.h
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief
 * @version 0.1
 * @date 2023-06-21
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */
#ifndef __CONSTRUCT_YOUNG_TABLEAU_H__
#define __CONSTRUCT_YOUNG_TABLEAU_H__

#include <vector>

namespace valhalla {
    namespace matrices {
        namespace construct_young_tableau {
            class Solution {
            public:
                std::vector<std::vector<int>> constructYoungTableau(std::vector<int> const &);
            };
        }
    }
}

#endif
