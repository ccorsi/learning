/**
 * @file search_nearly_sorted_array.h
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief
 * @version 0.1
 * @date 2023-02-21
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#ifndef __SEARCH_NEARLY_SORTED_ARRAY_H__
#define __SEARCH_NEARLY_SORTED_ARRAY_H__

#include <vector>

namespace valhalla {
    namespace arrays {
        namespace search_nearly_sorted_array {
            class Solution {
                int findIndex(std::vector<int> const &, int, std::vector<int>::size_type,
                              std::vector<int>::size_type, std::vector<int>::size_type);
            public:
                int findIndex(std::vector<int> const &, int);
            };
        }
    }
}

#endif
