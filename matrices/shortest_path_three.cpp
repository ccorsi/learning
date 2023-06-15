/**
 * @file shortest_path_three.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains a solution to the problem https://www.techiedelight.com/?problem=ShortestPathIII
 * @version 0.1
 * @date 2023-06-15
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include "shortest_path_three.h"

namespace valhalla {
    namespace matrices {
        namespace shortest_path_three {
            /*

            Given a maze in the form of a rectangular matrix, filled with either 'O', 'X', or 'M',
            where 'O' represents an open cell, 'X' represents a blocked cell, and 'M' represents
            landmines in the maze.

            The task is to find the shortest distance of every open cell in the maze from its
            nearest mine. You are only allowed to travel in either of the four directions, and
            diagonal moves are not allowed. The cells with landmines have a distance of 0, and
            blocked/unreachable cells have a distance of -1.

            Input:

            mat = [
                ['O', 'M', 'O', 'O', 'X'],
                ['O', 'X', 'X', 'O', 'M'],
                ['O', 'O', 'O', 'O', 'O'],
                ['O', 'X', 'X', 'X', 'O'],
                ['O', 'O', 'M', 'O', 'O'],
                ['O', 'X', 'X', 'M', 'O']
            ]

            Here, O (Open cell), X (Blocked Cell), and M (Landmine).

            Output:

            [
                [1,  0,  1,  2, -1],
                [2, -1, -1,  1,  0],
                [3,  4,  3,  2,  1],
                [3, -1, -1, -1,  2],
                [2,  1,  0,  1,  2],
                [3, -1, -1,  0,  1]
            ]

            */

            std::vector<std::vector<int>> Solution::updateShortestDistance(std::vector<std::vector<char>> const & mat) {
                std::vector<std::vector<int>> updated;



                return updated;
            } // updateShortestDistance
        }
    }
}
