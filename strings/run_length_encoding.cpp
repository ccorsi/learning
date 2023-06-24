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



                return encoded;
            } // encode
        }
    }
}
