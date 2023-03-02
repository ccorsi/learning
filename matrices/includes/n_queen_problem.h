/**
 * @file n_queen_problem.h
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief
 * @version 0.1
 * @date 2023-03-01
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#ifndef __N_QUEEN_PROBLEM_H__
#define __N_QUEEN_PROBLEM_H__

#include <vector>
#include <set>

namespace valhalla {
    namespace matrices {
        namespace n_queen_problem {
            class Solution {
                bool is_valid(std::vector<int> const &, int);
            public:
                std::set<std::vector<std::vector<int>>> solveNQueen(int);
            };
        }
    }
}

#endif
