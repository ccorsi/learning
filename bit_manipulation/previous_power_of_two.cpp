/**
 * @file previous_power_of_two.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This is a solution to the problem https://www.techiedelight.com/?problem=PreviousPowerOf2
 * @version 0.1
 * @date 2025-03-12
 *
 * @copyright Copyright (c) 2025 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include "previous_power_of_two.h"

namespace valhalla {

namespace bit_manipulation {

namespace previous_power_of_two {

/*

Given a positive number n, find the previous power of 2. If n itself is a power of 2, return n.

Input: n = 20
Output: 16

Input: n = 16
Output: 16

*/

int Solution::previousPowerOf2(int n) {
    int power = 2;

    while (power < n) {
        power <<= 1;
    }

    return power == n ? power : power >> 1;
} // previousPowerOf2

} // namespace previous_power_of_two

} // namespace bit_manipulation

} // namespace valhalla
