/**
 * @file run_length_encoding.h
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief
 * @version 0.1
 * @date 2023-06-24
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */
#ifndef __RUN_LENGTH_ENCODING_H__
#define __RUN_LENGTH_ENCODING_H__

#include <string>

namespace valhalla {
    namespace strings {
        namespace run_length_encoding {
            class Solution {
            public:
                std::string encode(std::string);
            };
        }
    }
}

#endif
