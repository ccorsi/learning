/**
 * @file checkers.h
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This file contains the different checkers template classes
 * @version 0.1
 * @date 2024-03-04
 *
 * @copyright Copyright (c) 2024 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#ifndef __CHECKERS_H__
#define __CHECKERS_H__

#include <istream>
#include <cwctype>
#include <cctype>
#include <type_traits>
#include <stdexcept>

namespace valhalla
{

namespace checkers
{

template<typename Type>
struct is_space_noop {
    is_space_noop() = default;
    bool operator()(Type chr) { return false; }
};

template<typename Type, typename IntType>
struct is_space_base {
    is_space_base() = default;
    bool operator()(IntType chr) {
        if constexpr (std::is_same_v<char, Type>) {
            return std::isspace(chr) != 0;
        } else {
            if constexpr (std::is_same_v<wchar_t, Type>) {
                return std::iswspace(chr) != 0;
            } else {
                // #error "Incorrect character type, only char or wchar_t are valid types "
                throw std::runtime_error(std::string("Unknown character type: ") + std::string(typeid(Type).name()));
            }
        }
    }
};
struct is_space : public is_space_base<char,int> {
    is_space() = default;
};
struct is_wspace : public is_space_base<wchar_t, wint_t> {
    is_wspace() = default;
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

} // namespace checkers

} // namespace valhalla

#endif // __CHECKERS_H__
