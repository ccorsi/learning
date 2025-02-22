/**
 * @file n_digit_numbers_seven.h
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief
 * @version 0.1
 * @date 2025-02-22
 *
 * @copyright Copyright (c) 2025 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */
#ifndef __N_DIGIT_NUMBERS_SEVEN_H__
#define __N_DIGIT_NUMBERS_SEVEN_H__

#include <string>
#include <unordered_set>

namespace valhalla {

namespace dynamic_programming {

namespace n_digit_numbers_seven {

class Solution {
public:
    std::unordered_set<std::string> findNDigitNumbers(int);
};

} // namespace n_digit_numbers_seven

} // namespace dynamic_programming

} // namespace valhalla

#endif
