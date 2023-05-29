/**
 * @file rod_cutting_two.h
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief
 * @version 0.1
 * @date 2023-05-21
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#ifndef __ROD_CUTTING_TWO_H__
#define __ROD_CUTTING_TWO_H__

namespace valhalla {
    namespace dynamic_programming {
        namespace rod_cutting_two {
            class Solution {
                void findProfit(const int, const int, const int, const long, long &);
            public:
                long findMaxProfit(int);
            };
        }
    }
}

#endif
