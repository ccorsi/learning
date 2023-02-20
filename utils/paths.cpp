/**
 * @file paths.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This file contains the different implementations of the paths utils
 * @version 0.1
 * @date 2023-02-17
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include <fstream>

#include "paths.h"

/**
 * @brief This method will check if the passed path exists.  It doesn't
 *  distinguish between a file and directory.  It will return true if the
 *  passed path exists else false.
 *
 * @param path The path to determine if it exists
 * @return true if the path is a file or directory
 * @return false if the path is not a file or directory
 */
bool valhalla::utils::paths::path_exists(std::string const & path) {
    std::ifstream fs(path);
    return fs.is_open();
}

/**
 * @brief This method will search for the filename within the current
 *  directory structure.  You should passed the expected path of the
 *  file relative to the top-level directory of your project.
 *
 * @param filename the name of the file that we are looking for
 * @param depth the number of tests that can be performed before stopping
 * @return std::string the path of the passed file or the passed file
 *  if not found
 */
std::string valhalla::utils::paths::find_path(std::string const & name, const size_t depth) {
    std::string path = name;

    for (size_t tests = 0 ; tests < depth ; tests++) {
        std::ifstream fs(path);
        if (fs.is_open()) return path;
        path = "../" + path;
    } // for

    return name;
}
