/**
 * @file k_partition_problem.h
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief
 * @version 0.1
 * @date 2023-04-12
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#ifndef __K_PARTITION_PROBLEM_H__
#define __K_PARTITION_PROBLEM_H__

#include <vector>

namespace valhalla {
    namespace arrays {
        namespace k_partition_problem {
            class Solution {
            public:
                std::vector<std::vector<int>> getSubsets(std::vector<int> const &, int);
            };
        }
    }
}

#endif
