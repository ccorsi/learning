/**
 * @file n_digit_numbers.h
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief
 * @version 0.1
 * @date 2025-02-07
 *
 * @copyright Copyright (c) 2025 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#ifndef __N_DIGIT_NUMBERS_H__
#define __N_DIGIT_NUMBERS_H__

#include <unordered_set>

namespace valhalla {

namespace strings {

namespace n_digit_numbers {

class Solution {
public:
    std::unordered_set<int> findStrictlyIncreasingNumbers(int);
};

} // namespace n_digit_numbers

} // namespace strings

} // namespace valhalla

#endif
