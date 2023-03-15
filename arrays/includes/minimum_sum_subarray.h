/**
 * @file minimum_sum_subarray.h
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief
 * @version 0.1
 * @date 2023-03-14
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#ifndef __MINIMUM_SUM_SUBARRAY_H__
#define __MINIMUM_SUM_SUBARRAY_H__

#include <vector>

namespace valhalla {
    namespace arrays {
        namespace minimum_sum_subarray {
            class Solution {
            public:
                std::vector<int> findMinSumSubarray(std::vector<int> const &, int);
            };
        }
    }
}

#endif
