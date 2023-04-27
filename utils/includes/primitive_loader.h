/**
 * @file primitive_loader.h
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains different templates that can be used to load primitive values
 * @version 0.1
 * @date 2023-04-14
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#ifndef __PRIMITIVE_LOADER_H__
#define __PRIMITIVE_LOADER_H__

#include <istream>
#include <iostream>
#include <vector>

#include "checkers.h"

namespace valhalla {
    namespace utils {
        namespace loaders {
            namespace primitive {
                /**
                 * @brief This loader can be used to load primitive types values that can be
                 *        surrounded by space type characters.  This template removes the 
                 *        need to manage space type characters.  It performs that task for
                 *        you by defining the IsSpace implementation.  The requirement is
                 *        that the primitive types will work with the >> operator.  This
                 *        implementation also provides the ability to reuse this to load
                 *        value for other similar input types.  For example:
                 * 
                 *          int age, length;
                 *          primitiveLoader<int> loader(&age);
                 *          in >> loader;
                 *          loader.set_reference(&length);
                 *          in >> leader;
                 * 
                 *       The value of age and length will then be populated with its
                 *       respective value read from the 'in' istream.
                 * 
                 * @tparam E The type of the instance that will be read into.
                 * @tparam Char The type of input stream used, char or wchar_t
                 * @tparam IsSpace The class that is used to skip spaces in the input
                 */
                template<
                    typename E,
                    typename Char = char,
                    typename IsSpace = valhalla::utils::checkers::is_space
                >
                class primitiveLoader {
                    E * m_value;
                    ::valhalla::utils::checkers::skip_spaces<Char, IsSpace> skipSpace;
                public:
                    using value_type = E;

                    primitiveLoader() = default;
                    primitiveLoader(E * value) : m_value(value) {}

                    void set_reference(E * value) { m_value = value; } 
                    
                    friend std::basic_istream<Char> & operator>>(std::basic_istream<Char> & in, primitiveLoader & loader) {
                        loader.skipSpace(in);
                        // The following could be used by it is too verbose while the latter is better and cleaner
                        // primitiveLoader<E,Char,IsSpace>::value_type & m_value = *(loader.m_value);
                        E & m_value = *(loader.m_value);
                        in >> m_value;
                        loader.skipSpace(in);                        
                        return in;
                    }
                };
            }
        }
    }
}

#endif
