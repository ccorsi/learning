/**
 * @file swap_bits.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This is a solution to the problem https://www.techiedelight.com/?problem=SwapBits
 * @version 0.1
 * @date 2025-03-12
 *
 * @copyright Copyright (c) 2025 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include "swap_bits.h"

#include <iostream>

namespace valhalla {

namespace bit_manipulation {

namespace swap_bits {

/*

Given an integer, swap two bits at given positions in a binary representation of it.

Input:

n = 31
p = 2, q = 6 (3rd and 7th bit from the right)

Output: 91

Explanation:

31 in binary is 00011111
91 in binary is 01011011

*/

int Solution::swapBits(int n, int p, int q) {
    if (p == q) {
        return n;
    }

    const int pmask = 1 << p, qmask = 1 << q;
    bool pvalue = n & pmask, qvalue = n & qmask;

    if (pvalue == qvalue) {
        return n;
    }

    return n ^ (pmask | qmask);
} // swapBits

} // namespace swap_bits

} // namespace bit_manipulation

} // namespace valhalla
