/**
 * @file three_partition_problem.h
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief
 * @version 0.1
 * @date 2023-04-12
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#ifndef __THREE_PARTITION_PROBLEM_H__
#define __THREE_PARTITION_PROBLEM_H__

#include <vector>
#include <set>

namespace valhalla {
    namespace arrays {
        namespace three_partition_problem {
            class Solution {
                bool Solution::findSum(std::vector<int> const &, std::set<int> &, std::set<int> &, int, const int);
            public:
                bool partition(std::vector<int> const &);
            };
        }
    }
}

#endif
