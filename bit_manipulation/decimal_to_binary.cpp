/**
 * @file decimal_to_binary.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This is a solution to the problem https://www.techiedelight.com/?problem=DecimalToBinary
 * @version 0.1
 * @date 2025-03-18
 *
 * @copyright Copyright (c) 2025 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include "decimal_to_binary.h"

namespace valhalla {

namespace bit_manipulation {

namespace decimal_to_binary {

/*

Given an integer, find its 32-bit binary representation without using built-in functions.

Input:  20
Output: "00000000000000000000000000010100"

Input:  64
Output: "00000000000000000000000001000000"

Input:  127
Output: "00000000000000000000000001111111"

Input:  -1
Output: "11111111111111111111111111111111"

*/

std::string Solution::toBinary(int n) {
    int size = sizeof(int) * 8;
    std::string binary(size, '0');
    int mask = 0x1;

    for (int shifts = size ; shifts-- > 0 ; ) {
        if (n & mask)
            binary[shifts] = '1';
        mask <<= 1;
    } // for (int shifts = size ; shifts-- > 0 ; )

    return binary;
} // toBinary

} // namespace decimal_to_binary

} // namespace bit_manipulation

} // namespace valhalla
