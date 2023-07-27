/**
 * @file print_string_zig_zag.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains a solution to the problem https://www.techiedelight.com/?problem=PrintStringZigZag
 * @version 0.1
 * @date 2023-06-23
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */


#include "print_string_zig_zag.h"

#include <iostream>

namespace valhalla {
    namespace strings {
        namespace print_string_zig_zag {
            /*

            Given a string and a positive integer `k`, print the string in `k` rows in the zigzag form.

            Input:

            str = "THISPROBLEMISAWESOME"
            k = 3

            Output: "TPLSSHSRBEIAEOEIOMWM"

            Explanation:

            (Row 1)		T				P				L				S				S
            (Row 2)			H		S		R		B		E		I		A		E		O		E
            (Row 3)				I				O				M				W				M


            Note: If `k` is more than length of the string, return the whole string.

            */

            std::string Solution::printZigZag(std::string s, int k) {
                if (k < 1) {
                    return "";
                }

                const std::string::size_type size = s.length();

                if (k >= size || k == 1) {
                    return s;
                }

                std::string zigzag(size, ' ');

                std::string::size_type dest = 0;
                const std::string::size_type tot = (k - 1) * 2;

                // std::cout << "s: \"" << s << "\" k: " << k << " tot: " << tot << " size: " << size << std::endl;

                for (std::string::size_type row = 0 ; row < k ; row++) {
                    // determine the step size
                    std::string::size_type step[2], next = 1;
                    std::string::size_type remainder = ( row % ( k - 1 ) );
                    step[0] = tot - ( remainder * 2 );
                    if (remainder == 0) {
                      step[1] = tot;
                     } else {
                      step[1] = tot - step[0];
                    }
                    // std::cout << "row: " << row << " step[0]: " << step[0] << " step[1]: " << step[1] << std::endl;
                    for(std::string::size_type idx = row ; idx < size ; idx+=step[next]) {
                        // std::cout << "size: " << size << " dest: " << dest << " idx: " << idx << std::endl;
                        zigzag[dest++] = s[idx];
                        next = ( next + 1 ) % 2;
                    } // for
                    // std::cout << "zipzag: " << zigzag << std::endl;
                } // for

                // std::cout << "returning zigzag: " << zigzag << std::endl;

                return zigzag;
            } // printZigZag
        }
    }
}
