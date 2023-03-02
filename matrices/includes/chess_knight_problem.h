/**
 * @file chess_knight_problem.h
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief
 * @version 0.1
 * @date 2023-03-02
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#ifndef __CHEES_KNIGHT_PROBLEM_H__
#define __CHEES_KNIGHT_PROBLEM_H__

#include <set>
#include <utility>

namespace valhalla {
    namespace matrices {
        namespace chess_knight_problem {
            class Solution {
                bool is_valid_move(std::set<std::pair<int,int>> const &, std::pair<int,int> const &, int);
            public:
                int findShortestDistance(int, std::pair<int,int> const &, std::pair<int,int> const &);
            };
        }
    }
}

#endif
