/**
 * @file paths.h
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This file contains different utilities that you can use to manipulate paths
 * @version 0.1
 * @date 2023-02-17
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#ifndef __PATHS_H__
#define __PATHS_H__

#include <string>

namespace valhalla {
    namespace utils {
        namespace paths {
            bool path_exists(std::string const &);
            std::string find_path(std::string const &, const size_t depth = 5);
        }
    }
}

#endif
