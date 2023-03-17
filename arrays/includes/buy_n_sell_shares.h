/**
 * @file buy_n_sell_shares.h
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief
 * @version 0.1
 * @date 2023-03-16
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#ifndef __BUY_N_SELL_SHARES_H__
#define __BUY_N_SELL_SHARES_H__

#include <vector>

namespace valhalla {
    namespace arrays {
        namespace buy_n_sell_shares {
            class Solution {
                void findMinBuy(std::vector<int> const &, int, int, int &);
                void findMaxSell(std::vector<int> const &, int, int, int &);
            public:
                int findMaxProfit(std::vector<int> const &);
            };
        }
    }
}

#endif
