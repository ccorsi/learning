/**
 * @file zero_sum.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This is an implementation of the problem
 *        https://www.techiedelight.com/check-subarray-with-0-sum-exists-not/
 * @version 0.1
 * @date 2022-12-26
 * 
 * @copyright Copyright (c) 2022 Claudio Corsi
 * 
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include <vector>
#include <set>

using namespace std;

#include "zero_sum.h"

/**
 * @brief This will determine if the passed zero contains a zero sum sub-array.
 * 
 * @param values an array of integers to check for a zero sun sub-array
 * @return true if a zero sum sub-array was found
 * @return false if no zero sum sub-array was found
 */
bool valhalla::arrays::zero_sum::Solution::has_zero_sum(const vector<int> &values) {
    // store all entries in the passed vector to help determine if there is a zero sum array
    set<int> current;
    
    current.insert(0); // for the case that the first entry is a zero.

    int sum = 0;

    for(auto itr = values.begin() ; itr != values.end() ; itr++) {
        sum += *itr;

        // check if we already encountered this sum
        auto found = current.find(sum);

        if (found != current.end()) {
            return true;
        }

        current.insert(sum);
    }

    return false;
}