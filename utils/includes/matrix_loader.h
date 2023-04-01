/**
 * @file matrix_loader.h
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains a template implementation of a matrix loader
 * @version 0.1
 * @date 2023-03-08
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#ifndef __MATRIX_LOADER_H__
#define __MATRIX_LOADER_H__

#include "vector_loader.h"
#include "checkers.h"

using namespace valhalla::utils::loaders::vectors;

namespace valhalla {
    namespace utils {
        namespace loaders {
            namespace matrix {

                /**
                 * @brief This class can be used to load a matrix of values into a matrix structure.  The
                 *      instance will use the passed open and closed character that are used to delimit
                 *      the matrix.  It will then add the entries to the passed matrix.  The expected
                 *      format of the matrix will contain the open character and close character on a
                 *      single line.  While each row will contain the entries to that given row of the
                 *      matrix surrounded by the open and close character.  For example
                 *
                 *      [
                 *      [1 2 3 4]
                 *      [5 6 7 8]
                 *      [9 10 11 12]
                 *      [13 14 15 16]
                 *      ]
                 *
                 *      The above matrix used the '[' as the open character and the ']' as the close
                 *      character.  The entries in this case is a numeric type.  Note that the open
                 *      character is at the beginning of the line and the close character is at the
                 *      end of the line for each row.
                 *
                 *      The class expects a struct or class that is used to skip space type characters
                 *      by implementing the bool operator()(std::basic_stream<Char> &) operator.
                 *
                 * @tparam E The type of entries to be added to the matrix
                 * @tparam Container The type of row container that will hold the entries
                 * @tparam Matrix The type of matrix that will hold the entries of Container row types
                 * @tparam Char The unit type of input we are processing, char or wchar_t
                 * @tparam IsSpace The struct or class used to skip space type unit types
                 * @tparam VectorLoader A Loader class that is used to load each row of entries of type E
                 */
                template<
                    typename E,
                    typename Container = std::vector<E>,
                    typename Matrix = std::vector<std::vector<E>>,
                    typename Char = char,
                    typename IsSpace = valhalla::utils::checkers::is_space,
                    typename VectorLoader = valhalla::utils::loaders::vectors::vectorLoader<E, Container, Char, IsSpace>
                >
                class matrixLoader {
                    Char m_open, m_close;
                    Matrix & m_container;
                    ::valhalla::utils::checkers::skip_spaces<Char, IsSpace> m_skipSpace;
                public:
                    using container = Container;

                    matrixLoader(Matrix & container, Char open = '[', Char close = ']') : m_container(container), m_open(open), m_close(close) {}

                    friend std::basic_istream<Char>& operator>>(std::basic_istream<Char>& in, matrixLoader & loader) {
                        loader.m_skipSpace(in); // skip space characters
                        // confirm that the first character is the open character
                        if (static_cast<Char>(in.peek()) == loader.m_open) {
                            in.get(); // read the open character
                            loader.m_skipSpace(in); // skip space characters
                            while (static_cast<char>(in.peek()) != loader.m_close) {
                                loader.m_container.push_back(Container()); // create a Container and add it to the matrix
                                Container & values = loader.m_container.back(); // get a reference to the newly created Container
                                VectorLoader vecLoader(values, loader.m_open, loader.m_close);
                                in >> vecLoader; // read the current line of entries into the created Container instance
                                loader.m_skipSpace(in); // skip space characters
                            } // while
                            in.get(); // read the close character
                            loader.m_skipSpace(in); // skip space characters
                        } else {
                            throw std::runtime_error("An invalid matrix format was passed");
                        } // else

                        return in;
                    }
                };
            }
        }
    }
}

#endif
