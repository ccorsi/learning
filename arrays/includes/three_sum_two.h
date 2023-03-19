/**
 * @file three_sum_two.h
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief
 * @version 0.1
 * @date 2023-03-18
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#ifndef __THREE_SUM_TWO_H__
#define __THREE_SUM_TWO_H__

#include <vector>

namespace valhalla {
    namespace arrays {
        namespace three_sum_two {
            class Solution {
                bool isTriplets(std::vector<int> &, const int, const int, std::vector<int> &, const int, const int);
            public:
                std::vector<int> findTriplets(std::vector<int> &, int);
            };
        }
    }
}

#endif
