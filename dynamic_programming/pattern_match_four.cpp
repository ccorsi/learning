/**
 * @file pattern_match_four.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains a solution to the problem https://www.techiedelight.com/?problem=PatternMatchIV
 * @version 0.1
 * @date 2023-07-05
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include "pattern_match_four.h"

namespace valhalla {

namespace dynamic_programming {

namespace pattern_match_four {

/*

Given a string and a pattern, count the number of times pattern appears in the string as a subsequence.

Input: word = 'subsequence', pattern = 'sue'
Output: 7
Explanation:

'su' bs 'e' quence
'su' bsequ 'e' nce
'su' bsequenc 'e'
's' ubseq 'ue' nce
's' ubseq 'u' enc 'e'
sub 's' eq 'ue' nce
sub 's' eq 'u' enc 'e'

*/

int Solution::count(std::string word, std::string pattern) {
    int total = -2;


    return total;
} // count

} // namespace pattern_match_four

} // namespace dynamic_programming

} // namespace valhalla
