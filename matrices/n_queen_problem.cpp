/**
 * @file n_queen_problem.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains a solution to the problem https://www.techiedelight.com/?problem=NQueenProblem
 * @version 0.1
 * @date 2023-03-01
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include <iostream>

#include "n_queen_problem.h"

/*

The N–queens puzzle is the problem of placing `N` chess queens on an `N × N` chessboard so that no two queens
threaten each other. Thus, the solution requires that no two queens share the same row, column, or diagonal.

The solution should return a Set of each possible solution to the N–Queens problem.

Input: N = 4
Output:
{
	[[0, 0, 1, 0], [1, 0, 0, 0], [0, 0, 0, 1], [0, 1, 0, 0]],
	[[0, 1, 0, 0], [0, 0, 0, 1], [1, 0, 0, 0], [0, 0, 1, 0]]
}

Here 1 represents the position of a queen in chessboard. Note that the solution exists for all natural numbers,
except for 2 and 3. The solution should return an empty set for N = 2 and N = 3.

Input: N = 2
Output: {}

*/

std::set<std::vector<std::vector<int>>> valhalla::matrices::n_queen_problem::Solution::solveNQueen(int n) {
    std::set<std::vector<std::vector<int>>> solutions;

    if (n == 1) {
        // TODO: figure out why the while loop doesn't produce the correct answer when n = 1
        std::vector<std::vector<int>> solution;
        solution.push_back(std::vector<int>(1,1));
        solutions.insert(solution);
        return solutions;
    } // if

    // if (n > 3) {
    std::set<std::vector<int>> queue;

    for (int row = 0 ; row < n ; row++) {
        std::vector<int> v;
        v.push_back(row);
        queue.insert(v);
    }

    while ( ! queue.empty() ) {
        std::vector<int> valid = *(queue.begin());
        queue.extract(valid); // get the next item on the queue

        // std::cout << "Processing vector: " << valid.size() << " queue size: " << queue.size() << " valid: ["; for (int value : valid) std::cout << " " << value; std::cout << " ]" << std::endl;
        for (int row = 0 ; row < n ; row++) {
            if (is_valid(valid, row)) {
                std::vector<int> solution(valid);
                solution.push_back(row);
                if (solution.size() == n) {
                    // std::cout << "Found a valid matrix: " << solution.size() << std::endl;
                    std::vector<std::vector<int>> mat;
                    for (int fits : solution) {
                        std::vector<int> values(n, 0);
                        values[fits] = 1;
                        mat.push_back(values);
                    } // for
                    // std::cout << "Added solution" << std::endl;
                    solutions.insert(mat);
                } else {
                    // std::cout << "Adding an incomplete solution size: " << solution.size() << " solution: ["; for (int value : solution) std::cout << " " << value; std::cout << " ]" << std::endl;
                    queue.insert(solution);
                } // else
            } // if
        } // for
    } // while

    return solutions;
}

bool valhalla::matrices::n_queen_problem::Solution::is_valid(std::vector<int> const & vec, int row) {
    if ( ! vec.empty() ) {
        int brow = row - 1, trow = row + 1;

        for (std::vector<int>::const_reverse_iterator itr = vec.rbegin() ; itr != vec.rend() ; itr++) {
            int spot = *itr;
            if (spot == brow || spot == row || spot == trow) {
                return false;
            }
            brow--; trow++;
        } // for
    } // if

    return true;
}
