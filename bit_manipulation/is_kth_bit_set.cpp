/**
 * @file is_kth_bit_set.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This is a solution to the problem https://www.techiedelight.com/?problem=IsKthBitSet
 * @version 0.1
 * @date 2025-03-10
 *
 * @copyright Copyright (c) 2025 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include "is_kth_bit_set.h"

namespace valhalla {

namespace bit_manipulation {

namespace is_kth_bit_set {

/*

Given an integer n and a positive number k, check if k'th bit is set or not.

Input: n = 20, k = 3
Output: true
Explanation: 20 in binary is 00010100

Input: n = 16, k = 3
Output: false
Explanation: 16 in binary is 00010000

*/

bool Solution::isKthBitSet(int n, int k) {
    return n & (1 << (k - 1));
} // isKthBitSet

} // namespace is_kth_bit_set

} // namespace bit_manipulation

} // namespace valhalla
