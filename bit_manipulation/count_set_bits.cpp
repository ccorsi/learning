/**
 * @file count_set_bits.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains a solution to the problem https://www.techiedelight.com/?problem=CountSetBits
 * @version 0.1
 * @date 2025-03-11
 *
 * @copyright Copyright (c) 2025 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include "count_set_bits.h"

#include <iostream>

namespace valhalla {

namespace bit_manipulation {

namespace count_set_bits {

/*

Given an integer, count its set bits.

Input: n = 16
Output: 1
Explanation: The binary representation of 16 is 00000000000000000000000000001000.

Input: n = -1
Output: 32
Explanation: The binary representation of -1 is 11111111111111111111111111111111.

*/

int Solution::countSetBits(int n) {
    if (n == 0) {
        return 0;
    } // if (n == 0)

    int size = sizeof(int) * 8, mask = 0x1, count = 0;

    while (size-- > 0) {
        if ( (n & mask) != 0) {
            count++;
        } // if ( (n & mask) != 0)
        mask <<= 1;
    } // while (size-- > 0)

    return count;
} // countBitSets

} // namespace count_set_bits

} // namespace bit_manipulation

} // namespace valhalla
