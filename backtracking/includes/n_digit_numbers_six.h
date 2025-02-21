/**
 * @file n_digit_numbers_six.h
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief
 * @version 0.1
 * @date 2025-02-20
 *
 * @copyright Copyright (c) 2025 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */
#ifndef __N_DIGIT_NUMBERS_SIX_H__
#define __N_DIGIT_NUMBERS_SIX_H__

#include <unordered_set>

namespace valhalla {

namespace backtracking {

namespace n_digit_numbers_six {

class Solution {
public:
    std::unordered_set<int> findNDigitNumbers(int);
};

} // namespace n_digit_numbers_six

} // namespace backtracking

} // namespace valhalla

#endif
