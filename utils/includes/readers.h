/**
 * @file readers.h
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This file contains different reader implementations can be used throughout
 *        the different test implementations.
 * @version 0.1
 * @date 2025-02-04
 *
 * @copyright Copyright (c) 2025 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#ifndef __READERS_H__
#define __READERS_H__

#include <istream>
#include <string>
#include <vector>

#include "loaders.h"

namespace valhalla
{

namespace utils
{

namespace readers
{

template<typename Char, Char chr>
struct BasicStringReader {
    std::basic_istream<Char> & operator()(std::basic_istream<Char> & in, std::basic_string<Char> & str, int state) {
        while (static_cast<Char>(in.peek()) != chr) {
            str += static_cast<Char>(in.get());
        }

        return in;
    }
};

typedef BasicStringReader<char, '"'> StringReader;
typedef BasicStringReader<wchar_t, L'"'> WStringReader;

template<typename Type, typename Char>
struct SimpleVectorReader {
    std::basic_istream<Char> & operator()(std::basic_istream<Char> & in, std::vector<Type> & vec, int state) {
        Type value;
        // Push a new instance to the vector
        vec.push_back(value);
        // Get a reference to the newly push element
        Type & data = vec.back();

        // Populate the newly added vector element and return
        valhalla::utils::loaders::loader::v6::dataLoader<Type,Char> PrimitiveLoader(data);
        return in >> PrimitiveLoader;
    }
};

template<typename T>
struct VectorReader : SimpleVectorReader<T, char> {};

template<typename T>
struct WVectorReader : SimpleVectorReader<T, wchar_t> {};

template<typename Type, typename Char>
struct BasicSetReader {
    std::basic_istream<Char> & operator()(std::basic_istream<Char> & in, std::set<Type> & set, int state) {
        Type value;

        // Populate the set element
        valhalla::utils::loaders::loader::v6::dataLoader<Type,Char> SetLoader(value);
        in >> SetLoader;

        // add the populated value
        set.insert(value);

        return in;
    }
};

template<typename Type>
struct SetReader : BasicSetReader<Type, char> {};

template<typename Type>
struct WSetReader : BasicSetReader<Type, wchar_t> {};

} // namespace readers

} // namespace utils

} // namespace valhalla

#endif
