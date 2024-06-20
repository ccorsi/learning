/**
 * @file tiles_problem.h
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief
 * @version 0.1
 * @date 2023-06-19
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */
#ifndef __TILES_PROBLEM_H__
#define __TILES_PROBLEM_H__

namespace valhalla {
    namespace matrices {
        namespace tiles_problem {
            class Solution {
                long combination_one(int, int);
                long combination_two(int, int);
                long combination_three(int, int);
                long combination(int, int);
            public:
                long findTotalWays(int);
            };
        }
    }
}

#endif
