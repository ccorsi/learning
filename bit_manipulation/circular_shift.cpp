/**
 * @file circular_shift.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This is a solution to the problem https://www.techiedelight.com/?problem=CircularShift
 * @version 0.1
 * @date 2025-03-19
 *
 * @copyright Copyright (c) 2025 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include "circular_shift.h"

#include <iostream>
#include <bitset>

namespace valhalla {

namespace bit_manipulation {

namespace circular_shift {

/*

Given two positive integers n and k, perform a circular shift on the binary representation of n by k positions.

The circular shift can be of two types:

• Left circular shift (moving the final bit to the first position while shifting all other bits to the next position).
• Right circular shift (moving the first bit to the last position while shifting all other bits to the previous position).


Input: n = 127, k = 3, isLeftShift = true
Output: 1016

Explanation:

The binary representation for n = 127 is: 00000000000000000000000001111111
Left shift 127 by 3 positions results in: 00000000000000000000001111111000


Input: n = 127, k = 3, isLeftShift = false
Output: -536870897

Explanation:

The binary representation for n = 127 is : 00000000000000000000000001111111
Right shift 127 by 3 positions results in: 11100000000000000000000000001111


Assume integer size to be 32 bits (4 bytes).

*/

int attempt_two(int n, int k, bool isLeftShift) {
    const int bits = sizeof(int) * 8;
    int lshift, rshift;

    if (isLeftShift) {
        lshift = bits - k;
        rshift = k;
    } else {
        lshift = k;
        rshift = bits - k;
    } // if (m_isLeftShift)

    std::cout << "k = " << k << " isLeftShift = " << (isLeftShift ? "true" : "false") << '\n';
    std::cout << "0: n = " << std::bitset<bits>(n) << " = " << n << '\n';
    n = ((n >> lshift) ^ (-1 << (bits - k))) | (n << rshift);
    std::cout << "1: n = " << std::bitset<bits>(n) << " = " << n << '\n';

    return n;
} // attempt_two

int attempt_one(int n, int k, bool isLeftShift) {
    const int bits = sizeof(int) * 8;
    const int mask = 0x1 << (bits - 1);

    // std::cout << "k = " << k << " isLeftShift = " << (isLeftShift ? "true" : "false") << '\n';
    // std::cout << "mask = " << std::bitset<bits>(mask) << '\n';
    // std::cout << "0: n = " << std::bitset<bits>(n) << " = " << n << '\n';

    // std::cout << "{ " << n << ", " << k << ", " << isLeftShift << ", ";
    while (k-- > 0) {
        if (isLeftShift) {
            if (n & mask) {
                // std::cout << "1: ";
                n <<= 1;
                n |= 0x1;
            } else {
                // std::cout << "2: ";
                n <<= 1;
            } // if (n & mask)
        } else {
            if (n & 0x1) {
                // std::cout << "3: ";
                n >>= 1;
                n |= mask;
            } else {
                // std::cout << "4: ";
                n >>= 1;
                n ^= (n & mask) ? mask : 0x0;
            } // if (n & 0x1)
        } // if (isLeftShift)
        // std::cout << "n = " << std::bitset<bits>(n) << " = " << n << '\n';
    } // while (k-- > 0)
    // std::cout << n << "}\n";

    // std::cout << "5: n = " << std::bitset<bits>(n) << " = " << n << '\n';
    return n;
} // attempt_one

int Solution::circularShift(int n, int k, bool isLeftShift) {
    return attempt_one(n,k,isLeftShift);
} // circularShift

} // namespace circular_shift

} // namespace bit_manipulation

} // namespace valhalla
