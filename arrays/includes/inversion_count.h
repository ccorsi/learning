/**
 * @file inversion_count.h
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief
 * @version 0.1
 * @date 2023-04-11
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#ifndef __INVERSION_COUNT_H__
#define __INVERSION_COUNT_H__

#include <vector>

namespace valhalla {
    namespace arrays {
        namespace inversion_count {
            class Solution {
            public:
                int findInversionCount(std::vector<int> &);
            };
        }
    }
}

#endif
