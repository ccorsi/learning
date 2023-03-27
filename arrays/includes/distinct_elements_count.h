/**
 * @file distinct_elements_count.h
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief
 * @version 0.1
 * @date 2023-03-26
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#ifndef __DISTINCT_ELEMENTS_COUNT_H__
#define __DISTINCT_ELEMENTS_COUNT_H__

#include <vector>

namespace valhalla {
    namespace arrays {
        namespace distinct_elements_count {
            class Solution {
            public:
                std::vector<int> findDistinctCount(std::vector<int> const &, int);
            };
        }
    }
}

#endif
