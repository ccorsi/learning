/**
 * @file sorted_merge_arrays.h
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief
 * @version 0.1
 * @date 2023-02-11
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#ifndef __SORTED_MERGE_ARRAYS_H__
#define __SORTED_MERGE_ARRAYS_H__

#include <vector>

namespace valhalla {
    namespace arrays {
        namespace sorted_merge_arrays {
            class Solution {
            public:
                std::vector<int> merge(std::vector<int> const &, std::vector<int> const &);
            };
        }
    }
}

#endif
