/**
 * @file longest_common_prefix.h
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief
 * @version 0.1
 * @date 2023-02-22
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#ifndef __LONGEST_COMMON_PREFIX_H__
#define __LONGEST_COMMON_PREFIX_H__

#include <vector>
#include <string>

namespace valhalla {
    namespace strings {
        namespace longest_common_prefix {
            class Solution {
            public:
                std::string findLCP(std::vector<std::string> const &);
            };
        }
    }
}

#endif
