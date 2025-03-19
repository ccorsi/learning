/**
 * @file reverse_bits.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This is a solution to the problem https://www.techiedelight.com/?problem=ReverseBits
 * @version 0.1
 * @date 2025-03-18
 *
 * @copyright Copyright (c) 2025 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include "reverse_bits.h"

// #include <iostream>
// #include <bitset>

namespace valhalla {

namespace bit_manipulation {

namespace reverse_bits {

/*

Given an integer, reverse its bits using binary operators.

Input: -100
Output: 973078527
Explanation: -100 in binary is 11111111111111111111111110011100. Reversing its bits
    results in number 973078527, which is 00111001111111111111111111111111 in binary.

*/

int Solution::reverseBits(int n) {
    int shifts = sizeof(int) * 4, lshifts = sizeof(int) * 8 - 1;
    int lmask = (0x1 << lshifts), rmask = 0x1;

    // std::cout << "n     = " << std::bitset<sizeof(int) * 8>(n) << "\n";
    // std::cout << "lmask = " << std::bitset<sizeof(int) * 8>(lmask) << "\nrmask = " << std::bitset<sizeof(int) * 8>(rmask) << "\n";
    while (shifts-- > 0) {
        if ((lmask & n && ! (rmask & n)) || ( ! (lmask & n) && rmask & n) ) {
            n ^= (lmask | rmask);
        } // if ((lmask & n && ! (rmask & )n) || ( ! (lmask & n) && rmask & n))
        lmask = (0x1 << --lshifts); // instead of lmask >>= 1; since the right bits are not necessarily set to 0.
        rmask <<= 1;
        // std::cout << "n     = " << std::bitset<sizeof(int) * 8>(n) << "\n";
        // std::cout << "lmask = " << std::bitset<sizeof(int) * 8>(lmask) << "\nrmask = " << std::bitset<sizeof(int) * 8>(rmask) << "\n";
    } // while (shifts-- > 0)

    return n;
} // reverseBits

} // namespace reverse_bits

} // namespace bit_manipulation

} // namespace valhalla
