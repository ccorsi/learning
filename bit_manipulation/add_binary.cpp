/**
 * @file add_binary.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This is a solution to the problem https://www.techiedelight.com/?problem=AddBinary
 * @version 0.1
 * @date 2025-03-18
 *
 * @copyright Copyright (c) 2025 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include "add_binary.h"

namespace valhalla {

namespace bit_manipulation {

namespace add_binary {

/*

Given two integers, add their binary representation.

Input: x = 12731, y = 38023
Output: "00000000000000001100011001000010"

Explanation:

x (12731) in binary is 00000000000000000011000110111011
y (38023) in binary is 00000000000000001001010010000111
x + y is 00000000000000001100011001000010

*/

std::string Solution::add(int x, int y) {
    int shifts = sizeof(int) * 8;
    std::string binary(shifts, '0');
    int mask = 0x1;
    int carry = 0;

    while (shifts-- > 0) {
        if (x & mask) carry++;
        if (y & mask) carry++;
        if (carry & 0x1) binary[shifts] = '1';
        carry >>= 1;
        mask <<= 1;
    }

    return binary;
} // add

} // namespace add_binary

} // namespace bit_manipulation

} // namespace valhalla
