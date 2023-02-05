/**
 * @file largest_consecutive_subarray.h
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief
 * @version 0.1
 * @date 2023-01-25
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#ifndef __LARGEST_CONSECUTIBVE_SUBARRAY_H__
#define __LARGEST_CONSECUTIBVE_SUBARRAY_H__

#include <vector>

namespace valhalla {
    namespace arrays {
        namespace largest_consecutive_subarray {
            class Solution {
            public:
                std::vector<int> findLargestSubarray(std::vector<int> const &);
            };
        }
    }
}

#endif
