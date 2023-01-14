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
    char level[81];
    size_t len;

    // Use the C+11 version of getenv instead since this is a safer version of
    // the getenv call.
    if (getenv_s(&len, level, 80, name) != 0) {
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
