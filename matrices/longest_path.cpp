/**
 * @file longest_path.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This is a solution to the problem https://www.techiedelight.com/?problem=LongestPath
 * @version 0.1
 * @date 2023-03-02
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include <iostream>
#include <queue>
#include <set>
#include <cassert>

#include "longest_path.h"

/*

Given a rectangular path in the form of a binary matrix, find the length of the longest possible
route from source to destination by moving to only non-zero adjacent positions, i.e., A route
can be formed from positions having their value as 1. Note there should not be any cycles in the
output path.

Input:

matrix = [
	[1, 0, 1, 1, 1, 1, 0, 1, 1, 1],
	[1, 0, 1, 0, 1, 1, 1, 0, 1, 1],
	[1, 1, 1, 0, 1, 1, 0, 1, 0, 1],
	[0, 0, 0, 0, 1, 0, 0, 1, 0, 0],
	[1, 0, 0, 0, 1, 1, 1, 1, 1, 1],
	[1, 1, 1, 1, 1, 1, 1, 1, 1, 0],
	[1, 0, 0, 0, 1, 0, 0, 1, 0, 1],
	[1, 0, 1, 1, 1, 1, 0, 0, 1, 1],
	[1, 1, 0, 0, 1, 0, 0, 0, 0, 1],
	[1, 0, 1, 1, 1, 1, 0, 1, 0, 0]
]
src  = (0, 0)
dest = (5, 7)

Output: 22

Explanation: The longest path is:

(0, 0) —> (1, 0) —> (2, 0) —> (2, 1) —> (2, 2) —> (1, 2) —> (0, 2) —> (0, 3) —> (0, 4) —> (1, 4) —>
  (1, 5) —> (2, 5) —> (2, 4) —> (3, 4) —> (4, 4) —> (5, 4) —> (5, 5) —> (5, 6) —> (4, 6) —>
  (4, 7) —> (4, 8) —> (5, 8) —> (5, 7)

Note: The solution should return 0 if no path is possible.

*/

int valhalla::matrices::longest_path::Solution::findLongestPathLen(std::vector<std::vector<int>> const & mat,
                                                                   std::pair<int,int> const & src,
                                                                   std::pair<int,int> const & dest) {
    /*
        NOTE: This solution is kind of slow and I wonder if there is another solution that is quicker
              than this implementation.
    */
    if (src == dest || mat.empty() || mat[0].empty() || mat[src.first][src.second] == 0) {
        return 0;
    } // if

    /*
        Data Structure requirements:

        current point, points visited, path length
    */
    std::queue<std::pair<std::set<std::pair<int,int>>,std::pair<std::pair<int,int>,int>>> points;

    points.push(std::pair(std::pair(std::set<std::pair<int,int>>(), std::pair(src,0))));

    std::vector<std::pair<int,int>> moves = {
        std::pair(0, 1), std::pair(0, -1), std::pair(1, 0), std::pair(-1, 0)
    };

    int longest = 0;

    while ( ! points.empty() ) {
        std::pair<std::set<std::pair<int,int>>,std::pair<std::pair<int,int>,int>> point = points.front(); points.pop();
        std::set<std::pair<int,int>> visited(point.first);

        if (visited.find(point.second.first) == visited.end()) {
            visited.insert(point.second.first);

            for (std::pair<int,int> move : moves) {
                std::pair<int,int> next(point.second.first);
                next.first += move.first;
                next.second += move.second;

                if (visited.find(next) == visited.end() && is_valid(mat, next)) {
                    assert(mat[next.first][next.second] == 1);
                    if (next == dest) {
                        if (longest < point.second.second + 1)
                            longest = point.second.second + 1;
                    } else {
                        points.push(std::pair(visited, std::pair(next, point.second.second + 1)));
                    } // else
                } // if
            } // for
        } // if
    } // while

    return longest;
}

bool valhalla::matrices::longest_path::Solution::is_valid(std::vector<std::vector<int>> const & mat, std::pair<int,int> const & point) {
    return (point.first > -1 && static_cast<std::vector<int>::size_type>(point.first) < mat.size() && point.second > -1
     && static_cast<std::vector<int>::size_type>(point.second) < mat[0].size() && mat[point.first][point.second] == 1);
}
