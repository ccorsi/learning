/**
 * @file swap_adjacent_bits.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This is a solution to the problem https://www.techiedelight.com/?problem=SwapAdjacentBits
 * @version 0.1
 * @date 2025-03-18
 *
 * @copyright Copyright (c) 2025 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include "swap_adjacent_bits.h"

// #include <iostream>
// #include <bitset>

namespace valhalla {

namespace bit_manipulation {

namespace swap_adjacent_bits {

/*

Given an integer, swap adjacent bits of it. In other words, swap bits present at even
positions with those present in odd positions.

Input:  761622921
Output: 513454662

Explanation:

761622921 (00 10 11 01 01 10 01 01 01 11 00 01 10 00 10 01)
513454662 (00 01 11 10 10 01 10 10 10 11 00 10 01 00 01 10)

*/

int Solution::swapAdjacentBits(int n) {
    int shifts = sizeof(int) * 4 - 1;
    int lmask = 0x2, rmask = 0x1;

    // std::cout << "n = " << std::bitset<sizeof(int) * 8>(n) << "\n";
    // std::cout << "lmask = " << std::bitset<sizeof(int) * 8>(lmask) << "\n";
    // std::cout << "rmask = " << std::bitset<sizeof(int) * 8>(rmask) << "\n";
    while (shifts-- > 0) {
        if (((n & lmask) && ! (n & rmask)) || ( ! (n & lmask) && (n & rmask))) {
            n ^= (lmask | rmask);
        } // if (((n & lmask) && ! (n & rmask)) || ( ! (n & lmask) && (n & rmask)))
        lmask <<= 2;
        rmask <<= 2;
        // std::cout << "n = " << std::bitset<sizeof(int) * 8>(n) << "\n";
        // std::cout << "lmask = " << std::bitset<sizeof(int) * 8>(lmask) << "\n";
        // std::cout << "rmask = " << std::bitset<sizeof(int) * 8>(rmask) << "\n";
    } // while (shifts-- > 0)

    return n;
} // swapAdjacentBits

} // namespace swap_adjacent_bits

} // namespace bit_manipulation

} // namespace valhalla
