/**
 * @file power_set_two.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains a solution to the problem https://www.techiedelight.com/?problem=PowerSetII
 * @version 0.1
 * @date 2025-04-03
 *
 * @copyright Copyright (c) 2025 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include "power_set_two.h"

#include <algorithm>
#include <set>

namespace valhalla {

namespace backtracking {

namespace power_set_two {

/*

Given a set S, return all distinct subsets of it, i.e., find distinct power set
of set S. A power set of any set S is the set of all subsets of S, including the
empty set and S itself.

Input : S[] = [1, 2, 3]
Output: [[1, 2, 3], [2, 3], [1, 3], [3], [1, 2], [2], [1], []]

Input : S[] = [1, 2, 1]
Output: [[1, 1, 2], [1, 2], [2], [1, 1], [1], []]

Input : S[] = [1, 1]
Output: [[1, 1], [1], []]

Input : S[] = []
Output: [[]]

Note: The solution can return elements of a subsets in any order.

*/

void process_next_entry(std::set<std::vector<int>> & seen,
                        std::vector<std::vector<int>> & power_set,
                        std::vector<int> & vec, std::vector<int> & S,
                        int start, int count) {
    if (count == 0) {
        if (seen.insert(vec).second) {
            power_set.push_back(vec);
        } // if (seen.insert(vec).second)
        return;
    } // if (count < 1)

    // Insure that we still have entries that need to be added to the passed vec
    if (count-- > 0) {
        const int last = static_cast<int>(S.size()) - count;
        // Make sure that we frivolously add entries to the vec when we don't have enough entries
        while (start < last) {
            vec.push_back(S[start]);
            process_next_entry(seen, power_set, vec, S, ++start, count);
            vec.pop_back();
        } // while (start < last)
    } // if (count-- > 0)

} // process_next_entry

std::vector<std::vector<int>> recursive_attempt_one(std::vector<int> & S) {
    std::vector<std::vector<int>> power_set = {{}};
    // sort the incoming vector for better processing
    std::sort(S.begin(), S.end());
    // create a set that contains the currently processed or processing vectors to avoid duplicate entries.
    std::set<std::vector<int>> seen = {{}};

    for (int count = static_cast<int>(S.size()) ; count-- > 0 ; ) {
        const int end = static_cast<int>(S.size()) - count;
        for (int start = 0 ; start < end ; ) {
            std::vector<int> vec = { S[start++] };
            process_next_entry(seen, power_set, vec, S, start, count);
        } // for (int start = 0 ; start < end ; )
    } // for (int count = static_cast<int>(S.size()) ; count-- > 0 ; )

    return power_set;
} // recursive_attempt_one

std::vector<std::vector<int>> Solution::findPowerSet(std::vector<int> & S) {
    return recursive_attempt_one(S);
} // findPowerSet

} // namespace power_set_two

} // namespace backtracking

} // namespace valhalla
