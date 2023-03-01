/**
 * @file common_elements.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This is a solution of the problem https://www.techiedelight.com/?problem=CommonElements
 * @version 0.1
 * @date 2023-03-01
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include <map>
#include <set>

#include "common_elements.h"

/*

Given an `M × N` integer matrix, find the common elements present in all rows of the matrix.
The solution should traverse the matrix once and return the common elements.

Input:
[
	[7, 1, 3, 5, 3, 6],
	[2, 3, 6, 1, 1, 6],
	[6, 1, 7, 2, 1, 4],
	[6, 6, 7, 1, 3, 3],
	[5, 5, 6, 1, 5, 4],
	[3, 5, 6, 2, 7, 1],
	[4, 1, 4, 3, 6, 4],
	[4, 6, 1, 7, 4, 3]
]

Output: {1, 6}

*/

std::unordered_set<int> valhalla::matrices::common_elements::Solution::findCommonElements(std::vector<std::vector<int>> const & mat) {
    std::unordered_set<int> results;

    if ( ! mat.empty() && ! mat[0].empty()) {
        std::map<int,std::set<int>> counts;

        for ( std::map<int,std::set<int>>::size_type row = 0 ; row < mat.size() ; row++) {
            std::vector<int> values = mat[row];
            for (int value : values) {
                counts[value].insert(row);
            } // for
        } // for

        for (std::map<int,std::set<int>>::value_type value : counts) {
            if (value.second.size() == mat.size())
                results.insert(value.first);
        } // for
    } // if

    return results;
}
