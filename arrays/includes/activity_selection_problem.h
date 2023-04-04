/**
 * @file activity_selection_problem.h
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief
 * @version 0.1
 * @date 2023-04-03
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#ifndef __ACTIVITY_SELECTION_PROBLEM_H__
#define __ACTIVITY_SELECTION_PROBLEM_H__

#include <utility>
#include <vector>
#include <set>

namespace valhalla {
    namespace arrays {
        namespace activity_selection_problem {
            class Solution {
            public:
                std::set<std::pair<int,int>> selectActivity(std::vector<std::pair<int,int>>);
            };
        }
    }
}

#endif
