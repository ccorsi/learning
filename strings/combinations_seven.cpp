/**
 * @file combinations_seven.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains a solution to the problem https://www.techiedelight.com/?problem=CombinationsVII
 * @version 0.1
 * @date 2023-03-03
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include "combinations_seven.h"

/*

Given n lists of characters and a number whose digits lie between 1 and n, print all possible combinations
by replacing its digits with the characters of the corresponding list. If any digit of the number gets
repeated, it should be replaced by the same character considered in its previous occurrence.

Input:

lists =
[
	['A', 'B', 'C', 'D'],
	['E', 'F', 'G', 'H', 'I', 'J', 'K'],
	['L', 'M', 'N', 'O', 'P', 'Q'],
	['R', 'S', 'T'],
	['U', 'V', 'W', 'X', 'Y', 'Z']
]

keys = [0, 2, 0]

Output: {"ALA", "AMA", "ANA", "AOA", "APA", "AQA", "BLB", "BMB", "BNB", "BOB", "BPB", "BQB", "CLC", "CMC",
    "CNC", "COC", "CPC", "CQC", "DLD", "DMD", "DND", "DOD", "DPD", "DQD"}

*/

std::unordered_set<std::string> valhalla::strings::combinations_seven::Solution::findCombinations(std::vector<std::vector<char>> const & lists, std::vector<int> const & keys) {
    std::unordered_set<std::string> combinations;

	if ( ! keys.empty() ) {
		const int key = keys[0];
		for (char letter : lists[key]) {
			std::map<int,char> seen;
			std::string current;
			current+=letter;
			seen[key] = letter;
			findCombination(lists, keys, combinations, current, 1, seen);
		} // for
	} // if

    return combinations;
}

void valhalla::strings::combinations_seven::Solution::findCombination(std::vector<std::vector<char>> const & lists, std::vector<int> const & keys,
	std::unordered_set<std::string> & combinations, std::string const & current, int next_idx, std::map<int,char> & seen) {

	if (next_idx == keys.size()) {
		combinations.insert(current);
		return;
	}

	const int key = keys[next_idx];

	if (seen.find(key) == seen.end()) {
		for (char letter : lists[key]) {
			std::string next = current;
			next += letter;
			std::map<int,char> seen_sofar = seen;
			seen_sofar[key] = letter;
			findCombination(lists, keys, combinations, next, next_idx + 1, seen_sofar);
		} // for
	} else {
		std::string next = current;
		next += seen[key];
		findCombination(lists, keys, combinations, next, next_idx + 1, seen);
	} // else
}
