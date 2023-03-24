/**
 * @file group_elements.h
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief
 * @version 0.1
 * @date 2023-03-22
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#ifndef __GROUP_ELEMENTS_H__
#define __GROUP_ELEMENTS_H__

#include <vector>
#include <utility>

namespace valhalla {
    namespace arrays {
        namespace group_elements {
            class Solution {
                struct cmp {
                    bool operator()(const std::pair<int,std::pair<int,int>> & lhs, const std::pair<int,std::pair<int,int>> & rhs) const {
                        return lhs.first < rhs.first;
                    }
                };
            public:
                std::vector<int> sortArray(std::vector<int> const &);
            };
        }
    }
}

#endif
