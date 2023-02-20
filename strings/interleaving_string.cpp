/**
 * @file interleaving_string.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This is a solution to the problem https://www.techiedelight.com/?problem=InterleavingString
 * @version 0.1
 * @date 2023-02-14
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include <iostream>
#include <cstring>

#include "interleaving_string.h"

/*

Find all interleavings of given strings that can be formed from all the characters of the first and second string where the order of characters is preserved.

Input: X = "ABC", Y = "ACB"
Output: {"ACBABC", "AABCBC", "ACABCB", "ABCACB", "AACBBC", "ABACCB", "ACABBC", "ABACBC", "AACBCB", "AABCCB"}

Input: X = "", Y = ""
Output: {}

*/

std::unordered_set<std::string> valhalla::strings::interleaving_string::Solution::findInterleavings(std::string X, std::string Y) {
    std::unordered_set<std::string> results;
    const size_t x_len = X.size(), y_len = Y.size();

    if (x_len + y_len > 0) {
        // concatenate the two strings
        std::string str = X + Y;
        // insert the concatenated string into the result container
        results.insert(str);

        // only produce combinations if both strings are greater than zero
        if (x_len != 0 && y_len != 0) {
            // create a copy of concatenate strings
            const char *s = str.c_str();
            // get the len and size required to store the concatenated strings
            const size_t str_len = str.length();
            const size_t str_size = str_len + 1;

            for (size_t step_size = 0 ; step_size < x_len ; ) {
                char* chrs = new char[str_size]; // dynamically create an updatable string
                strcpy_s(chrs, str_size, s); // copy constant string to chrs

                step_size++; // increment the step size

                std::cout << "chrs: " << chrs << ", step_size: " << step_size << std::endl;
                for (size_t start_from = x_len ; start_from > 0 ; start_from--) {
                    for (size_t start = start_from - step_size, end = str_len - step_size + 1; start <= end && end < str_size; start++, end-= step_size) {
                        char chr = chrs[start];
                        for (size_t idx = 0 ; idx < step_size ; idx++) {
                            chrs[start + idx] = chrs[start + idx + 1];
                        } // for
                        chrs[start + step_size] = chr;
                        std::cout << "Adding chrs: " << chrs << ", start: " << start << ", end: " << end << std::endl;
                        results.insert(chrs);
                    }  // for
                } // for
                delete [] chrs; // delete the allocated characters
                /*
                const size_t start = x_len + step_size; // calculate the start
                const size_t end = str_len; // set end
                step_size++;  // increment the step size used to copy characters around

                std::cout << "chrs: " << chrs << ", step_size: " << step_size << ", start: " << start << ", end: " << end << std::endl;
                for (size_t cur = start ; cur < end ; cur += step_size) {
                    char chr = chrs[cur]; // get a copy of the cur character
                    std::cout << "chr[" << cur << "]: " << chr << std::endl;
                    for (size_t idx = 0 ; idx < step_size ; idx++) {
                        chrs[cur - idx] = chrs[cur - idx - 1];
                        std::cout << "Update chrs: " << chrs << ", cur - idx - 1: " << (cur - idx - 1) << std::endl;
                    } // for
                    chrs[cur - step_size] = chr;
                    std::cout << "Adding chrs: " << chrs << ", cur - step_size: " << (cur - step_size) << std::endl;
                    results.insert(chrs);
                } // for

                delete [] chrs; // delete allocated string
                */
            } // for
        } // if
    } // if

    /*
    if (x_len + y_len > 0) {
        // concatenate the two strings
        std::string str = X + Y;
        // insert the concatenated string into the result container
        results.insert(str);

        // only produce combinations if both strings are greater than zero
        if (x_len != 0 && y_len != 0) {
            const char *s = str.c_str();
            const size_t str_len = str.length();
            size_t len = strlen(s);

            for (size_t size = 0 ; size < x_len ; ) {
                // char* chrs = _strdup(s); // always start with the same string
                char* chrs = new char[str_len + 1];
                strcpy_s(chrs, str_len + 1, s); // copy constant string to chrs
                len = x_len; // reset the len to x_len
                size_t end = y_len - size;
                size++; // increment size

                while (len-- > 0) {
                    for (size_t idx = 0 ; idx < end ; idx+=size) {
                        char chr = chrs[len + idx];
                        for (size_t extra = 0 ; extra < size ; extra++ ) {
                            chrs[len + idx + extra] = chrs[len + idx + extra + 1];
                        } // for
                        chrs[len + idx + size] = chr;

                        results.insert(chrs);
                    } // for
                } // while
                // free the space since we are done
                delete [] chrs;
                // set the pointer to nullptr
                chrs = nullptr;
            } // for
        } // if
    } // if
    */

    return results;
}
