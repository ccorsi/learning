/**
 * @file parity_of_number.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This is a solution to the problem https://www.techiedelight.com/?problem=ParityOfNumber
 * @version 0.1
 * @date 2025-03-12
 *
 * @copyright Copyright (c) 2025 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include "parity_of_number.h"

namespace valhalla {

namespace bit_manipulation {

namespace parity_of_number {

bool Solution::findParity(int n) {
    static const int size = sizeof(int) * 8;
    int count = 0;
    bool parity = false;

    while (count++ < size && n != 0) {
        parity = (n & 0x1) ? ! parity : parity;
        n >>= 1;
    }

    return parity;
} // findParity

} // namespace parity_of_number

} // namespace bit_manipulation

} // namespace valhalla
