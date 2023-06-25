/**
 * @file maximum_occurring_word.h
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief
 * @version 0.1
 * @date 2023-06-24
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */
#ifndef __MAXIMUM_OCCURRING_WORD_H__
#define __MAXIMUM_OCCURRING_WORD_H__

#include <string>
#include <vector>

namespace valhalla {
    namespace strings {
        namespace maximum_occurring_word {
            class Solution {
            public:
                std::string lexigraphicSort(std::vector<std::string> const &);
            };
        }
    }
}

#endif
