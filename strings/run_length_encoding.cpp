/**
 * @file run_length_encoding.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains a solution to the problem https://www.techiedelight.com/?problem=RunLengthEncoding
 * @version 0.1
 * @date 2023-06-24
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include "run_length_encoding.h"

#include <vector>

namespace valhalla {
    namespace strings {
        namespace run_length_encoding {
            /*

            Run–length encoding (RLE) is a simple form of lossless data compression that runs
            on sequences with the same value occurring many consecutive times. It encodes the
            sequence to store only a single value and its count.

            Input: "WWWWWWWWWWWWBWWWWWWWWWWWWBBBWWWWWWWWWWWWWWWWWWWWWWWWBWWWWWWWWWWWWWW"
            Output: "12W1B12W3B24W1B14W"
            Explanation: String can be interpreted as a sequence of twelve W’s, one B,
                         twelve W’s, three B’s, and so on..

            */

            std::string Solution::encode(std::string s) {
                std::string encoded;

                if (s.empty()) {
                    return encoded;
                }

                char current = s[0];
                int count = 0;

                for(char chr : s) {
                    if (chr != current) {
                        std::vector<char> value;
                        while (count > 0) {
                            value.push_back('0' + count % 10);
                            count /= 10;
                        } // while
                        for(std::vector<char>::reverse_iterator itr = value.rbegin() ; itr != value.rend() ; itr++) {
                            encoded += *itr;
                        } // for
                        encoded += current;
                        current = chr;
                        count = 1;
                    } else {
                        count++;
                    }
                } // for

                if (count > 0) {
                    std::vector<char> value;
                    while (count > 0) {
                        value.push_back('0' + count % 10);
                        count /= 10;
                    } // while
                    for(std::vector<char>::reverse_iterator itr = value.rbegin() ; itr != value.rend() ; itr++) {
                        encoded += *itr;
                    } // for
                    encoded += current;
                }

                return encoded;
            } // encode
        }
    }
}
