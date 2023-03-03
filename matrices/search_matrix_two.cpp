/**
 * @file search_matrix_two.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains a solution to the problem https://www.techiedelight.com/?problem=SearchMatrixII
 * @version 0.1
 * @date 2023-03-03
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include <queue>

#include "search_matrix_two.h"

/*

Given an `M × N` matrix of characters, find all occurrences of a given string in it and return a set of
its coordinates. You are allowed to search the string in all eight possible directions, i.e., North, West,
South, East, North-East, North-West, South-East, South-West. There should not be any cycles in the output
path.

Input:

[
	['D', 'E', 'M', 'X', 'B'],
	['A', 'O', 'E', 'P', 'E'],
	['D', 'D', 'C', 'O', 'D'],
	['E', 'B', 'E', 'D', 'S'],
	['C', 'P', 'Y', 'E', 'N']
]

word = "CODE"

Output:

{
	[(2, 2), (2, 3), (2, 4), (1, 4)],
	[(2, 2), (1, 1), (2, 1), (3, 2)],
	[(2, 2), (1, 1), (2, 1), (3, 0)],
	[(2, 2), (2, 3), (3, 3), (4, 3)],
	[(2, 2), (1, 1), (2, 1), (1, 2)],
	[(2, 2), (1, 1), (0, 0), (0, 1)],
	[(2, 2), (1, 1), (2, 0), (3, 0)],
	[(2, 2), (2, 3), (3, 3), (3, 2)]
}

*/

std::set<std::vector<std::pair<int,int>>> valhalla::matrices::search_matrix_two::Solution::searchMatrix(std::vector<std::vector<char>> const & mat, std::string word) {
    std::set<std::vector<std::pair<int,int>>> paths;

	if ( ! word.empty() && ! mat.empty() && ! mat[0].empty() ) {
		const char head = word[0];
		const std::vector<char>::size_type rows = mat.size(), cols = mat[0].size();
		std::vector<std::pair<int,int>> moves = {
			std::pair(-1,  0), std::pair(-1,  1), std::pair( 0,  1), std::pair( 1,  1),
			std::pair( 1,  0), std::pair( 1, -1), std::pair( 0, -1), std::pair(-1, -1),
		};

		for (std::vector<char>::size_type row = 0 ; row < rows ; row++) {
			for (std::vector<char>::size_type col = 0 ; col < cols ; col++) {
				if (mat[row][col] == head) {
					// int idx = 1;
					std::vector<std::pair<int,int>> path = { std::pair(row,col) };
					if (path.size() == word.length()) {
						paths.insert(path);
						continue;
					} // if
					std::queue<std::vector<std::pair<int,int>>> candidates;
					candidates.push(path);
					while ( ! candidates.empty() ) {
						std::vector<std::pair<int,int>> candidate = candidates.front(); candidates.pop();
						char chr = word[candidate.size()];
						std::pair<int,int> point = candidate.back();
						for (std::pair<int,int> move : moves) {
							std::pair<int,int> next(point);
							next.first += move.first;
							next.second += move.second;
							if (is_valid_move(mat, candidate, chr, next)) {
								std::vector<std::pair<int,int>> visited = candidate;
								visited.push_back(next);
								if (visited.size() == word.length()) {
									paths.insert(visited);
								} else {
									candidates.push(visited);
								} // else
							} // if
						} // for
					} // while
				} // if
			} // for
		} // for
	} // if

    return paths;
}

bool valhalla::matrices::search_matrix_two::Solution::is_valid_move(std::vector<std::vector<char>> const & mat,
																	std::vector<std::pair<int,int>> const & visited, char chr,
																	std::pair<int,int> const & next) {
	return next.first > -1 && static_cast<std::vector<char>::size_type>(next.first) < mat.size() && next.second > -1
	&& static_cast<std::vector<char>::size_type>(next.second) < mat[0].size() && mat[next.first][next.second] == chr
	&& ! contains(visited, next);
}

bool valhalla::matrices::search_matrix_two::Solution::contains(std::vector<std::pair<int,int>> const & visited, std::pair<int,int> const & next) {
	for (std::pair<int,int> point : visited)
		if (point.first == next.first && point.second == next.second)
			return true;

	return false;
}
