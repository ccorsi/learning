/**
 * @file next_power_of_two.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This is a solution to the problem https://www.techiedelight.com/?problem=NextPowerOf2
 * @version 0.1
 * @date 2025-03-12
 *
 * @copyright Copyright (c) 2025 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include "next_power_of_two.h"

#include <iostream>

namespace valhalla {

namespace bit_manipulation {

namespace next_power_of_two {

/*

Given a positive number n, find the next highest power of 2. If n itself is a power of 2, return n.

Input: n = 20
Output: 32

Input: n = 16
Output: 16

*/

int Solution::nextPowerOf2(int n) {
    int power = 2;

    while (power < n) {
        power <<= 1;
    }

    return power;
} // nextPowerOf2

} // namespace next_power_of_two

} // namespace bit_manipulation

} // namespace valhalla
