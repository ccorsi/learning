/**
 * @file pair_loader.h
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains a template class that can be used to load a pair instance from
 *        an istream.
 * @version 0.1
 * @date 2023-03-15
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#ifndef __PAIR_LOADER_H__
#define __PAIR_LOADER_H__

#include <utility>

#include "checkers.h"

namespace valhalla {
    namespace utils {
        namespace loaders {
            namespace pairs {
                /**
                 * @brief This pair template loader can be used to load a pair instance from
                 *      a istream.  It has the ability to load the different types of instance
                 *      for the first and second field of the pair.  The class will assume that
                 *      the pair is formatted as follows:
                 *
                 *          (1,2)
                 *
                 *      It will then look for the ( character and then the ) character after
                 *      reading the data.  Note that the user is not restricted to using the
                 *      ( and ) characters to enclose the pair with.
                 *
                 * @tparam leftType The type of instance that is being loaded into the first field
                 * @tparam rightType The type of instance that is being loaded into the second field
                 * @tparam Char The type of istream that will be used to load the pair values, default char
                 * @tparam openChar The character used to enclose the left side of the pair. default (
                 * @tparam closeChar The character used to enclose the right side of the pair, default )
                 * @tparam IsSpace The operator used to skip space like characters, default is_space
                 */
                template<
                    typename leftType,
                    typename rightType,
                    typename Char = char,
                    Char openChar = '(',
                    Char closeChar = ')',
                    typename IsSpace = valhalla::utils::checkers::is_space
                >
                class pairLoader {
                    std::pair<leftType,rightType> & m_pair;
                    Char m_open = openChar, m_close = closeChar;
                    IsSpace isSpace;
                public:
                    pairLoader() = default;
                    pairLoader(std::pair<leftType,rightType> & p) : m_pair(p) {}

                    friend std::basic_istream<Char> & operator>>(std::basic_istream<Char> & in, pairLoader & loader) {
                        while (loader.isSpace(in.peek())) in.get(); // skip space characters
                        if (static_cast<Char>(in.peek()) == loader.m_open) {
                            Char chr;
                            in >> chr; // read the open character
                            while (loader.isSpace(in.peek())) in.get(); // skip space characters
                            while (static_cast<Char>(in.peek()) != loader.m_close) {
                                in >> loader.m_pair.first;
                                while (loader.isSpace(in.peek())) in.get(); // skip space characters
                                in >> loader.m_pair.second;
                                while (loader.isSpace(in.peek())) in.get(); // skip space characters
                            } // while
                            std::basic_string<Char> line;
                            std::getline(in, line); // read the close character and the end of line
                        } else {
                            throw std::runtime_error("Invalid input format was encounter"); // throw a runtime exception if an invalid format was passed
                        } // else

                        return in;
                    }
                };
            }
        }
    }
}

#endif
