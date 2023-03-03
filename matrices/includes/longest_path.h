/**
 * @file longest_path.h
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief
 * @version 0.1
 * @date 2023-03-02
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#ifndef __LONGEST_PATH_H__
#define __LONGEST_PATH_H__

#include <vector>
#include <utility>

namespace valhalla {
    namespace matrices {
        namespace longest_path {
            class Solution {
                bool is_valid(std::vector<std::vector<int>> const &, std::pair<int,int> const &);
            public:
                int findLongestPathLen(std::vector<std::vector<int>> const &, std::pair<int,int> const &, std::pair<int,int> const &);
            };
        }
    }
}

#endif
