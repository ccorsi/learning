/**
 * @file unbounded_search_sorted_array.h
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief
 * @version 0.1
 * @date 2023-02-20
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#ifndef __UNBOUNDED_SEARCH_SORTED_ARRAY_H__
#define __UNBOUNDED_SEARCH_SORTED_ARRAY_H__

#include <functional>

extern std::function<int(int)> f;

namespace valhalla {
    namespace arrays {
        namespace unbounded_search_sorted_array {
            class Solution {
            public:
                int findValue();
            };
        }
    }
}

#endif
