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

/**
 * @brief Used in the case that no character are supposed to be skipped.
 *
 * @tparam Type The character stream we are going to use, char or wchar_t.
 */
template<typename Type>
struct is_space_noop {
    is_space_noop() = default;
    bool operator()(Type chr) { return false; }
};

/**
 * @brief Based implementation that uses the standard isspace or iswspace
 *      methods to determine if a space should be skipped or not.
 *
 * @tparam Type The character stream we are going to use, char or wchar_t.
 * @tparam IntType The value type expected, int or wint_t.
 */
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
/**
 * @brief char based space character check.
 *
 */
struct is_space : public is_space_base<char,int> {
    is_space() = default;
};
/**
 * @brief wchar_t based space character check.
 *
 */
struct is_wspace : public is_space_base<wchar_t, wint_t> {
    is_wspace() = default;
};
/**
 * @brief Variable length string of characters to compare with.
 *
 * @tparam Char The type of characters we are comparing, char or wchar_t
 * @tparam IntType The type of parameter type the operator() expects
 * @tparam Characters A class or struct that contains a static str string field
 */
template<typename Char, typename IntType, typename Characters>
struct skip_characters_base {
    bool operator()(IntType chr) {
        if constexpr (std::is_same_v<char, Char>) {
            return std::isspace(chr) || Characters::str.find(chr) != Characters::str.npos;
        } else {
            if constexpr (std::is_same_v<wchar_t, Char>) {
                return std::iswspace(chr) || Characters::str.find(chr) != Characters::str.npos;
            } else {
                // #error "Incorrect character type, only char or wchar_t are valid types "
                throw std::runtime_error(std::string("Unknown character type: ") + std::string(typeid(Char).name()));
            }
        }
    }
};
template<typename Characters>
struct skip_characters : skip_characters_base<char, int, Characters> {
};
template<typename Characters>
struct skip_wcharacters : skip_characters_base<wchar_t, wint_t, Characters> {
};
template<typename Characters>
struct skip_chars {
    std::string characters;
    skip_chars() : characters(Characters::str) {}
    bool operator()(int chr) {
        return std::isspace(chr) || characters.find(chr) != characters.npos;
    }
};
/**
 * @brief variable length character check method used to determine if a given
 *      character should be skipped or not.
 *
 * @tparam Type The character stream we are going to use, char or wchar_t.
 * @tparam IntType The value type expected, int or wint_t.
 * @tparam Chars Variable length of characters that should be skipped.
 */
template<typename Type, typename IntType, Type... Chars>
struct is_space_or_base {
    // is_space_or_base() = default;
    bool any_of(IntType chr, Type check) {
        return chr == check;
    }

    template<typename... Rest>
    bool any_of(IntType chr, Type check, Rest... rest) {
        return chr == check || any_of(chr, rest...);
    }

    bool operator()(IntType chr) {
        if constexpr (std::is_same_v<char, Type>) {
            return std::isspace(chr) || any_of(chr, Chars...);
        } else {
            if constexpr (std::is_same_v<wchar_t, Type>) {
                return std::iswspace(chr) || any_of(chr, Chars...);
            } else {
                // #error "Incorrect character type, only char or wchar_t are valid types "
                throw std::runtime_error(std::string("Unknown character type: ") + std::string(typeid(Type).name()));
            }
        }
    }
};
/**
 * @brief Variable length character skipping for char input stream.
 *
 * @tparam Chars Variable length char characters that should be skipped.
 */
template<char... Chars>
struct is_space_or : public is_space_or_base<char, int,Chars...> {
};
/**
 * @brief Variable length character skipping for wchar_t input stream.
 *
 * @tparam Chars Variable length wchar_t characters that should be skipped.
 */
template<wchar_t... Chars>
struct is_wspace_or : public is_space_or_base<wchar_t, wint_t,Chars...> {
};
/**
 * @brief Used to skip zero or more characters using the passed IsSpace
 *      struct.
 *
 * @tparam Char The character stream we are going to use, char or wchar_t.
 * @tparam IsSpace The space skipping struct used to check if a space should be skipped
 */
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
/**
 * @brief Used to determine if current character in the input stream is the
 *      expected character.  In this case, it will always return true.
 *
 * @tparam Char The character stream we are going to use, char or wchar_t.
 */
template<typename Char>
struct is_character_noop {
    bool operator()(std::basic_istream<Char> & in) {
        return true;
    }
};

/**
 * @brief Used to determine if the current character in the input stream is the
 *      expected character.  In this case, it will determine if the passed
 *      character if part of the passed variable length Chars.
 *
 * @tparam Char The character stream we are going to use, char or wchar_t.
 * @tparam Chars Variable length of expected characters.
 */
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

/**
 * @brief Used to determine if the current character in the input stream is the
 *      expected character.  In this case, it will return true for every other
 *      characters processed.  This was created to handle a unique issue with
 *      the data loader template class.
 *
 * @todo confirm that the above statement is true.
 *
 * @tparam Char The character stream we are going to use, char or wchar_t.
 */
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
