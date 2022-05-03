/**
 * @file debug.h
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This file contains the debug class that can be used throughout to help debug the
 *      different implementations.  If will look for an environment variable and parse the
 *      debug level that we are going to use.
 * @version 0.1
 * @date 2022-03-28
 * 
 * @copyright Copyright (c) 2022 Claudio Corsi
 * 
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#ifndef __DEBUG_H__
#define __DEBUG_H__

#include <string>

/**
 * @brief This is the class that performs the logging of messages.  The user 
 *      should not be using this but instead should just use the macros that
 *      are defined instead.
 * 
 */
struct debug_manager {
    static void log(const char* filename, int lineno, std::string& msg);
    static void debug(const char* filename, int lineno, std::string& msg);
    static void warn(const char* filename, int lineno, std::string& msg);
    static void error(const char* filename, int lineno, std::string& msg);

    static void log(const char* filename, int lineno, const char* msg);
    static void debug(const char* filename, int lineno, const char* msg);
    static void warn(const char* filename, int lineno, const char* msg);
    static void error(const char* filename, int lineno, const char* msg);
};

// used for log level messages
#define LOGMSG(msg) debug_manager::log(__FILE__, __LINE__, msg)

#define DEBUGMSHG(msg) debug_manager::debug(__FILE__, __LINE__, msg)

#define WARNMSG(msg) debug_manager::warn(__FILE__, __LINE__, msg)

#define ERRORMSG(msg) debug_manager::error(__FILE__, __LINE__, msg)

#endif

