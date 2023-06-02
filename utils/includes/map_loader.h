/**
 * @file map_loader.h
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains a template implementation of a map loader
 * @version 0.1
 * @date 2023-06-01
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#ifndef __MAP_LOADER_H__
#define __MAP_LOADER_H__

#include <map>

#include "checkers.h"

namespace valhalla {
    namespace utils {
        namespace loaders {
            namespace map {
                /**
                 * @brief This will load entries to a map type container using a basic_istream
                 *      input stream.  It has the ability to load any key/value types that implement
                 *      the >> operator.  For example, we have the following text that we want to load
                 *      into a map.
                 *
                 *          { 'A' : 'B', 'C' : 'D' }
                 *
                 *      This can then be loaded using the following definition:
                 *
                 *      std::map<char,char> data;
                 *      mapLoader<
                 *          char,
                 *          char,
                 *          std::map<char,char>,
                 *          '{',
                 *          '}',
                 *          ':',
                 *          valhalla::utils::checkes::is_space_or<','>
                 *      > loader(data);
                 *      in >> data;
                 *
                 * @tparam Key The key type of the map container
                 * @tparam Value The value type of the map container
                 * @tparam Map The map type of the map
                 * @tparam Char The unit type of input we are processing, char or w_char_t
                 * @tparam openChar The character used to enclose the left side of the pair. default {
                 * @tparam closeChar The character used to enclose the right side of the pair, default }
                 * @tparam dividerChar The character used to seperate the Key/Value pair, default :
                 * @tparam IsSpace The struct or class used to skip space type unit types
                 */
                template<
                    typename Key,
                    typename Value,
                    typename Map = std::map<Key,Value>,
                    typename Char = char,
                    Char openChar = '{',
                    Char closeChar = '}',
                    Char dividerChar = ':',
                    typename IsSpace = valhalla::utils::checkers::is_space
                >
                class mapLoader {
                    Char m_open = openChar, m_close = closeChar, m_divider = dividerChar;
                    Map & m_map;
                    ::valhalla::utils::checkers::skip_spaces<Char, IsSpace> m_skipSpace;
                public:
                    using container = Map;

                    mapLoader(Map & dict) : m_map(dict) {}

                    friend std::basic_istream<Char> & operator>>(std::basic_istream<Char> & in, mapLoader & loader) {
                        loader.m_skipSpace(in); // skip spaces
                        if (static_cast<Char>(in.peek()) == loader.m_open) {
                            in.get();  // read open character
                            loader.m_skipSpace(in); // skip space characters
                            while (static_cast<Char>(in.peek()) != loader.m_close) {
                                Key key;
                                Value value;
                                loader.m_skipSpace(in); // skip space characters
                                in >> key;
                                loader.m_skipSpace(in); // skip space characters
                                if (static_cast<Char>(in.peek()) != loader.m_divider) {
                                    throw std::runtime_error("An invalid matrix format was passed");
                                } // if
                                in.get(); // read divider character
                                loader.m_skipSpace(in); // skip space characters
                                in >> value;
                                loader.m_map[key] = value;
                                loader.m_skipSpace(in); // skip space characters
                            } // while
                            in.get();  // read close character
                            loader.m_skipSpace(in);
                            return in;
                        }
                        throw std::runtime_error("An invalid map format was passed");
                    }
                };
            }
        }
    }
}
#endif