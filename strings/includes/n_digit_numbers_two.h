/**
 * @file n_digit_numbers_two.h
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains the header information for the problem https://www.techiedelight.com/?problem=NDigitNumbersII
 * @version 0.1
 * @date 2025-02-19
 *
 * @copyright Copyright (c) 2025 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#ifndef __N_DIGIT_NUMBERS_TWO_H__
#define __N_DIGIT_NUMBERS_TWO_H__

#include <unordered_set>
#include <string>

namespace valhalla {

namespace strings {

namespace n_digit_numbers_two {

class Solution {
public:
    std::unordered_set<std::string> findNDigitNumbers(int);
};

} // namespace n_digit_numbers_two

} // namespace strings

} // namespace valhalla

#endif
