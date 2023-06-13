/**
 * @file tuple_loader.h
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This includes a loader that will load values into a tuple
 * @version 0.2
 * @date 2023-03-28
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#ifndef __TUPLE_LOADER_H__
#define __TUPLE_LOADER_H__

#include <tuple>

#include "checkers.h"

namespace valhalla {
    namespace utils {
        namespace loaders {
            namespace tuple {
                /**
                 * @brief This loader is used to load a tuple of three distinct entries.
                 *        The user will provide the type of characters that will be loaded
                 *        in each of the three entries of the tuple.  The tuple will be
                 *        surrounded by the OpenChar and CloseChar.  It uses the IsSpace
                 *        to skip Char that are considered spaces.  For example,
                 *
                 *          (1, 2, 3)
                 *
                 *        We can define the three entries as int where '(' is the open
                 *        character and ')' is the closing character.  The characters ','
                 *        and ' ' are considered space like characters.  The above can
                 *        then define a tupleTripleLoader as follows:
                 *
                 *          tupleTripleLoader<
                 *              int,
                 *              int,
                 *              int,
                 *              char,
                 *              '(',
                 *              ')',
                 *              valhalla::utils::checkers::is_space_or<','>
                 *          > loader(tuple);
                 *          in >> loader;
                 *
                 * @tparam TypeOne The type of the first entry in the tuple
                 * @tparam TypeTwo The type of the second entry in the tuple
                 * @tparam TypeThree The type of the third entry in the tuple
                 * @tparam Char The type of input, char or wchar_t
                 * @tparam OpenChar The Char used on the left of the defined tuple
                 * @tparam CloseChar The Char used on the right of the defined tuple
                 * @tparam IsSpace This is used to skip space like characters
                 */
                template<
                    typename TypeOne,
                    typename TypeTwo,
                    typename TypeThree,
                    typename Char = char,
                    Char OpenChar = '(',
                    Char CloseChar = ')',
                    typename IsSpace = valhalla::utils::checkers::is_space>
                class tupleTripletLoader {
                    std::tuple<TypeOne,TypeTwo,TypeThree> & m_data;
                    ::valhalla::utils::checkers::skip_spaces<Char, IsSpace> skipSpace;
                public:
                    tupleTripletLoader() = default;
                    tupleTripletLoader(std::tuple<TypeOne,TypeTwo,TypeThree> & data) : m_data(data) {}

                    friend std::basic_istream<Char> & operator>>(std::basic_istream<Char> & in, tupleTripletLoader & loader) {
                        loader.skipSpace(in); // skip space characters
                        if (static_cast<Char>(in.peek()) == OpenChar) {
                            in.get(); // read the open character
                            loader.skipSpace(in); // skip space characters
                            while (static_cast<Char>(in.peek()) != CloseChar) {
                                TypeOne value_one;
                                TypeTwo value_two;
                                TypeThree value_three;
                                in >> value_one; loader.skipSpace(in);
                                in >> value_two; loader.skipSpace(in);
                                in >> value_three; loader.skipSpace(in);
                                loader.m_data = std::make_tuple( value_one, value_two, value_three ); // set the read value in the tuple
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

                /**
                 * @brief This template will be used to load a standard tuple instance that can
                 *        create a tuple type with any amount of types.  The user will provide
                 *        the type of characters that will be loaded using the Loader type.  This
                 *        is a user defined type that will load the individual entries of the tuple
                 *        and will also implement the >> operator used to load the entries of the
                 *        TupleType.  This will then be assigned to the passed entry to this
                 *        template.  The tuple will be surrounded by the OpenChar and CloseChar.
                 *        It uses the IsSpace to skip Char that are considered spaces.  For example,
                 *
                 *          (1, 2, 3, Loader, 'A')
                 *
                 *        We can define the five entries as int, int, int, string and char where '('
                 *        is the open character and ')' is the closing character.  The characters ',',
                 *        '\'' and ' ' are considered space like characters.  The above can
                 *        then define a tupleLoader as follows:
                 *
                 *          tupleLoader<
                 *              std::tuple<int,int,int,std::string,char>,
                 *              DataLoader,
                 *              char,
                 *              '(',
                 *              ')',
                 *              valhalla::utils::checkers::is_space
                 *          > loader(tuple);
                 *          in >> loader;
                 *
                 *        The DataLoader will define the >> operator that will be used to load the
                 *        tuple and assign it to this template tuple instance.  It could then look like:
                 *
                 *        class DataLoader {
                 *          std::tuple<int,int,int,std::string::char> & m_tuple;
                 *        public:
                 *          DataLoader() = default;
                 *          DataLoader(std::tuple<int,int,int,std::string::char> & tuple) : m_tuple(tuple) {}
                 *
                 *          friend std::istream & operator>>(std::istream & in, DataLoader & loader) {
                 *            int, x, y, z,
                 *            std::string name;
                 *            char type;
                 *
                 *            ::valhalla::utils::checkers::skip_spaces<char, valhalla::utils::checkers::is_space_or<',','\''>> skipSpace;
                 *
                 *            skipSpace(in); // skip space characters
                 *            in >> x; skipSpace(in);
                 *            in >> y; skipSpace(in);
                 *            in >> z; skipSpace(in);
                 *            in >> name; skipSpace(in);
                 *            in >> type; skipSpace(in);
                 *
                 *            loader.m_tuple = std::make_tuple<int,int,int,std::string,char>(x,y,z,name,type);
                 *
                 *            return in;
                 *          }
                 *        };
                 *
                 * @tparam TupleType Type of tuple that is being loaded
                 * @tparam Loader This is used to load the tuple and used to assign the loaded data
                 * @tparam Char Char The type of input, char or wchar_t
                 * @tparam OpenChar The Char used on the left of the defined tuple
                 * @tparam CloseChar The Char used on the right of the defined tuple
                 * @tparam IsSpace This is used to skip space like characters
                 */
                template<
                    typename TupleType,
                    typename Loader,
                    typename Char = char,
                    Char OpenChar = '(',
                    Char CloseChar = ')',
                    typename IsSpace = valhalla::utils::checkers::is_space
                >
                class tupleLoader {
                    TupleType & m_tuple;
                    ::valhalla::utils::checkers::skip_spaces<Char, IsSpace> skipSpace;
                public:
                    tupleLoader() = default;
                    tupleLoader(TupleType & data) : m_tuple(data) {}

                    friend std::basic_istream<Char> & operator>>(std::basic_istream<Char> & in, tupleLoader & loader) {
                        loader.skipSpace(in); // skip space characters
                        if (static_cast<Char>(in.peek()) == OpenChar) {
                            in.get(); // read the open character
                            loader.skipSpace(in); // skip space characters
                            while (static_cast<Char>(in.peek()) != CloseChar) {
                                Loader tuple(loader.m_tuple); // create an instance of the loader instance
                                in >> tuple; // read the entries of the tuple
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
