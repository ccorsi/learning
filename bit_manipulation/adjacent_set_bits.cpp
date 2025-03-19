/**
 * @file adjacent_set_bits.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This is a solution to the problem https://www.techiedelight.com/?problem=AdjacentSetBits
 * @version 0.1
 * @date 2025-03-18
 *
 * @copyright Copyright (c) 2025 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include "adjacent_set_bits.h"

// #include <iostream>
// #include <bitset>

namespace valhalla {

namespace bit_manipulation {

namespace adjacent_set_bits {

/*

Given a number, check if adjacent bits are set in the binary representation of it.

Input : 67
Output: true
Explanation: 67 in binary is 01000011 and has adjacent pair of set bits.

*/

bool Solution::isAdjacentBitsSet(int n) {
    int shifts = sizeof(int) * 8 - 1;
    int lmask = 0x2, rmask = 0x1;

    // std::cout << "n = " << std::bitset<sizeof(int) * 8>(n) << "\n";
    // std::cout << "(lmask | rmask) = " << std::bitset<sizeof(int) * 8>((lmask | rmask)) << "\n";

    while (shifts-- > 0) {
        if ((n & lmask) && (n & rmask)) {
            return true;
        } // if ((n & lmask) && (n & rmask))
        lmask <<= 1;
        rmask <<= 1;
        // std::cout << "n = " << std::bitset<sizeof(int) * 8>(n) << "\n";
        // std::cout << "(lmask | rmask) = " << std::bitset<sizeof(int) * 8>((lmask | rmask)) << "\n";
    } // while (shifts-- > 0)

    return false;
} // isAdjacentBitsSet

} // namespace adjacent_set_bits

} // namespace bit_manipulation

} // namespace valhalla
