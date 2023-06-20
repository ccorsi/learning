/**
 * @file boggle_search.h
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief
 * @version 0.1
 * @date 2023-06-20
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */
#ifndef __BOGGLE_SEARCH_H__
#define __BOGGLE_SEARCH_H__

#include <string>
#include <unordered_set>
#include <vector>

namespace valhalla {
    namespace matrices {
        namespace boggle_search {
            class Solution {
            public:
                std::unordered_set<std::string> searchBoggle(std::vector<std::vector<char>> const &, std::unordered_set<std::string> const &);
            };
        }
    }
}

#endif
