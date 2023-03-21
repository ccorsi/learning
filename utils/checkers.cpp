/**
 * @file checkers.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief Contains implementations for one or more concrete check structs.
 * @version 0.2
 * @date 2023-03-08
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include "checkers.h"

namespace valhalla {
    namespace utils {
        namespace checkers {

            bool is_space::operator()(int chr) {
                return std::isspace(chr) != 0;
            }

            bool is_wspace::operator()(wint_t chr) {
                return iswspace(chr) != 0;
            }
        }
    }
}
