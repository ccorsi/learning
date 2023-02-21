/**
 * @file search_sorted_array.h
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief
 * @version 0.1
 * @date 2023-02-20
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#ifndef __SEARCH_SORTED_ARRAY_H__
#define __SEARCH_SORTED_ARRAY_H__

#include <vector>

namespace valhalla {
    namespace arrays {
        namespace search_sorted_array {
            class Solution {
            public:
                int findIndex(std::vector<int> const &, int);
            };
        }
    }
}

#endif
