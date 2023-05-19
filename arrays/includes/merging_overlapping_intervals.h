/**
 * @file merging_overlapping_intervals.h
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief
 * @version 0.1
 * @date 2023-05-15
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#ifndef __MERGING_OVERLAPPING_INTERVALS_H__
#define __MERGING_OVERLAPPING_INTERVALS_H__

#include <utility>
#include <set>
#include <vector>

namespace valhalla {
    namespace arrays {
        namespace merging_overlapping_intervals {
            class Solution {
            public:
                std::set<std::pair<int,int>> mergeIntervals(std::vector<std::pair<int,int>>);
            };
        }
    }
}

#endif
