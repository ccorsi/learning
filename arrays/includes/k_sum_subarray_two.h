/**
 * @file k_sum_subarray_two.h
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief
 * @version 0.1
 * @date 2023-03-15
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#ifndef __K_SUM_SUBARRAY_TWO_H__
#define __K_SUM_SUBARRAY_TWO_H__

#include <set>
#include <vector>

namespace valhalla {
    namespace arrays {
        namespace k_sum_subarray_two {
            class Solution {
            public:
                std::set<std::vector<int>> getAllSubarrays(std::vector<int> const &, int);
            };
        }
    }
}

#endif
