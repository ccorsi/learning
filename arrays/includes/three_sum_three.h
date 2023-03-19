/**
 * @file three_sum_three.h
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief
 * @version 0.1
 * @date 2023-03-19
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#ifndef __THREE_SUM_THREE_H__
#define __THREE_SUM_THREE_H__

#include <vector>
#include <set>

namespace valhalla {
    namespace arrays {
        namespace three_sum_three {
            class Solution {
                void Solution::isTriplets(std::vector<int> &, const int, std::set<std::vector<int>> &, const int, std::vector<int> &, const int, const int);
            public:
                std::set<std::vector<int>> getTriplets(std::vector<int> &, int);
            };
        }
    }
}

#endif
