/**
 * @file maximum_length_subarray.h
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief 
 * @version 0.1
 * @date 2023-01-01
 * 
 * @copyright Copyright (c) 2023 Claudio Corsi
 * 
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */
#ifndef __MAXIMUM_LENGTH_SUBARRAY_H__
#define __MAXIMUM_LENGTH_SUBARRAY_H__

#include <vector>

namespace valhalla {
    namespace arrays {
        namespace maximum_length_subarray {
            class Solution {
            public:
                std::vector<int> find_maximum_subarray(std::vector<int> const &, int);
            };
        }
    }
}

#endif
