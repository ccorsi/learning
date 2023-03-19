/**
 * @file decode_array.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains a solution to the problem https://www.techiedelight.com/?problem=DecodeArray
 * @version 0.3
 * @date 2023-03-17
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include "decode_array.h"

#include <cmath>

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

Input : [7, 8, 8, 9, 10, 9, 9, 10, 11, 10, 11, 12, 11, 12, 13]
Output: [3, 4, 5, 5, 6, 7]
Explanation: [(3 + 4), (3 + 5), (3 + 5), (3 + 6), (3 + 7), (4 + 5), (4 + 5), (4 + 6), (4 + 7), (5 + 5), (5 + 6), (5 + 7), (5 + 6), (5 + 7), (6 + 7)]

Input : [6, 6, 7, 6, 7, 7]
Output: [3, 3, 3, 4]
Explanation: [(3, 3), (3, 3), (3, 4), (3, 3), (3, 4), (3, 4)]

Input:  [8, 10, 12, 12, 14, 16]
Output: [3, 5, 7, 9]
Explanation: [(3 + 5), (3 + 7), (3 + 9), (5 + 7), (5 + 9), (7 + 9)]

Note: Assume valid input and input size > 2

*/

std::vector<int> valhalla::arrays::decode_array::Solution::decode(std::vector<int> const & nums) {
    std::vector<int> decoded;
    const int size = nums.size();

    if ( size > 1 ) {
        // We to determine the number of entries that are required to create the nums array
        const int size = ( 1 + static_cast<int>(std::sqrt( 1 + 8 * nums.size() )) ) / 2;

        decoded.push_back(( nums[0] + nums[1] - nums[size - 1] ) / 2);
        decoded.push_back( nums[0] - decoded[0] );

        for (int idx = 2 ; idx < size ; idx++) {
            decoded.push_back(nums[idx-1] - decoded[0]);
        } // for
    } // if

    return decoded;
}
