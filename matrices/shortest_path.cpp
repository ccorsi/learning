/**
 * @file shortest_path.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This is a solution to the problem https://www.techiedelight.com/?problem=ShortestPath
 * @version 0.1
 * @date 2023-03-02
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include <queue>
#include <set>

#include "shortest_path.h"

/*

Given a maze in the form of a binary rectangular matrix, find the length of the shortest
path from a given source to a given destination. The path can only be constructed out of
cells having value 1, and at any moment, you can only move one step in one of the four
directions (Top, Left, Down, Right).

Input:

matrix = [
	[1, 1, 1, 1, 1, 0, 0, 1, 1, 1],
	[0, 0, 1, 0, 1, 1, 0, 1, 0, 1],
	[0, 0, 1, 0, 1, 1, 1, 0, 0, 1],
	[1, 0, 1, 1, 1, 0, 1, 1, 0, 1],
	[0, 0, 0, 1, 0, 0, 0, 1, 0, 1],
	[1, 0, 1, 1, 1, 0, 0, 1, 1, 0],
	[0, 0, 0, 0, 1, 0, 0, 1, 0, 1],
	[0, 1, 1, 1, 1, 1, 1, 1, 0, 0],
	[1, 1, 1, 1, 1, 0, 0, 1, 1, 1],
	[0, 0, 1, 0, 0, 1, 1, 0, 0, 1]
]
src  = (0, 0)
dest = (5, 7)

Output: 12

Explanation: The shortest path from (0, 0) to (5, 7) has length 12. The shortest path is
marked below with x.

[
	[x, x, x, x, x, 0, 0, 1, 1, 1],
	[0, 0, 1, 0, x, 1, 0, 1, 0, 1],
	[0, 0, 1, 0, x, x, x, 0, 0, 1],
	[1, 0, 1, 1, 1, 0, x, x, 0, 1],
	[0, 0, 0, 1, 0, 0, 0, x, 0, 1],
	[1, 0, 1, 1, 1, 0, 0, x, 1, 0],
	[0, 0, 0, 0, 1, 0, 0, 1, 0, 1],
	[0, 1, 1, 1, 1, 1, 1, 1, 0, 0],
	[1, 1, 1, 1, 1, 0, 0, 1, 1, 1],
	[0, 0, 1, 0, 0, 1, 1, 0, 0, 1]
]

Note: The solution should return -1 if no path is possible.

*/

int valhalla::matrices::shortest_path::Solution::findShortestPath(std::vector<std::vector<int>> const & mat,
                                                                  std::pair<int,int> const & src,
                                                                  std::pair<int,int> const & dest) {
    if ( ! mat.empty() && ! mat[0].empty() && mat[src.first][src.second] == 1) {
        /*
            Data Structure wiil contain the last point in the path and the length to
            the last point from the source.
        */
        std::queue<std::pair<std::pair<int,int>, int>> points;

        std::set<std::pair<int,int>> visited;

        points.push(std::pair(src, 0));

        std::vector<std::pair<int,int>> moves = {
            std::pair(1,0), std::pair(-1,0), std::pair(0,1), std::pair(0,-1)
        };

        while ( ! points.empty() ) {
            std::pair<std::pair<int,int>, int> point = points.front(); points.pop();

            // check if the enqueued point was already visited
            if (visited.find(point.first) == visited.end()) {
                // add the non-visited point to the visited container
                visited.insert(point.first);
                // check surrounding moves
                for (std::pair<int,int> move : moves) {
                    std::pair<int,int> next(point.first);
                    next.first += move.first;
                    next.second += move.second;

                    if (is_valid_move(visited, mat, next)) {
                        if (next == dest) {
                            return point.second + 1;
                        } else {
                            points.push(std::pair(next, point.second + 1));
                        }
                    } // if
                } // for
            } // if
        } // while
    } // if

    return -1;
}

bool valhalla::matrices::shortest_path::Solution::is_valid_move(std::set<std::pair<int,int>> const & visited,
                                                                std::vector<std::vector<int>> const & mat,
                                                                std::pair<int,int> const & point) {
    return point.first > -1 && static_cast<std::vector<int>::size_type>(point.second) < mat.size() && point.second > -1
        && static_cast<std::vector<int>::size_type>(point.second) < mat[0].size() && visited.find(point) == visited.end();
}
