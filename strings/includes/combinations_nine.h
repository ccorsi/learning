/**
 * @file combinations_nine.h
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief
 * @version 0.1
 * @date 2023-03-06
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#ifndef __COMBINATIONS_NINE_H__
#define __COMBINATIONS_NINE_H__

#include <unordered_set>
#include <vector>
#include <string>

namespace valhalla {
    namespace strings {
        namespace combinations_nine {
            class Solution {
                void findCombination(std::unordered_set<std::string> &, std::vector<std::vector<std::string>> const &,
	                                 std::string &, int);
            public:
                std::unordered_set<std::string> findCombinations(std::vector<std::vector<std::string>> const &);
            };
        }
    }
}

#endif
