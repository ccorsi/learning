/**
 * @file checkers.h
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This file contains different checker functions
 * @version 0.1
 * @date 2023-03-08
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#ifndef __CHECKERS_H__
#define __CHECKERS_H__

#include <cwctype>
#include <cctype>

namespace valhalla {
    namespace utils {
        namespace checkers {
            struct is_space {
                is_space() = default;
                bool operator()(int chr);
            };
            struct is_wspace {
                is_wspace() = default;
                bool operator()(wint_t chr);
            };
            // template<typename Container>
            // struct skip_chars {
            //     Container characters;
            //     skip_chars(Container chars) : characters(chars) {}
            //     bool operator()(int chr) { return std::isspace(chr) || characters.find(chr) != characters.end(); }
            // };
            template<char... Chars>
            struct is_space_or {
                bool any_of(int chr, char check) {
                    return chr == check;
                }

                template<typename... Rest>
                bool any_of(int chr, char check, Rest... rest) {
                    return chr == check || any_of(chr, rest...);
                }

                bool operator()(int chr) {
                    return std::isspace(chr) || any_of(chr, Chars...);
                }
            };
            template<wchar_t... Chars>
            struct is_wspace_or {
                bool any_of(wint_t chr, wchar_t check) {
                    return chr == check;
                }

                template<typename... Rest>
                bool any_of(wint_t chr, wchar_t check, Rest... rest) {
                    return chr == check || any_of(chr, rest...);
                }

                bool operator()(wint_t chr) {
                    return std::iswspace(chr) || any_of(chr, Chars...);
                }
            };
            // This requres c++20 to build
            // template<typename Container, Container characters>
            // struct skip_chars {
            //     bool operator()(int chr) { return std::isspace(chr) || characters.find(chr) != characters.end(); }
            // };
        }
    }
}

#endif
