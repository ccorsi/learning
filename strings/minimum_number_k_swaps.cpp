/**
 * @file minimum_number_k_swaps.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This is a soluition to the problem https://www.techiedelight.com/?problem=MinimumNumberKSwaps
 * @version 0.1
 * @date 2023-05-20
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include "minimum_number_k_swaps.h"

#include <algorithm>

namespace valhalla {
    namespace strings {
        namespace minimum_number_k_swaps {
            /*

            Given string representation of a positive integer, find the minimum number
            possible by doing at-most `k` swap operations upon its digits.

            Input : s = "934651", k = 1
            Output: 134659

            Input : s = "934651", k = 2
            Output: 134569

            Input : s = "52341", k = 2
            Output: 12345 (Only 1 swap needed)

            Input : s = "12345", k = 2
            Output: 12345 (no change as all digits are already sorted in increasing order)

            */

            std::string Solution::findMinNumber(std::string s, int k) {
                const std::string::size_type size = s.size();
                std::string::size_type cnt = 0;

                while (cnt < size && k > 0) {
                    char chr = s[cnt];
                    std::string::size_type smallest = cnt;

                    for (std::string::size_type idx = smallest + 1 ; idx < size ; idx++) {
                        if (s[idx] <= chr) {
                            smallest = idx;
                            chr = s[idx];
                        } // if
                    } // for

                    if (chr != s[cnt] && smallest != cnt) {
                        char tmp = s[cnt];
                        s[cnt] = s[smallest];
                        s[smallest] = tmp;
                        k--;
                    }
                    cnt++;
                } // while

                return s;
            } // findMinNumber
        }
    }
}
