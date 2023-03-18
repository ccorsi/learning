/**
 * @file decode_array.h
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief
 * @version 0.1
 * @date 2023-03-17
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#ifndef __DECODE_ARRAY_H__
#define __DECODE_ARRAY_H__

#include <vector>

namespace valhalla {
    namespace arrays {
        namespace decode_array {
            class Solution {
            public:
                std::vector<int> decode(std::vector<int> const &);
            };
        }
    }
}

#endif
