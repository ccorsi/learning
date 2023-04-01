/**
 * @file set_loader.h
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains template set loaders
 * @version 0.1
 * @date 2023-03-08
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#ifndef __SET_LOADER_H__
#define __SET_LOADER_H__

#include <istream>
#include <set>

#include "checkers.h"

namespace valhalla {
    namespace utils {
        namespace loaders {
            namespace set {
                /**
                 * @brief This template will be able to load entries within a set container.  The
                 *      class will assume that all of the entries are located on a single line.
                 *      The class will assume that the entries are surrounded by an open and close
                 *      delimiter like { and }.
                 *
                 * @tparam E The type of values being loaded and store in the set
                 * @tparam Set The type of set that the entries will be inserted into
                 * @tparam Char The type of input characters that are being read, char or wchar_t
                 * @tparam IsSpace This is used to skip space type characters
                 */
                template<
                    typename E,
                    typename Set = std::set<E>,
                    typename Char = char,
                    typename IsSpace = valhalla::utils::checkers::is_space
                >
                class setLoader {
                    Set & m_set;
                    Char m_open, m_close;
                    ::valhalla::utils::checkers::skip_spaces<Char, IsSpace> skipSpace;
                public:
                    setLoader() = default;
                    setLoader(Set & set, Char open = '{', Char close = '}') : m_set(set), m_open(open), m_close(close) {}

                    friend std::basic_istream<Char> & operator>>(std::basic_istream<Char> & in, setLoader & loader) {
                        loader.skipSpace(in); // skip space characters
                        if (static_cast<Char>(in.peek()) == loader.m_open) {
                            in.get(); // read the open character
                            loader.skipSpace(in); // skip space characters
                            while (static_cast<Char>(in.peek()) != loader.m_close) {
                                E value;
                                in >> value;
                                loader.m_set.insert(value); // insert the read value into the container
                                loader.skipSpace(in); // skip space characters
                            } // while
                            in.get(); // read the close character and the end of line
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
