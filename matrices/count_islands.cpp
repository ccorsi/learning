/**
 * @file count_islands.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains a solution to the problem https://www.techiedelight.com/?problem=CountIslands
 * @version 0.1
 * @date 2023-06-21
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include "count_islands.h"

namespace valhalla {
    namespace matrices {
        namespace count_islands {
            /*

            Given a binary matrix where 0 represents water and 1 represents land,
            and connected ones form an island, count the total islands.

            Input:

            [
                [1, 0, 1, 0, 0, 0, 1, 1, 1, 1],
                [0, 0, 1, 0, 1, 0, 1, 0, 0, 0],
                [1, 1, 1, 1, 0, 0, 1, 0, 0, 0],
                [1, 0, 0, 1, 0, 1, 0, 0, 0, 0],
                [1, 1, 1, 1, 0, 0, 0, 1, 1, 1],
                [0, 1, 0, 1, 0, 0, 1, 1, 1, 1],
                [0, 0, 0, 0, 0, 1, 1, 1, 0, 0],
                [0, 0, 0, 1, 0, 0, 1, 1, 1, 0],
                [1, 0, 1, 0, 1, 0, 0, 1, 0, 0],
                [1, 1, 1, 1, 0, 0, 0, 1, 1, 1]
            ]

            Output: 5

            Explanation: There are a total of 5 islands present in the above matrix.
            They are marked by the numbers 1 to 5 in the matrix below.

            1  0  2  0  0  0  3  3  3  3
            0  0  2  0  2  0  3  0  0  0
            2  2  2  2  0  0  3  0  0  0
            2  0  0  2  0  3  0  0  0  0
            2  2  2  2  0  0  0  5  5  5
            0  2  0  2  0  0  5  5  5  5
            0  0  0  0  0  5  5  5  0  0
            0  0  0  4  0  0  5  5  5  0
            4  0  4  0  4  0  0  5  0  0
            4  4  4  4  0  0  0  5  5  5

            */

            int Solution::countIslands(std::vector<std::vector<int>> const & mat) {
                int islands = -1;



                return islands;
            } // countIslands
        }
    }
}
