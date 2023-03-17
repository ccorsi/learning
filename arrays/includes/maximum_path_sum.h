/**
 * @file maximum_path_sum.h
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief
 * @version 0.1
 * @date 2023-03-15
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#ifndef __MAXIMUM_PATH_SUM_H__
#define __MAXIMUM_PATH_SUM_H__

#include <vector>

namespace valhalla {
    namespace arrays {
        namespace maximum_path_sum {
            class Solution {
                void checkPath(std::vector<int> const &, std::vector<int> const &, int, int, int, int &);
            public:
                int findMaxPathSum(std::vector<int> const &, std::vector<int> const &);
            };
        }
    }
}

#endif
