/**
 * @file checkers.h
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This file contains different checker functions
 * @version 0.2
 * @date 2023-03-08
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#ifndef __CHECKERS_H__
#define __CHECKERS_H__

#include <istream>
#include <cwctype>
#include <cctype>

namespace valhalla {
    namespace utils {
        namespace checkers {
            template<typename Type>
            struct is_space_noop {
                is_space_noop() = default;
                bool operator()(Type chr) { return false; }
            };
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
            template<typename Char, typename IsSpace>
            struct skip_spaces {
                IsSpace isSpace;
                std::basic_istream<Char> & operator()(std::basic_istream<Char> & in) {
                    while (isSpace(static_cast<Char>(in.peek()))) in.get();
                    return in;
                }
            };
            // This requres c++20 to build
            // template<typename Container, Container characters>
            // struct skip_chars {
            //     bool operator()(int chr) { return std::isspace(chr) || characters.find(chr) != characters.end(); }
            // };
            template<typename Char>
            struct is_character_noop {
                bool operator()(std::basic_istream<Char> & in) {
                    return true;
                }
            };

            template<typename Char, Char... Chars>
            struct is_character {
                bool operator()(std::basic_istream<Char> & in, Char check) {
                    if (static_cast<Char>(in.peek()) != check) {
                        return false;
                    } // if
                    in.get(); // read check character
                    return true;
                }

                template<typename... Rest>
                bool operator()(std::basic_istream<Char> & in, Char check, Rest... rest) {
                    if (static_cast<Char>(in.peek()) != check) {
                        return false;
                    } // if
                    in.get(); // read check character
                    return operator()(in, rest...);
                }

                bool operator()(std::basic_istream<Char> & in) {
                    return operator()(in, Chars...);
                }
            };

            template<typename Char>
            struct is_no_character {
                int m_count = 0;
                bool operator()(std::basic_istream<Char> & in) {
                    m_count = ++m_count % 2;
                    return m_count == 0;
                }
            };
        }
    }
}

#endif
