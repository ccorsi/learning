/**
 * @file minimum_absolute_sum_pair.h
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief
 * @version 0.1
 * @date 2023-03-27
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#ifndef __MINIMUM_ABSOLUTE_SUM_PAIR_H__
#define __MINIMUM_ABSOLUTE_SUM_PAIR_H__

#include <utility>
#include <vector>

namespace valhalla {
    namespace arrays {
        namespace minimum_absolute_sum_pair {
            class Solution {
            public:
                std::pair<int,int> findPair(std::vector<int> const &);
            };
        }
    }
}

#endif
