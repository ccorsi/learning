/**
 * @file collect_coins.h
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief
 * @version 0.1
 * @date 2023-06-20
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */
#ifndef __COLLECT_COINS_H__
#define __COLLECT_COINS_H__

#include <vector>

namespace valhalla {
    namespace matrices {
        namespace collect_coins {
            class Solution {
            public:
                int getMaxCoins(std::vector<std::vector<int>> const &);
            };
        }
    }
}

#endif
