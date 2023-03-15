/**
 * @file k_sum_subarray.h
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief
 * @version 0.1
 * @date 2023-03-15
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#ifndef __K_SUM_SUBARRAY_H__
#define __K_SUM_SUBARRAY_H__

#include <vector>

namespace valhalla {
    namespace arrays {
        namespace k_sum_subarray {
            class Solution {
                void checkSubArray(std::vector<int> const &, const int, std::vector<int> &, int, int);
            public:
                std::vector<int> findSubarray(std::vector<int> const &, int);
            };
        }
    }
}

#endif
