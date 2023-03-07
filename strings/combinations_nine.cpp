/**
 * @file combinations_nine.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains a solution to the problem https://www.techiedelight.com/?problem=CombinationsIX
 * @version 0.1
 * @date 2023-03-06
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include "combinations_nine.h"

/*

Given a lists of words, print all combinations of phrases that can be formed by picking one word from each list.

Input:

lists =
[
	["John", "Emma"],
	["Plays", "Hates", "Watches"],
	["Cricket", "Soccer", "Chess"]
]

Output:

{
	"John Plays Cricket",
	"John Plays Soccer",
	"John Plays Chess",
	"John Hates Cricket",
	"John Hates Soccer",
	"John Hates Chess",
	"John Watches Cricket",
	"John Watches Soccer",
	"John Watches Chess",
	"Emma Plays Cricket",
	"Emma Plays Soccer",
	"Emma Plays Chess",
	"Emma Hates Cricket",
	"Emma Hates Soccer",
	"Emma Hates Chess",
	"Emma Watches Cricket",
	"Emma Watches Soccer",
	"Emma Watches Chess"
}

*/

std::unordered_set<std::string> valhalla::strings::combinations_nine::Solution::findCombinations(std::vector<std::vector<std::string>> const & lists) {
    std::unordered_set<std::string> combinations;

	if ( ! lists.empty() ) {
		for (std::string word : lists[0]) {
			findCombination(combinations, lists, word, 1);
		} // for
	} // if

    return combinations;
}

void valhalla::strings::combinations_nine::Solution::findCombination(std::unordered_set<std::string> & combinations, std::vector<std::vector<std::string>> const & lists,
	std::string & current, int next_idx) {

	if (next_idx == lists.size()) {
		combinations.insert(current);
		return;
	} // if

	for (std::string word : lists[next_idx]) {
		std::string next = current + " " + word;
		findCombination(combinations, lists, next, next_idx + 1);
	} // for
}
