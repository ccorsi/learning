/**
 * @file smallest_subarray.h
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief
 * @version 0.1
 * @date 2023-03-15
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#ifndef __SMALLEST_SUBARRAY_H__
#define __SMALLEST_SUBARRAY_H__

#include <vector>

namespace valhalla {
    namespace arrays {
        namespace smallest_subarray {
            class Solution {
            public:
                int findSmallestSubarray(std::vector<int> const &, int);
            };
        }
    }
}

#endif
