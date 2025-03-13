/**
 * @file unset_rightmost_set_bit.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This is a solution to the problem https://www.techiedelight.com/?problem=UnsetRightmostSetBit
 * @version 0.1
 * @date 2025-03-11
 *
 * @copyright Copyright (c) 2025 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include "unset_rightmost_set_bit.h"

namespace valhalla {

namespace bit_manipulation {

namespace unset_rightmost_set_bit {

/*

Given an integer, unset its rightmost set bit.

Input: n = 20
Output: 16
Explanation:

20 in binary is 00010100
16 in binary is 00010000

*/

int Solution::unsetRightmostSetBit(int n) {
    if (n == 0) {
        return n;
    } // if (n == 0)

    int k = 0;
    while (n % 2 == 0) {
        k++;
        n >>= 1;
    } // while (n % 2 == 0)

    n >>= 1;
    k++;
    return n <<= k;

    // return n;
} // unsetRightmostSetBit

} // namespace unset_rightmost_set_bit

} // namespace bit_manipulation

} // namespace valhalla
