/**
 * @file chess_knight_problem.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This is a solution to the problem https://www.techiedelight.com/?problem=ChessKnightProblem
 * @version 0.1
 * @date 2023-03-02
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include <set>
#include <queue>
#include <vector>

#include "chess_knight_problem.h"

/*

Given a chessboard, find the shortest distance (minimum number of steps) taken by a knight to reach a given
destination from a given source.

Input:

N = 8 			(8 x 8 matrix)
src  = (0, 7)	(Source coordinates)
dest = (7, 0)	(Destination coordinates)

Output: 6

Explanation: The minimum number of steps required is 6. The knight's movement is illustrated in the following figure:

https://techiedelight.com/practice/images/Chess-Board.png


The solution should return -1 if the path is not possible.

*/

int valhalla::matrices::chess_knight_problem::Solution::findShortestDistance(int N, std::pair<int,int> const & src, std::pair<int,int> const & dest) {
    if (N > 0) {
        if (src == dest) {
            return 0;
        } // if

        std::vector<std::pair<int,int>> moves = {
            std::pair( 2,  1), // move down right
            std::pair( 2, -1), // move down left
            std::pair( 1,  2), // move down right
            std::pair(-1,  2), // move up right
            std::pair(-2,  1), // move left down
            std::pair(-2, -1), // move left up
            std::pair( 1, -2), // move down left
            std::pair(-1, -2), // move up left
        };
        std::set<std::pair<int,int>> visited;
        std::queue<std::pair<std::pair<int,int>,int>> points;

        points.push(std::pair(std::pair(src),0));

        while ( ! points.empty()) {
            std::pair<std::pair<int,int>,int> next = points.front(); points.pop();
            if (visited.find(next.first) == visited.end()) {
                visited.insert(next.first); // add the next point to the visited

                for (std::pair<int,int> move : moves) {
                    std::pair<int,int> point = next.first;
                    point.first += move.first;
                    point.second += move.second;
                    if (is_valid_move(visited, point, N)) {
                        if (point == dest) {
                            return next.second + 1;
                        } // if
                        points.push(std::pair(point, next.second + 1));
                    } // if
                }  // for
            } // if
        } // while
    } // if

    return -1;
}

bool valhalla::matrices::chess_knight_problem::Solution::is_valid_move(std::set<std::pair<int,int>> const & visited, std::pair<int,int> const & move, int N) {
    return (move.first > -1 && move.first < N && move.second > -1 && move.second < N && visited.find(move) == visited.end());
}
