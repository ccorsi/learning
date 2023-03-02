/**
 * @file knight_tour_problem.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains a solution to the problem https://www.techiedelight.com/?problem=KnightTourProblem
 * @version 0.1
 * @date 2023-03-01
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include <queue>

#include "knight_tour_problem.h"

/*

Given a chessboard, return all sequences of moves of a knight on a chessboard such that the knight visits
every square only once. The solution should start the tour from the top-leftmost of the board, mark it as
1, and use the next numbers to represent the knight's consecutive moves.

Input: N = 5

Output:

{
	[[1, 18, 7, 12, 25], [8, 13, 2, 19, 6], [3, 20, 17, 24, 11], [14, 9, 22, 5, 16], [21, 4, 15, 10, 23]],
	[[1, 10, 21, 16, 7], [20, 15, 8, 11, 22], [9, 2, 23, 6, 17], [14, 19, 4, 25, 12], [3, 24, 13, 18, 5]],
	[[1, 18, 13, 8, 3], [12, 7, 2, 21, 14], [17, 22, 19, 4, 9], [6, 11, 24, 15, 20], [23, 16, 5, 10, 25]],
	[[1, 18, 13, 8, 21], [12, 7, 20, 3, 14], [19, 2, 17, 22, 9], [6, 11, 24, 15, 4], [25, 16, 5, 10, 23]]

	...and 300 more tours.
}

*/

std::set<std::vector<std::vector<int>>> valhalla::matrices::knight_tour_problem::Solution::_knightTour(int n) {
    /*
        NOTE: The following solution does find the required combinations but it is quite slow and I am not sure
            if it is actually *fast* compared to other solutions that have been implemented.  There is a need
            to look at the other solutions and compare them to this one.
    */
    std::set<std::vector<std::vector<int>>> solutions;

    if (n > 0) {
        std::vector<std::pair<int,int>> moves = {
            std::pair( 2,  1), // move right down
            std::pair( 2, -1), // move right up
            std::pair( 1,  2), // move down right
            std::pair(-1,  2), // move down left
            std::pair(-2,  1), // move left down
            std::pair(-2, -1), // move left up
            std::pair( 1, -2), // move up right
            std::pair(-1, -2), // move up left
        };
        const int total = n * n;
        std::queue<std::pair<std::vector<std::vector<int>>,std::pair<int,int>>> queue;
        std::vector<std::vector<int>> mat(n, std::vector(n, 0));
        mat[0][0] = 1;
        if (mat[0][0] != n) {
            queue.push(std::pair(mat, std::pair(0,0)));
        } else {
            solutions.insert(mat);
        } // else

        while ( ! queue.empty() ) {
            std::pair<std::vector<std::vector<int>>,std::pair<int,int>> current = queue.front();
            queue.pop();

            for (std::pair<int,int> move : moves) {
                std::pair<int,int> point(current.second);

                point.first  += move.first;
                point.second += move.second;

                if (is_valid_move(current.first, point, n)) {
                    std::vector<std::vector<int>> solution(current.first);
                    solution[point.first][point.second] = solution[current.second.first][current.second.second] + 1;
                    if (solution[point.first][point.second] == total) {
                        solutions.insert(solution);
                    } else {
                        queue.push(std::pair(solution, point));
                    } // else
                } // if
            } // for
        } // while
    } // if

    return solutions;
}

bool valhalla::matrices::knight_tour_problem::Solution::is_valid_move(std::vector<std::vector<int>> const & mat, std::pair<int,int> const & move, int n) {
    return ! (move.first < 0 || move.first >= n || move.second < 0 || move.second >= n || mat[move.first][move.second] != 0);
}
