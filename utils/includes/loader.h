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
                 *      expected that the passed isteam is ready to read instances
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
            };
        }
    }
}

#endif
