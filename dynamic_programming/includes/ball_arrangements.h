/**
 * @file ball_arrangements.h
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief
 * @version 0.1
 * @date 2023-03-11
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#ifndef __BALL_ARRANGEMENTS_H__
#define __BALL_ARRANGEMENTS_H__

namespace valhalla {
    namespace dynamic_programming {
        namespace ball_arrangements {
            class Solution {
                void findNextMax(int, int, int, char, int &, char *, std::set<std::string> &);
                void findNextMin(int, int, int, char, int &, char *, std::set<std::string> &);
                void findNext(int, int, int, char, int &, char *, std::set<std::string> &);
            public:
                int totalWays(int, int, int);
            };
        }
    }
}

#endif
