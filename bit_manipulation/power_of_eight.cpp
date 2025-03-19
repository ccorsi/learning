/**
 * @file power_of_eight.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This is a solution to the problem https://www.techiedelight.com/?problem=PowerOf8
 * @version 0.1
 * @date 2025-03-17
 *
 * @copyright Copyright (c) 2025 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include "power_of_eight.h"

namespace valhalla {

namespace bit_manipulation {

namespace power_of_eight {

/*

Given a number, check if it is a power of 8 or not.

Input: 512
Output: true

Input: 56
Output: false

*/

bool Solution::isPowerOf8(int n) {
    if (n == 0) {
        return false;
    }
    int shifts = ( sizeof(int) * 8 / 3 ) - 1;
    int mask = 0x1;
    for (int mask = 0x1 ; shifts-- > 0 ; mask <<= 3) {
        if (mask == n) {
            return true;
        }
    } // for (int mask = 0x1 ; shifts-- > 0 ; mask <<= 3)

    return false;
} // isPowerOf8

} // namespace power_of_eight

} // namespace bit_manipulation

} // namespace valhalla
