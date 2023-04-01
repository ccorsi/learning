/**
 * @file loader.h
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This include contains classes that can be used to load classes from a file
 * @version 0.1
 * @date 2023-02-16
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#ifndef __LOADER_H__
#define __LOADER_H__

#include <istream>
#include <fstream>
#include <vector>
#include <string>
#include <stdexcept>

#include "debug.h"

namespace valhalla {
    namespace utils {
        namespace loaders {
            /**
             * @brief The class is used to load instances of the define type T.  The
             *      type T is expected to have an associated operator>> implemented and
             *      a default constructor.  The class will load an instance of the type
             *      T and add it to a vector container.  It then will return an instance
             *      of the container.
             *
             * @tparam T The type that will be read and added to the returning container
             */
            template<typename T>
            class Loader {
                std::vector<T> process(std::istream & is) {
                    std::vector<T> container;

                    // NOTE: I had to call peek instead of eof to determine if I reached the end of file.
                    while (is.good() && is.peek() != -1) {
                        T e; // this will insure that we don't reuse the same instance
                        is >> e;
                        container.push_back(e);
                    } // while

                    return container;
                }
            public:
                Loader() = default;

                /**
                 * @brief Load instances of type T from the passed filename.  It is
                 *      expected that the passed filename exists.  If it doesn't the
                 *      operator will return an empty container.
                 *
                 * @param filename The name of the file to load instances from
                 *
                 * @return std::vector<T> container containing instance of load type T
                 */
                std::vector<T> operator()(std::string filename) {
                    std::ifstream is(filename);

                    // check if opened file successfully
                    if (is.good()) {
                        return process(is);
                    } else {
                        std::string msg = std::string("Unable to open file ") + filename;
                        DEBUGMSHG(msg);
                        std::vector<T> container;
                        return container;
                    } // else
                }

                /**
                 * @brief Load instances of type T from the passed filename.  It is
                 *      expected that the passed filename exists.  If it doesn't, the
                 *      operator will return an empty container.
                 *
                 * @param filename The name of the file to load instances from
                 *
                 * @return std::vector<T> container containing instance of load type T
                 */
                std::vector<T> operator()(char *filename) {
                    std::ifstream is(filename);

                    // check if opened file successfully
                    if (is.good()) {
                        return process(is);
                    } else {
                        std::string msg = std::string("Unable to open file ") + filename;
                        DEBUGMSHG(msg);
                        std::vector<T> container;
                        return container;
                    } // else
                }

                /**
                 * @brief Load instances of type T from the passed istream.  It is
                 *      expected that the passed istream is ready to read instances
                 *      of type T.  If it isn't ready to read instances of type T,
                 *      the operator will return an empty container.
                 *
                 * @param is The istream used to load instance from
                 *
                 * @return std::vector<T> container containing instance of load type T
                 */
                std::vector<T> operator()(std::istream & is) {
                    // check if opened file successfully
                    if (is.good()) {
                        return process(is);
                    } else {
                        DEBUGMSHG("Unable to use passed istream");
                        std::vector<T> container;
                        return container;
                    } // else
                }

                /**
                 * @brief Load instances of type T from the passed istream.  It is
                 *      expected that the passed ifstream is ready to read instances
                 *      of type T.  If it isn't ready to read instances of type T,
                 *      the operator will return an empty container.
                 *
                 * @param is The ifstream used to load instance from
                 *
                 * @return std::vector<T> container containing instance of load type T
                 */
                std::vector<T> operator()(std::ifstream & is) {
                    // check if opened file successfully
                    if (is.good()) {
                        return process(is);
                    } else {
                        DEBUGMSHG("Unable to use passed istream");
                        std::vector<T> container;
                        return container;
                    } // else
                }
            };

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
             * @deprecated Use ::valhalla::utils::loaders::vectors::vectorLoader instead
             */
            template<typename E, typename Container = std::vector<E>>
            class vectorLoader {
                char m_open, m_close;
                Container & m_container;
            public:
                vectorLoader() = default;
                vectorLoader(char open, char close, Container &container) : m_open(open), m_close(close), m_container(container) {}

                friend std::istream& operator>>(std::istream& in, vectorLoader & loader) {
                    if (static_cast<char>(in.peek()) == loader.m_open) {
                        char chr;
                        in >> chr; // read the open character
                        while (static_cast<char>(in.peek()) != loader.m_close) {
                            E value;
                            in >> value;
                            loader.m_container.push_back(value); // insert the read value into the container
                        } // while
                        std::string line;
                        std::getline(in, line); // read the close character and the end of line
                    } else {
                        throw std::runtime_error("Invalid input format was encounter"); // throw a runtime exception if an invalid format was passed
                    } // else

                    return in;
                }
            };

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
             * @tparam E The type of entries to be added to the matrix
             * @tparam Container The type of row container that will hold the entries
             * @tparam Matrix The type of matrix that will hold the entries of Container row types
             * @deprecated Use ::valhalla::utils::loaders::matrix::matrixLoader instead
             */
            template<
                typename E,
                typename Container = std::vector<E>,
                typename Matrix = std::vector<std::vector<E>>
            >
            class matrixLoader {
                char m_open, m_close;
                Matrix & m_container;
            public:
                using container = Container;

                matrixLoader(Matrix & container, char open = '[', char close = ']') : m_container(container), m_open(open), m_close(close) {}

                friend std::istream& operator>>(std::istream& in, matrixLoader & loader) {
                    // confirm that the first character is the open character
                    if (static_cast<char>(in.peek()) == loader.m_open) {
                        std::string line;
                        std::getline(in, line); // read the open character and the end of line
                        while (static_cast<char>(in.peek()) != loader.m_close) {
                            loader.m_container.push_back(Container()); // create a Container and add it to the matrix
                            Container & values = loader.m_container.back(); // get a reference to the newly created Container
                            vectorLoader<E> vecLoader(loader.m_open, loader.m_close, values);
                            in >> vecLoader; // read the current line of entries into the created Container instance
                        } // while
                        std::getline(in, line); // read the close character and the end of line
                    } else {
                        throw std::runtime_error("An invalid matrix format was passed");
                    } // else

                    return in;
                }
            };
        }
    }
}

#endif
