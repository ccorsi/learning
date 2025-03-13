/**
 * @file count_flipped_bits.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This is a solution to the problem https://www.techiedelight.com/?problem=CountFlippedBits
 * @version 0.1
 * @date 2025-03-11
 *
 * @copyright Copyright (c) 2025 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include "count_flipped_bits.h"

namespace valhalla {

namespace bit_manipulation {

namespace count_flipped_bits {

/*

Given two integers x and y, find the total number of bits needed to be flipped for converting x to y.

Input: x = 65, y = 80
Output: 2
Explanation: The total number of bits to be flipped is 2 since 65 is 01000001 in binary and 80 is 01010000 in binary.

*/

int Solution::findBits(int x, int y) {
    int count = 0, size = sizeof(int) * 8, combined = x ^ y;

    while (size-- > 0) {
        if ((combined & 0x1) != 0) {
            count++;
        } // if ((combined & 0x1) != 0)
        combined >>= 1;
    } // while (size-- > 0)

    return count;
} // findBits

} // namespace count_flipped_bits

} // namespace bit_manipulation

} // namespace valhalla
