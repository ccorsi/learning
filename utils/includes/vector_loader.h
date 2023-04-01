/**
 * @file vloader.h
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This include file contains a loader that will load values into a vector
 * @version 0.1
 * @date 2023-03-08
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#ifndef __VECTOR_LOADER_H__
#define __VECTOR_LOADER_H__

#include <istream>
#include <vector>

#include "checkers.h"

namespace valhalla {
    namespace utils {
        namespace loaders {
            namespace vectors {
                /**
                 * @brief This template is used to load a vector from an istream that is read from
                 *      a single line input stream.  The vector will be wrapped by the passed open
                 *      and close character.  For example:
                 *
                 *          [1 2 3 4 5]
                 *
                 *      Note that this class expects the open character is at the beginning of the
                 *      line.
                 *
                 * @tparam E The type entries that will be loaded in the container
                 * @tparam Container The container that will be used to add the entries to
                 * @tparam Char The type of character being read, char or wchar_t
                 * @tparam IsSpace Struct or Class that expects an I type passed and returns a bool
                 */
                template<typename E,
                         typename Container = std::vector<E>,
                         typename Char = char,
                         typename IsSpace = valhalla::utils::checkers::is_space>
                class vectorLoader {
                    Container & m_container;
                    Char m_open, m_close;
                    ::valhalla::utils::checkers::skip_spaces<Char, IsSpace> skipSpace;
                public:
                    vectorLoader() = default;
                    vectorLoader(Container & container, Char open, Char close) : m_container(container), m_open(open), m_close(close) {}

                    friend std::basic_istream<Char> & operator>>(std::basic_istream<Char> & in, vectorLoader & loader) {
                        loader.skipSpace(in); // skip space characters
                        if (static_cast<Char>(in.peek()) == loader.m_open) {
                            in.get(); // read the open character
                            loader.skipSpace(in); // skip space characters
                            while (static_cast<Char>(in.peek()) != loader.m_close) {
                                E value;
                                in >> value;
                                loader.m_container.push_back(value); // insert the read value into the container
                                loader.skipSpace(in); // skip space characters
                            } // while
                            in.get(); // read the close character
                            loader.skipSpace(in); // skip space characters
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
