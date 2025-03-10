/**
 * @file toggle_kth_bit.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This is a solution to the problem https://www.techiedelight.com/?problem=ToggleKthBit
 * @version 0.1
 * @date 2025-03-10
 *
 * @copyright Copyright (c) 2025 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include "toggle_kth_bit.h"

namespace valhalla {

namespace bit_manipulation {

namespace toggle_kth_bit {

/*

Given an integer n and a positive number k, toggle k'th bit of n.

Input: n = 20, k = 3
Output: 16
Explanation: 20 in binary is 00010100 and 16 in binary is 00010000

Input: n = 16, k = 3
Output: 20

*/

int Solution::toggleKthBit(int n, int k) {
    int mask = (1 << (k - 1));
    return (n & mask) ? n ^ mask : n | mask;
} // toggleKthBit

} // namespace toggle_kth_bit

} // namespace bit_manipulation

} // namespace valhalla
