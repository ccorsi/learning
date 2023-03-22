/**
 * @file buy_and_sell_stock_three.h
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief
 * @version 0.1
 * @date 2023-03-21
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#ifndef __BUY_AND_SELL_STOCK_THREE_H__
#define __BUY_AND_SELL_STOCK_THREE_H__

#include <vector>

namespace valhalla {
    namespace arrays {
        namespace buy_and_sell_stock_three {
            class Solution {
                void checkMaximumProfit(std::vector<int> const &, const int,
                                        std::vector<int> const &, const int,
                                        const int, int, int, int &);
            public:
                int findMaximumProfit(std::vector<int> const &, std::vector<int> const &);
            };
        }
    }
}

#endif
