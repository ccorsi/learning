/**
 * @file debug.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This file contains the debug class that will be used to help debug any issues with different implementations.
 * @version 0.2
 * @date 2022-03-28
 * 
 * @copyright Copyright (c) 2022 Claudio Corsi
 * 
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

#include "debug.h"

using namespace std;

const int NONE = 0;
const int LOG = 1;
const int WARN = 2;
const int DEBUG = 3;
const int ERROR = 4;

/**
 * @brief Get the debug level
 * 
 * @return int 
 */
int get_debug_level() {
    static const char *name = "DEBUGLEVEL";

    // Use the C+11 version of getenv instead since this is a safer version of
    // the getenv call.
    #ifdef WIN32
    std::size_t len;
    char level[81];
    if (getenv_s(&len, level, 80, name) == 0) {
    #else
    char *level;
    if ((level = getenv(name)) != nullptr) {
    #endif
        // This will return 0 if no conversion was possible
        return atoi(level);
    } else {
        return LOG;
    }
}

// Whenever this library is loaded we want to set the debug level.
// TODO: We should consider creating something that can be dynamically updated.
int debugLevel = get_debug_level();

void debug_manager::log(const char* fname, int lineno, string& msg) {
    get_out() << "LOG: " << fname << " at line: " << lineno << " :: " << msg << endl;
}

void debug_manager::debug(const char* fname, int lineno, string& msg) {
    get_out() << "DEBUG: " << fname << " at line: " << lineno << " :: " << msg << endl;
}

void debug_manager::warn(const char* fname, int lineno, string& msg) {
    get_out() << "WARN: " << fname << " at line: " << lineno << " :: " << msg << endl;
}

void debug_manager::error(const char* fname, int lineno, string& msg) {
    get_out() << "ERROR: " << fname << " at line: " << lineno << " :: " << msg << endl;
}

void debug_manager::log(const char* fname, int lineno, const char* msg) {
    get_out() << "LOG: " << fname << " at line: " << lineno << " :: " << msg << endl;
}

void debug_manager::debug(const char* fname, int lineno, const char* msg) {
    get_out() << "DEBUG: " << fname << " at line: " << lineno << " :: " << msg << endl;
}

void debug_manager::warn(const char* fname, int lineno, const char* msg) {
    get_out() << "WARN: " << fname << " at line: " << lineno << " :: " << msg << endl;
}

void debug_manager::error(const char* fname, int lineno, const char* msg) {
    get_out() << "ERROR: " << fname << " at line: " << lineno << " :: " << msg << endl;
}

std::ostream & debug_manager::get_out() {
    static bool initialized = false;
    static bool useCout = false;
    // std::cout << "Entering get_out initialized = " << initialized << " useCout = " << useCout << std::endl;

    if ( ! initialized || ! useCout ) {
        static const char *name = "DEBUGTEST";

        static const char debugfilename[] = "debug.txt";

        static std::ofstream fout;

        // std::cout << "Inside fout initialized = " << initialized << " useCout = " << useCout << std::endl;

        if (initialized == ! useCout) {
            // std::cout << "Returning defined fout initialized = " << initialized << " useCout = " << useCout << std::endl;
            return fout;
        }

        // Use the C+11 version of getenv instead since this is a safer version of
        // the getenv call.
    #ifdef WIN32
        std::size_t len;
        char level[81];
        int errorno;
        if ((errorno = getenv_s(&len, level, 80, name)) == 0) {
    #else
        char *level;
        if ((level = getenv(name)) != nullptr) {
    #endif
            // std::cout << "Setting fout initialized = " << initialized << " useCout = " << useCout << std::endl;
            fout.open(debugfilename, std::ios::trunc);

            std::atexit([]() {
                // delete the file when exiting program
                // std::cout << "Deleting " << debugfilename << " file." << std::endl;
                std::remove(debugfilename);
            });

            initialized = true;

            // std::cout << "Exitting fout get_out" << std::endl;
            return fout;
        } // if

        // std::cout << "level = " << level << std::endl;
    } // if

    useCout = initialized = true;
    // std::cout << "Exitting cout get_out" << std::endl;
    return std::cout;

}
