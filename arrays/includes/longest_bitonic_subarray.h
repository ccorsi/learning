/**
 * @file longest_bitonic_subarray.h
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief
 * @version 0.1
 * @date 2023-02-04
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#ifndef __LONGEST_BITONIC_SUBARRAY_H__
#define __LONGEST_BITONIC_SUBARRAY_H__

#include <vector>

namespace valhalla {
    namespace arrays {
        namespace longest_bitonic_subarray {
            class Solution {
            public:
                std::vector<int> findBitonicSubarray(std::vector<int> const &);
            };
        }
    }
}

#endif
