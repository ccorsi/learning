/**
 * @file position_of_rightmost_set_bit.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This is a solution to the problem https://www.techiedelight.com/?problem=PositionOfRightmostSetBit
 * @version 0.1
 * @date 2025-03-11
 *
 * @copyright Copyright (c) 2025 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include "position_of_rightmost_set_bit.h"

namespace valhalla {

namespace bit_manipulation {

namespace position_of_rightmost_set_bit {

/*

Given an integer, find position of the rightmost set bit in it.

Input: n = 20
Output: 3
Explanation: 20 in binary is 00010100

*/

int Solution::positionOfRightmostSetBit(int n) {
    if (n == 0) {
        return 0;
    }

    int pos = 1;

    while (n % 2 == 0) {
        n >>= 1;
        pos++;
    }

    return pos;
} // positionOfRightmostSetBit

} // namespace position_of_rightmost_set_bit

} // namespace bit_manipulation

} // namespace valhalla
