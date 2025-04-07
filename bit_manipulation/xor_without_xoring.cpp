/**
 * @file xor_without_xoring.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This is a solution to the problem https://www.techiedelight.com/?problem=XORWithoutXORing
 * @version 0.1
 * @date 2025-03-22
 *
 * @copyright Copyright (c) 2025 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include "xor_without_xoring.h"

namespace valhalla {

namespace bit_manipulation {

namespace xor_without_xoring {

/*

Given two integers, find their XOR without using the XOR operator.

Input: x = 65, y = 80
Output: 17
Explanation: x in binary is 01000001 and y in binary is 01010000.
    Their XOR is 00010001, which is 17 in decimal.

*/

int Solution::findXOR(int x, int y) {
    int result = 0;
    int mask = 0x1;

    for (int checks = sizeof(int) * 8 ; checks-- > 0 ; ) {
        if ((x & mask) != (y & mask)) {
            result |= mask;
        } // if ((x & mask) != (y & mask))
        mask <<= 1;
    } // for (int checks = sizeof(int) * 8 ; checks-- > 0 ; )

    return result;
} // findXOR

} // namespace xor_without_xoring

} // namespace bit_manipulation

} // namespace valhalla
