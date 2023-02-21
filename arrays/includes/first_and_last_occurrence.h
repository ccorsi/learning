/**
 * @file first_and_last_occurrence.h
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief
 * @version 0.1
 * @date 2023-02-20
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#ifndef __FIRST_AND_LAST_OCCURRENCE_H__
#define __FIRST_AND_LAST_OCCURRENCE_H__

#include <vector>
#include <map>

namespace valhalla {
    namespace arrays {
        namespace first_and_last_occurrence {
            class Solution {
            public:
                std::pair<int,int> findPair(std::vector<int> const &, int);
            };
        }
    }
}

#endif
