/**
 * @file checkers.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief Contains implementations for one or more concrete check structs.
 * @version 0.1
 * @date 2023-03-08
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include "checkers.h"

bool valhalla::utils::checkers::is_space::operator()(int chr) {
    return std::isspace(chr) != 0;
}

bool valhalla::utils::checkers::is_wspace::operator()(wint_t chr) {
    return iswspace(chr) != 0;
}
