/**
 * @file decode_array.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains a solution to the problem https://www.techiedelight.com/?problem=DecodeArray
 * @version 0.1
 * @date 2023-03-17
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include "decode_array.h"

/*

Given an integer array `X`, which is constructed by taking the sum of every distinct pair from another
array `Y`, decode `X` to get the original array back. If the original array is `Y[0], Y[1], … , Y[n-1]`,
then the input array `X` is:

[
  (Y[0] + Y[1]), (Y[0] + Y[2]), … (Y[0] + Y[n-1]),
  (Y[1] + Y[2]), (Y[1] + Y[3]), … (Y[1] + Y[n-1]),
  …
  …
  (Y[i] + Y[i+1]), (Y[i] + Y[i+2]), … (Y[i] + Y[n-1]),
  …
  …
  (Y[n-2] + Y[n-1])
]

Input : [3, 4, 5, 5, 6, 7]
Output: [1, 2, 3, 4]
Explanation: The input array [3, 4, 5, 5, 6, 7] is formed by the sum of every distinct pair of the
output array [(1 + 2), (1 + 3), (1 + 4), (2 + 3), (2 + 4), (3 + 4)]

Input : [3, 4, 5, 6, 5, 6, 7, 7, 8, 9]
Output: [1, 2, 3, 4, 5]
Explanation: [(1 + 2), (1 + 3), (1 + 4), (1 + 5), (2 + 3), (2 + 4), (2 + 5), (3 + 4), (3 + 5)]

Input : [3, 4, 5]
Output: [1, 2, 3]
Explanation: [(1 + 2), (1 + 3), (2 + 3)]


Note: Assume valid input and input size > 2

*/

#include <algorithm>
#include <set>

std::vector<int> valhalla::arrays::decode_array::Solution::decode(std::vector<int> const & nums) {
    std::vector<int> decoded;

    if ( ! nums.empty() ) {
        std::vector<int> result = nums;
        std::set<int> used;

        std::sort(result.begin(), result.end());

        const int sub = result[0];
        int last = result[0];

        // ad the first entry since it will always be part of the pair solution
        used.insert(last);

        for (int num : result) {
            if (num != last && num != sub) {
                last = num;
                // know that all of the values in used are less than num
                // so let us see if we can find a combination.
                int diff = num - sub;
                // second == true means that the value was inserted
                // used.insert(diff).second;
                if (diff == sub || used.find(diff) == used.end()) {
                    bool not_found = true;
                    for (std::set<int>::const_reverse_iterator itr = used.rbegin() ; itr != used.rend() ; itr++) {
                        int value = *itr;
                        if (used.find(num - value) != used.end()) {
                            not_found = false;
                            break;
                        } // if
                    } // for
                    if (not_found) {
                        used.insert(diff);
                    } // if
                } // if
            } // if
        } // for

        for (int value : used) {
            decoded.push_back(value);
        } // for
    } // if

    return decoded;
}
