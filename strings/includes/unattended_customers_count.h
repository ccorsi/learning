/**
 * @file unattended_customers_count.h
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief
 * @version 0.1
 * @date 2023-05-19
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#ifndef __UNATTENDED_CUSTOMERS_COUNT_H__
#define __UNATTENDED_CUSTOMERS_COUNT_H__

#include <string>

namespace valhalla {
    namespace strings {
        namespace unattended_customers_count {
            class Solution {
            public:
                int findUnattendedCustomers(std::string sequence, int capacity);
            };
        }
    }
}

#endif
