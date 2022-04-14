/**
 * @file macros.h
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief 
 * @version 0.1
 * @date 2022-03-24
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef __MACROS_H__
#define __MACROS_H__

/**
 * @brief This file will contain different macros that will be used throughout the code
 *   to help properly define method signatures and whatnot of the different implementations.
 *   This is to be able to use the correct syntax for each of the different versions of the
 *   compiler.
 * 
 *   This file will be updated whenever any of the features are being used.
 * 
 */

#if __cpp_constexpr >= 200704L
    #define CONSTEXPR11 constexpr
    #define CONSTEXPR constexpr
#else
    #define CONSTEXPR11
    #define CONSTEXPR
#endif

#if __cpp_constexpr >= 201304L
    #define CONSTEXPR14 constexpr
#else
    #define CONSTEXPR14
#endif

#if __cpp_constexpr >= 201603L
    #define CONSTEXPR17 constexpr
#else
    #define CONSTEXPR17
#endif

// The following two defines were defined for c++20 but they were included within different
// drafts of the specifciation.  This is why two separate defines were created.
#if __cpp_constexpr >= 201907L
    #define CONSTEXPR20 constexpr
#else
    #define CONSTEXPR20
#endif

#if __cpp_constexpr >= 202002L
    #define CONSTEXPR20EX constexpr
#else
    #define CONSTEXPR20EX
#endif

#if __cpp_constexpr >= 202110L
    #define CONSTEXPR23 constexpr
#else
    #define CONSTEXPR23
#endif

#endif __MACROS_H__