/**
 * @file minimum_absolute_difference_two.h
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief
 * @version 0.1
 * @date 2023-03-22
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#ifndef __MINIMUM_ABSOLUTE_DIFFERENCE_TWO_H__
#define __MINIMUM_ABSOLUTE_DIFFERENCE_TWO_H__

#include <vector>
#include <utility>

namespace valhalla {
    namespace arrays {
        namespace minimum_absolute_difference_two {
            class Solution {
                struct cmp {
                    bool operator()(const std::pair<int,std::pair<int,int>> & lhs, const std::pair<int,std::pair<int,int>> & rhs) {
                        return lhs.second.first < rhs.second.first && lhs.second.second < rhs.second.second;
                    }
                };
            public:
                int findMaxAbsDiff(std::vector<int> &);
            };
        }
    }
}

#endif
