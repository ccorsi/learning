/**
 * @file power_of_four.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This is a solution to the problem https://www.techiedelight.com/?problem=PowerOf4
 * @version 0.1
 * @date 2025-03-13
 *
 * @copyright Copyright (c) 2025 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include "power_of_four.h"

#include <iostream>
#include <bitset>

namespace valhalla {

namespace bit_manipulation {

namespace power_of_four {

/*

Given a positive number, check if it is a power of 4 or not.

Input: 256
Output: true

Input: 25
Output: false

*/

bool Solution::isPowerOf4(int n) {
    if (n == 0) return false;
    int shifts = sizeof(int) * 4 - 1;
    int mask = 0x1;
    for (int mask = 0x1 ; shifts-- > 0 ; mask <<= 2) {
        if (mask == n)
            return true;
    } // for (int mask = 0x1 ; shifts-- > 0 ; mask <<= 2)
    return false;
} // isPowerOf4

} // namespace power_of_four

} // namespace bit_manipulation

} // namespace valhalla
