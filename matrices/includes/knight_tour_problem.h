/**
 * @file knight_tour_problem.h
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief
 * @version 0.1
 * @date 2023-03-01
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#ifndef __KNIGHT_TOUR_PROBLEM_H__
#define __KNIGHT_TOUR_PROBLEM_H__

#include <vector>
#include <set>

namespace valhalla {
    namespace matrices {
        namespace knight_tour_problem {
            class Solution {
                bool is_valid_move(std::vector<std::vector<int>> const &, std::pair<int,int> const &, int);
            public:
                std::set<std::vector<std::vector<int>>> _knightTour(int);
            };
        }
    }
}

#endif
