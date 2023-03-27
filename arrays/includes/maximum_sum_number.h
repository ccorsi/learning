/**
 * @file maximum_sum_number.h
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief
 * @version 0.1
 * @date 2023-03-26
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#ifndef __MAXIMUM_SUM_NUMBER_H__
#define __MAXIMUM_SUM_NUMBER_H__

#include <utility>
#include <vector>

namespace valhalla {
    namespace arrays {
        namespace maximum_sum_number {
            class Solution {
            public:
                std::pair<int,int> constructMaxSumNumber(std::vector<int> &);
            };
        }
    }
}

#endif
