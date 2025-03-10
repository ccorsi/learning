/**
 * @file turn_off_kth_bit.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This is a solution to the problem https://www.techiedelight.com/?problem=TurnOffKthBit
 * @version 0.1
 * @date 2025-03-10
 *
 * @copyright Copyright (c) 2025 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include "turn_off_kth_bit.h"

#include <iostream>

namespace valhalla {

namespace bit_manipulation {

namespace turn_off_kth_bit {

/*

Given an integer n and a positive number k, turn off k'th bit in n.

Input: n = 20, k = 3
Output: 16
Explanation:

20 in binary is 00010100
16 in binary is 00010000

Input: n = -20, k = 3
Output: -24
Explanation:

-20 in binary is 1111111111101100
-24 in binary is 1111111111101000

*/

int Solution::turnOffKthBit(int n, int k) {
    int mask = 1 << (k -1);
    // n ^= mask;
    // return n ^ (1 << (k - 1));
    return (n & mask) ? n ^ mask : n;
} // turnOffKthBit

} // namespace turn_off_kth_bit

} // namespace bit_manipulation

} // namespace valhalla
