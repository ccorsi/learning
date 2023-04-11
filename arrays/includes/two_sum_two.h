/**
 * @file two_sum_two.h
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief
 * @version 0.1
 * @date 2023-04-05
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#ifndef __TWO_SUM_TWO_H__
#define __TWO_SUM_TWO_H__

#include <utility>
#include <vector>

namespace valhalla {
    namespace arrays {
        namespace two_sum_two {
            class Solution {
            public:
                std::pair<int,int> findPair(std::vector<int> const &, int);
            };
        }
    }
}

#endif
