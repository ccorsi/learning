/**
 * @file minimum_range.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This is a solution to the problem https://www.techiedelight.com/?problem=MinimumRange
 * @version 0.1
 * @date 2023-04-01
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */


#include "minimum_range.h"

namespace valhalla {
    namespace arrays {
        namespace minimum_range {
            /*

            Given three sorted arrays of variable length, efficiently compute
            the minimum range with at least one element from each array.

            Input : [[3, 6, 8, 10, 15], [1, 5, 12], [4, 8, 15, 16]]
            Output: (3, 5)

            Input : [[2, 3, 4, 8, 10, 15], [1, 5, 12], [7, 8, 15, 16]]
            Output: (4, 7)

            Input : [[1], [1, 2], [0, 1]]
            Output: (1, 1)

            If minimum range doesn't exist, the solution should return the
            pair (-1, -1).

            Input : [[], [], []]
            Output: (-1, -1)

            */

            std::pair<int,int> Solution::findMinRange(std::vector<int> const & X, std::vector<int> const & Y, std::vector<int> const & Z) {
                std::pair<int,int> minRange(-2, -2);


                return minRange;
            } // findMinRange
        }
    }
}
