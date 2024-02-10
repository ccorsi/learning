/**
 * @file minimum_inversions.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains a solution to the problem https://www.techiedelight.com/?problem=MinimumInversions
 * @version 0.1
 * @date 2023-06-29
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include "minimum_inversions.h"

#include <stack>

namespace valhalla {
    namespace strings {
        namespace minimum_inversions {
            /*

            Given an expression consisting of an opening brace '{' and a closing brace '}',
            find the minimum number of inversions needed to balance the expression.

            Input : "{{}{{}{{"
            Output: 2
            Explanation: Minimum number of inversions needed is 2, as shown below:

            {{}{{}{{ ——> {{}{{}}{ ——> {{}{{}}}


            Input : "{{{{{{"
            Output: 3
            Explanation: Minimum number of inversions needed is 3, as shown below:

            {{{{{{ ——> {{{}{{ ——> {{{}}{ ——> {{{}}}


            The solution should return -1 on invalid input.

            */

            int Solution::findMinimumInversions(std::string s) {
                int min = -1;
                std::string::size_type size = s.size();

                if (size % 2 == 0) {
                    min = 0;
                    // check that we hava a balanced string
                    std::stack<char> parans;

                    for(char chr : s) {
                        switch(chr) {
                            case '{':
                                parans.push(chr);
                                break;
                            case '}':
                                if (parans.size() == 0) {
                                    min++;
                                    parans.push('{');
                                } else {
                                    if (parans.top() != '{') min++;
                                    parans.pop();
                                } // else
                                break;
                        } // switch
                    } // for
                    min += ( static_cast<int>( parans.size() ) / 2 );
                } // if

                return min;
            } // findMinimumInversions
        }
    }
}
