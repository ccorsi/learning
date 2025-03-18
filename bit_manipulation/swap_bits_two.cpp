/**
 * @file swap_bits_two.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This is a solution to the problem https://www.techiedelight.com/?problem=SwapBitsII
 * @version 0.1
 * @date 2025-03-13
 *
 * @copyright Copyright (c) 2025 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include "swap_bits_two.h"

#include <iostream>
#include <bitset>

namespace valhalla {

namespace bit_manipulation {

namespace swap_bits_two {

/*

Given an integer `n`, swap consecutive `b` bits starting from the given positions `p` and `q`
in a binary representation of an integer. The bits to be swapped should not overlap with each other.

Input:

n = 15
p = 2, q = 5	(3rd and 6th bit from the right)
b = 2			(Total number of consecutive bits in each sequence)

Output: 99

Explanation:

15 in binary is 00001111
99 in binary is 01100011

*/

int Solution::swapBits(int n, int p, int q, int b) {
    if (p == q) {
        return n;
    }

    int pmask = 1 << p, qmask = 1 << q;

    while (b-- > 0) {
        bool pvalue = n & pmask, qvalue = n & qmask;

        if (pvalue != qvalue) {
            n ^= (pmask | qmask);
        }

        pmask <<= 1;
        qmask <<= 1;
    } // while (b-- > 0)

    return n;
} // swapBits

} // namespace swap_bits_two

} // namespace bit_manipulation

} // namespace valhalla
