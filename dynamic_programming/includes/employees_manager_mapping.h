/**
 * @file employees_manager_mapping.h
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief
 * @version 0.1
 * @date 2023-06-01
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#ifndef __EMPLOYEES_MANAGER_MAPPING_H__
#define __EMPLOYEES_MANAGER_MAPPING_H__

#include <unordered_set>
#include <unordered_map>

namespace valhalla {
    namespace dynamic_programming {
        namespace employees_manager_mapping {
            class Solution {
            public:
                std::unordered_map<char, std::unordered_set<char>> findMapping(std::unordered_map<char, char> &);
            };
        }
    }
}

#endif
