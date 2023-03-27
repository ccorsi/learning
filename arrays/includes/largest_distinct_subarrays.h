/**
 * @file largest_distinct_subarrays.h
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief
 * @version 0.1
 * @date 2023-03-26
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#ifndef __LARGEST_DISTINCT_SUBARRAYS_H__
#define __LARGEST_DISTINCT_SUBARRAYS_H__

#include <set>
#include <vector>

namespace valhalla {
    namespace arrays {
        namespace largest_distinct_subarrays {
            class Solution {
            public:
                std::set<std::vector<int>> findDistinctSubarrays(std::vector<int> const &);
            };
        }
    }
}

#endif
