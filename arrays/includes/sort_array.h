/**
 * @file sort_array.h
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief
 * @version 0.1
 * @date 2023-04-05
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#ifndef __SORT_ARRAY_H__
#define __SORT_ARRAY_H__

#include <vector>

namespace valhalla {
    namespace arrays {
        namespace sort_array {
            class Solution {
                void quicksort(std::vector<int> &, int, int);
                int  partition(std::vector<int> &, int, int);
            public:
                void sort(std::vector<int> &);
            };
        }
    }
}

#endif
