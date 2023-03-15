/**
 * @file maximum_product_subarray.h
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief
 * @version 0.1
 * @date 2023-03-14
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#ifndef __MAXIMUM_PRODUCT_SUBARRAY_H__
#define __MAXIMUM_PRODUCT_SUBARRAY_H__

#include <vector>

namespace valhalla {
    namespace arrays {
        namespace maximum_product_subarray {
            class Solution {
                void checkMaxProduct(std::vector<int> const &, int &, int, int);
            public:
                int findMaxProduct(std::vector<int> const &);
            };
        }
    }
}

#endif
