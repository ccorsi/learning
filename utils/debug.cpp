/**
 * @file debug.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This file contains the debug class that will be used to help debug any issues with different implementations.
 * @version 0.1
 * @date 2022-03-28
 * 
 * @copyright Copyright (c) 2022 Claudio Corsi
 * 
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */
#include <iostream>
#include <string>

#include "debug.h"

using namespace std;

// #if defined(__APPLE__) || defined(__MACH__)
//     #define GETENV getenv
// #elif defined(__linux__)
//     #define GETENV getenv
// #elif defined(_WIN32)
//     #define GETENV getenv
// #else
//     #error "Unale to determine the Operating System Type"
// #endif

/**
 * @brief Get the debug level
 * 
 * @return int 
 */
int get_debug_level() {
    const char *name = "DEBUGLEVEL";
    char level[81];
    size_t len;

    // Use the C+11 version of getenv instead since this is a safer version of
    // the getenv call.
    if (getenv_s(&len, level, 80, name) != 0) {
        // This will return 0 if no conversion was possible
        return atoi(level);
    } else {
        return 0;
    }
}

int debugLevel = get_debug_level();

void debug_manager::log(const char* fname, int lineno, string& msg) {
    cout << "LOG: " << fname << " at line: " << lineno << " :: " << msg << endl;
}

void debug_manager::debug(const char* fname, int lineno, string& msg) {
    cout << "DEBUG: " << fname << " at line: " << lineno << " :: " << msg << endl;
}

void debug_manager::warn(const char* fname, int lineno, string& msg) {
    cout << "WARN: " << fname << " at line: " << lineno << " :: " << msg << endl;
}

void debug_manager::error(const char* fname, int lineno, string& msg) {
    cout << "ERROR: " << fname << " at line: " << lineno << " :: " << msg << endl;
}

void debug_manager::log(const char* fname, int lineno, const char* msg) {
    cout << "LOG: " << fname << " at line: " << lineno << " :: " << msg << endl;
}

void debug_manager::debug(const char* fname, int lineno, const char* msg) {
    cout << "DEBUG: " << fname << " at line: " << lineno << " :: " << msg << endl;
}

void debug_manager::warn(const char* fname, int lineno, const char* msg) {
    cout << "WARN: " << fname << " at line: " << lineno << " :: " << msg << endl;
}

void debug_manager::error(const char* fname, int lineno, const char* msg) {
    cout << "ERROR: " << fname << " at line: " << lineno << " :: " << msg << endl;
}
