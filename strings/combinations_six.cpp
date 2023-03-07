/**
 * @file combinations_six.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains a solution to the problem https://www.techiedelight.com/?problem=CombinationsVI
 * @version 0.1
 * @date 2023-03-03
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include "combinations_six.h"

/*

Given a sequence of numbers between 2 and 9, print all possible combinations of words formed from the
mobile keypad which has english alphabets associated with each key.

keypad = {
	2: ['A', 'B', 'C'],
	3: ['D', 'E', 'F'],
	4: ['G', 'H', 'I'],
	5: ['J', 'K', 'L'],
	6: ['M', 'N', 'O'],
	7: ['P', 'Q', 'R', 'S'],
	8: ['T', 'U', 'V'],
	9: ['W', 'X', 'Y', 'Z']
}

Input : [2, 3, 4]

Output: {"CEG", "AEH", "CDH", "CFI", "CEH", "BEI", "AFH", "BFG", "BDI", "ADH", "AEG", "AEI", "BEH", "BFH",
    "BDH", "CEI", "AFG", "BFI", "ADG", "CDG", "BDG", "CDI", "BEG", "AFI", "CFG", "CFH", "ADI"}

*/

std::unordered_set<std::string> valhalla::strings::combinations_six::Solution::findCombinations(std::unordered_map<int,std::vector<char>> & keypad,
    std::vector<int> & nums) {

    std::unordered_set<std::string> combinations;

	if ( ! nums.empty() ) {
		for (char letter : keypad[nums[0]]) {
			std::string current;
			current+=letter;
			findCombination(combinations, keypad, current, 1, nums);
		} // for
	} // if

    return combinations;
}

void valhalla::strings::combinations_six::Solution::findCombination(std::unordered_set<std::string> & combinations,
	std::unordered_map<int,std::vector<char>> & keypad, std::string const & current, const int next,
	std::vector<int> const & nums) {

	if (next == nums.size()) {
		combinations.insert(current);
		return;
	} //

	for (char letter : keypad[nums[next]]) {
		findCombination(combinations, keypad, current+letter, next + 1, nums);
	} // for
}
