/**
 * @file turn_on_kth_bit.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains a solution to the problem https://www.techiedelight.com/?problem=TurnOnKthBit
 * @version 0.1
 * @date 2025-03-10
 *
 * @copyright Copyright (c) 2025 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include "turn_on_kth_bit.h"

namespace valhalla {

namespace bit_manipulation {

namespace turn_on_kth_bit {

/*

Given an integer n and a positive number k, turn on k'th bit in n.

Input: n = 20, k = 4
Output: 28
Explanation:

20 in binary is 00010100
28 in binary is 00011100


Input: n = -24, k = 3
Output: -20
Explanation:

-24 in binary is 1111111111101000
-20 in binary is 1111111111101100

*/

int Solution::turnOnKthBit(int n, int k) {
    int mask = (1 << (k - 1));
    return (n & mask) == false ? n | mask : n;
} // turnOnKthBit

} // namespace turn_on_kth_bit

} // namespace bit_manipulation

} // namespace valhalla
