/**
 * @file smallest_window_to_sort_array.h
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief
 * @version 0.1
 * @date 2023-03-15
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#ifndef __SMALLEST_WINDOW_TO_SORT_ARRAY_H__
#define __SMALLEST_WINDOW_TO_SORT_ARRAY_H__

#include <vector>
#include <utility>

namespace valhalla {
    namespace arrays {
        namespace smallest_window_to_sort_array {
            class Solution {
            public:
                std::pair<int,int> findSmallestWindow(std::vector<int> const &);
            };
        }
    }
}

#endif
