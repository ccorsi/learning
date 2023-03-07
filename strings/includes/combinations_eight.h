/**
 * @file combinations_eight.h
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief
 * @version 0.1
 * @date 2023-03-03
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#ifndef __COMBINATIONS_EIGHT_H__
#define __COMBINATIONS_EIGHT_H__

#include <set>
#include <vector>
#include <string>

namespace valhalla {
    namespace strings {
        namespace combinations_eight {
            class Solution {
                void findCombination(std::set<std::vector<std::string>> &, std::vector<std::string> &, int, std::string const &);
            public:
                std::set<std::vector<std::string>> findCombinations(std::string);
            };
        }
    }
}

#endif
