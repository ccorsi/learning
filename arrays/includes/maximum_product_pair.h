/**
 * @file maximum_product_pair.h
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief 
 * @version 0.1
 * @date 2023-01-01
 * 
 * @copyright Copyright (c) 2023 Claudio Corsi
 * 
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */
#ifndef __MAXIMUM_PRODUCT_PAIR_H__
#define __MAXIMUM_PRODUCT_PAIR_H__

#include <vector>
#include <map>

namespace valhalla {
    namespace arrays {
        namespace maximum_product_pair {
            class Solution {
            public:
                std::pair<int,int> find(std::vector<int>&);
            };
        }
    }
}

#endif