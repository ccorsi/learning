/**
 * @file data_loader.h
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains a general loader loader template class used to load loader into an instance
 *      using a basic_istream instance.
 * @version 0.1
 * @date 2023-06-05
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#ifndef __DATA_LOADER_H__
#define __DATA_LOADER_H__

#include <iostream>

#include "checkers.h"

namespace valhalla {
    namespace utils {
        namespace loaders {
            namespace loader {
                namespace v1 {
                    /**
                     * @brief This is a template Reader class that can be used to facilitate the use of
                     *        the dataLoader template class to load values into a object.
                     *
                     * @tparam Type The type of the instance that will be loaded
                     * @tparam Char The type of character that will be read, char or wchar_t
                     * @tparam IsSpace The class that will be used to skip space like characters
                     */
                    template<
                        typename Type,
                        typename Char = char,
                        typename IsSpace = valhalla::utils::checkers::is_space,
                        typename IsOpenChar = valhalla::utils::checkers::is_character_noop<Char>,
                        typename IsCloseChar = valhalla::utils::checkers::is_character_noop<Char>
                    >
                    class typeReader {
                        Type & m_value;
                    public:
                        typeReader() = default;
                        typeReader(Type & value) : m_value(value) {}

                        friend std::basic_istream<Char> & operator>>(std::basic_istream<Char> & in, typeReader & reader) {
                            valhalla::utils::checkers::skip_spaces<Char,IsSpace> skipSpace;
                            IsOpenChar isOpenChar;

                            skipSpace(in); // skip space-like characters
                            if (isOpenChar(in)) {
                                skipSpace(in); // skip space-like characters
                                in >> reader.m_value;
                                skipSpace(in); // skip space-like characters

                                IsCloseChar isCloseChar;
                                if (isCloseChar(in)) {
                                    skipSpace(in); // skip space-like characters
                                    return in;
                                } // if
                                throw std::runtime_error("Invalid input encountered for closed character - typeReader");
                            } // if

                            throw std::runtime_error("Invalid input encountered for open character - typeReader");
                        }
                    };

                    /**
                     * @brief This is a general loader loader template class that can be used to
                     *      populate a instance of type Type from a passed basic_istream.  It
                     *      will use the defined Reader type to load the instance.  The Char
                     *      will define what type of input stream will be used.  While the
                     *      OpenChar and CloseChar will define the characters that will wrap
                     *      the defined instance loader.  The IsSpace type is used to skip space
                     *      like characters the is processed from the input.
                     *
                     *      There is some requirements that need to be defined to be able to
                     *      correctly define an instance of this template.  The definition of
                     *      the Reader type requires that it defines a default constructor and
                     *      one that expects a reference of type Type.  Finally, this type
                     *      requires an implementation of the >> operator.
                     *
                     *      The other requirement is that the class definitions of the IsOpenChar
                     *      and IsCloseChar typename requires that it implements the operator()
                     *      the returns a bool and that expects a std::basic_istream<Char> reference.
                     *      This method will be used to determine if zero or more expected characters
                     *      are part of the basic_istream.  There is already an implementation that
                     *      can be used to determine if a given basic_istream contains the required
                     *      open and close character{s}.  The struct is
                     *      valhalla::utils::checkers::is_character<Char,Char...Chars>.
                     *
                     *      Lastly, the IsSpace typename is used to skip space like characters within
                     *      the passed basic_istream.
                     *
                     *      Let us now take an example of how this can be used.
                     *
                     * @tparam Type The object type that will be loaded
                     * @tparam Reader A class that is used to read the characters into a given Type instance
                     * @tparam Char The type of character trait that the basic_istream will be producing, char or wchar_t.
                     * @tparam IsOpenChar The class used to determine if the required open character{s} exists
                     * @tparam IsCloseChar The class used to determine if the required close character{s} exists
                     * @tparam IsSpace The class used to skip space type characters
                     */
                    template<
                        typename Type,
                        typename Reader,
                        typename Char,
                        typename IsOpenChar,
                        typename IsCloseChar,
                        typename IsSpace = ::valhalla::utils::checkers::is_space
                    >
                    class dataLoader {
                        Type & m_type;
                    public:
                        dataLoader() = default;
                        dataLoader(Type & type) : m_type(type) {}

                        friend std::basic_istream<Char> & operator>>(std::basic_istream<Char> & in, dataLoader & loader) {
                            valhalla::utils::checkers::skip_spaces<Char, IsSpace> skipSpace;
                            IsOpenChar isOpenChar;
                            IsCloseChar isCloseChar;

                            skipSpace(in); // skip space-like input
                            if (isOpenChar(in)) {
                                skipSpace(in); // skip space-like input

                                Reader reader(loader.m_type);
                                std::streamoff pos = in.tellg();
                                in >> reader;
                                if (in.tellg() == pos) {
                                    throw std::runtime_error("No input was processed");
                                } // if

                                skipSpace(in); // skip space-like input
                                if (isCloseChar(in)) {
                                    skipSpace(in); // skip space-like input
                                    return in;
                                } // if

                                throw std::runtime_error("Invalid input data encountered no close character found - dataLoader");
                            } // if

                            throw std::runtime_error("Invalid input data encountered no open character found - dataLoader");
                        }
                    };
                } // v1
                namespace v2 {
                    class State {
                        int m_state;
                        int m_states;
                    public:
                        State(const int states) : m_states(states), m_state(0) {
                            if (m_states < 1) {
                                throw std::runtime_error("Invalid states, has to be 1 or greater");
                            }
                        }

                        bool operator()() {
                            m_state++;
                            bool state = m_state != m_states;
                            m_state = m_state % m_states;
                            return state;
                        }

                        int state() { return m_state; }
                    };
                    /**
                     * @brief This is a helper class that can be used to load a particular type Type using a basic_istream.
                     *      The default implementation will expect the passed Type to implement that >> operator and the
                     *      default implementation of the () operator will return false.  This operator is used to determine
                     *      if more data needs to be processed to complete the populating of the instance.  The last entry
                     *      is the states.  This is used to inform the dateLoader how many fields are being loaded that will
                     *      be required to create an instance of type Type.  This is useful when each field is separated by
                     *      one or more space-like characters.  The dataLoader will skip these characters after reading
                     *      each field.
                     *
                     * @tparam Type The type of instance that will be populated using this Reader
                     * @tparam Char The type of input that will be processed, one of char or wchar_t
                     * @tparam states The states how many entries need to be read before completely populating Type instance, 1 or greater
                     */
                    template<
                        typename Type,
                        typename Char,
                        int states = 1
                    >
                    class dataReader {
                        Type & m_data;
                        State m_state;
                    protected:
                        Type & get_data() { return m_data; }
                        virtual std::basic_istream<Char> & load(std::basic_istream<Char> & in) = 0;
                    public:
                        dataReader() = default;
                        dataReader(Type & data) : m_data(data), m_state(states) {}

                        friend std::basic_istream<Char> & operator>>(std::basic_istream<Char> & in, dataReader & reader) {
                            return reader.load(in);
                        }

                        virtual bool operator()() { return m_state(); }

                        inline int state() { return m_state.state(); }
                    };

                    /**
                     * @brief The template class can be used to load any type of instance.  From a regular primitive type,
                     *      class type to a container and dictionary type instance.  It allows one to be able to determine
                     *      how the instance can be loaded using the Reader type definition.  The Reader type needs to be
                     *      able to define the >> operator as well as a () operator that returns a bool.  The first operator
                     *      is obvious but the second operator is used to determine if we've completed loading the object
                     *      of type Type.  This technique will allow one to create any type of Type that the loader can
                     *      populate.
                     *
                     * @tparam Type The type that will be populated
                     * @tparam Char The type of input used, char or wchar_t
                     * @tparam Reader The reader type that will be used to populate the type
                     * @tparam IsOpenChar The type used to determine if the open character was encountered
                     * @tparam IsCloseChar The type used to determine if the close character was encountered
                     * @tparam IsSpace The type used to skip space-like characters when processing the input stream
                     */
                    template<
                        typename Type,
                        typename Char = char,
                        typename Reader = dataReader<Type,Char>,
                        typename IsOpenChar = valhalla::utils::checkers::is_character_noop<Char>,
                        typename IsCloseChar = valhalla::utils::checkers::is_character_noop<Char>,
                        typename IsSpace = valhalla::utils::checkers::is_space
                    >
                    class dataLoader {
                        Type & m_type;
                    public:
                        dataLoader() = default;
                        dataLoader(Type & type) : m_type(type) {}

                        friend std::basic_istream<Char> & operator>>(std::basic_istream<Char> & in, dataLoader & dataloader) {
                            valhalla::utils::checkers::skip_spaces<Char, IsSpace> skipSpace;
                            IsOpenChar isOpenChar;
                            IsCloseChar isCloseChar;

                            skipSpace(in); // skip space-like input
                            if (isOpenChar(in)) {
                                skipSpace(in); // skip space-like input

                                Reader reader(dataloader.m_type);
                                while (isCloseChar(in) == false) {
                                    do {
                                        std::streamoff pos = in.tellg();
                                        in >> reader;
                                        if (in.tellg() == pos) {
                                            throw std::runtime_error("No input was processed");
                                        } // if
                                        skipSpace(in); // skip space-like input
                                    } while (reader());
                                } // while

                                skipSpace(in); // skip space-like input
                                return in;
                            } // if

                            throw std::runtime_error("Invalid input data encountered no open character found - dataLoader v2");
                        }
                    };
                } // v2
                namespace v3 {
                    class State {
                        int m_state;
                        int m_states;
                    public:
                        State(const int states) : m_states(states), m_state(0) {
                            if (m_states < 1) {
                                throw std::runtime_error("Invalid states, has to be 1 or greater");
                            }
                        }

                        bool operator()() {
                            m_state++;
                            bool state = m_state != m_states;
                            m_state = m_state % m_states;
                            return state;
                        }

                        int state() { return m_state; }
                    };
                    /**
                     * @brief A template class used to populate the passed type using the passed basic_istream.  It
                     *      implements the (std::basic_istream<Char>&, Type&, int) operator.
                     *
                     * @tparam Type The type that is being populated
                     * @tparam Char The input character trait that is being used, char or wchar_t
                     */
                    template<
                        typename Type,
                        typename Char
                    >
                    struct reader {
                        /**
                         * @brief The operator is used to read the data passed.  It expects a reference to the
                         *      instance that is being populated.  The passed state will provide details about
                         *      which field we are reading.  For instance, if we are populating a class that
                         *      contains n fields then this operator will be called n times with state 0 through
                         *      n - 1.  This information can then be used to correctly load the data into its
                         *      expected field type.  When state n - 1 was passed then we can instantiate the
                         *      passed type using the gathered parameter values.  The version will just expect
                         *      the Type to define the appropiate >> operator.
                         *
                         * @param in A reference to a basic_istream instance
                         * @param type The instance that will be assigned.
                         * @param state The current state of the input.
                         * @return std::basic_istream<Char>& The passed input stream used to read the data from
                         */
                        virtual std::basic_istream<Char> & operator()(std::basic_istream<Char> & in, Type & type, int state) {
                            return in >> type;
                        }
                    };
                    /**
                     * @brief This is a helper class that can be used to load a particular type Type using a basic_istream.
                     *      The default implementation will expect the passed Type to implement that >> operator and the
                     *      default implementation of the () operator will return false.  This operator is used to determine
                     *      if more data needs to be processed to complete the populating of the instance.  The last entry
                     *      is the states.  This is used to inform the dateLoader how many fields are being loaded that will
                     *      be required to create an instance of type Type.  This is useful when each field is separated by
                     *      one or more space-like characters.  The dataLoader will skip these characters after reading
                     *      each field.
                     *
                     * @tparam Type The type of instance that will be populated using this Reader
                     * @tparam Char The type of input that will be processed, one of char or wchar_t
                     * @tparam Reader The type that is used to actually read the data used to populate the Type instance
                     * @tparam states The states how many entries need to be read before completely populating Type instance, 1 or greater
                     */
                    template<
                        typename Type,
                        typename Char,
                        typename Reader = reader<Type,Char>,
                        int states = 1
                    >
                    class dataReader {
                        Type & m_data;
                        State m_state;
                        Reader m_reader;

                        std::basic_istream<Char> & load(std::basic_istream<Char> & in) { return m_reader(in, m_data, m_state.state()); }
                    public:
                        dataReader() = default;
                        dataReader(Type & data) : m_data(data), m_state(states) {}

                        friend std::basic_istream<Char> & operator>>(std::basic_istream<Char> & in, dataReader & reader) {
                            return reader.load(in);
                        }

                        bool operator()() { return m_state(); }

                        inline int state() { return m_state.state(); }
                    };

                    /**
                     * @brief The template class can be used to load any type of instance.  From a regular primitive type,
                     *      class type to a container and dictionary type instance.  It allows one to be able to determine
                     *      how the instance can be loaded using the Reader type definition.  The Reader type needs to be
                     *      able to define the >> operator as well as a () operator that returns a bool.  The first operator
                     *      is obvious but the second operator is used to determine if we've completed loading the object
                     *      of type Type.  This technique will allow one to create any type of Type that the loader can
                     *      populate.
                     *
                     * @tparam Type The type that will be populated
                     * @tparam Char The type of input used, char or wchar_t
                     * @tparam Reader The reader type that will be used to populate the type
                     * @tparam IsOpenChar The type used to determine if the open character was encountered
                     * @tparam IsCloseChar The type used to determine if the close character was encountered
                     * @tparam IsSpace The type used to skip space-like characters when processing the input stream
                     */
                    template<
                        typename Type,
                        typename Char = char,
                        typename Reader = dataReader<Type,Char>,
                        typename IsOpenChar = valhalla::utils::checkers::is_character_noop<Char>,
                        typename IsCloseChar = valhalla::utils::checkers::is_character_noop<Char>,
                        typename IsSpace = valhalla::utils::checkers::is_space
                    >
                    class dataLoader {
                        Type & m_type;
                    public:
                        dataLoader() = default;
                        dataLoader(Type & type) : m_type(type) {}

                        friend std::basic_istream<Char> & operator>>(std::basic_istream<Char> & in, dataLoader & dataloader) {
                            valhalla::utils::checkers::skip_spaces<Char, IsSpace> skipSpace;
                            IsOpenChar isOpenChar;
                            IsCloseChar isCloseChar;

                            skipSpace(in); // skip space-like input
                            if (isOpenChar(in)) {
                                skipSpace(in); // skip space-like input

                                Reader reader(dataloader.m_type);
                                while (isCloseChar(in) == false) {
                                    do {
                                        std::streamoff pos = in.tellg();
                                        in >> reader;
                                        if (in.tellg() == pos) {
                                            throw std::runtime_error("No input was processed");
                                        } // if
                                        skipSpace(in); // skip space-like input
                                    } while (reader());
                                } // while

                                skipSpace(in); // skip space-like input
                                return in;
                            } // if

                            throw std::runtime_error("Invalid input data encountered no open character found - dataLoader v3");
                        }
                    };
                } // v3
                namespace v4 {
                    class State {
                        int m_state;
                        int m_states;
                    public:
                        State(const int states) : m_states(states), m_state(0) {
                            if (m_states < 1) {
                                throw std::runtime_error("Invalid states, has to be 1 or greater");
                            }
                        }

                        bool operator()() {
                            m_state++;
                            bool state = m_state != m_states;
                            m_state = m_state % m_states;
                            return state;
                        }

                        int state() { return m_state; }
                    };
                    /**
                     * @brief A template class used to populate the passed type using the passed basic_istream.  It
                     *      implements the (std::basic_istream<Char>&, Type&, int) operator.
                     *
                     * @tparam Type The type that is being populated
                     * @tparam Char The input character trait that is being used, char or wchar_t
                     */
                    template<
                        typename Type,
                        typename Char
                    >
                    struct reader {
                        /**
                         * @brief The operator is used to read the data passed.  It expects a reference to the
                         *      instance that is being populated.  The passed state will provide details about
                         *      which field we are reading.  For instance, if we are populating a class that
                         *      contains n fields then this operator will be called n times with state 0 through
                         *      n - 1.  This information can then be used to correctly load the data into its
                         *      expected field type.  When state n - 1 was passed then we can instantiate the
                         *      passed type using the gathered parameter values.  The version will just expect
                         *      the Type to define the appropiate >> operator.
                         *
                         * @param in A reference to a basic_istream instance
                         * @param type The instance that will be assigned.
                         * @param state The current state of the input.
                         * @return std::basic_istream<Char>& The passed input stream used to read the data from
                         */
                        virtual std::basic_istream<Char> & operator()(std::basic_istream<Char> & in, Type & type, int state) {
                            return in >> type;
                        }
                    };
                    /**
                     * @brief This is a helper class that can be used to load a particular type Type using a basic_istream.
                     *      The default implementation will expect the passed Type to implement that >> operator and the
                     *      default implementation of the () operator will return false.  This operator is used to determine
                     *      if more data needs to be processed to complete the populating of the instance.  The last entry
                     *      is the states.  This is used to inform the dateLoader how many fields are being loaded that will
                     *      be required to create an instance of type Type.  This is useful when each field is separated by
                     *      one or more space-like characters.  The dataLoader will skip these characters after reading
                     *      each field.
                     *
                     * @tparam Type The type of instance that will be populated using this Reader
                     * @tparam Char The type of input that will be processed, one of char or wchar_t
                     * @tparam Reader The type that is used to actually read the data used to populate the Type instance
                     * @tparam states The states how many entries need to be read before completely populating Type instance, 1 or greater
                     */
                    template<
                        typename Type,
                        typename Char,
                        typename Reader = reader<Type,Char>,
                        int states = 1
                    >
                    class dataReader {
                        Type & m_data;
                        State m_state;
                        Reader m_reader;

                        std::basic_istream<Char> & load(std::basic_istream<Char> & in) { return m_reader(in, m_data, m_state.state()); }
                    public:
                        dataReader() = default;
                        dataReader(Type & data) : m_data(data), m_state(states) {}

                        friend std::basic_istream<Char> & operator>>(std::basic_istream<Char> & in, dataReader & reader) {
                            return reader.load(in);
                        }

                        bool operator()() { return m_state(); }

                        inline int state() { return m_state.state(); }
                    };

                    /**
                     * @brief The template class can be used to load any type of instance.  From a regular primitive type,
                     *      class type to a container and dictionary type instance.  It allows one to be able to determine
                     *      how the instance can be loaded using the Reader type definition.  The Reader type needs to be
                     *      able to define the >> operator as well as a () operator that returns a bool.  The first operator
                     *      is obvious but the second operator is used to determine if we've completed loading the object
                     *      of type Type.  This technique will allow one to create any type of Type that the loader can
                     *      populate.
                     *
                     * @tparam Type The type that will be populated
                     * @tparam Char The type of input used, char or wchar_t
                     * @tparam Reader The reader type that will be used to populate the type, default reader<Type,Char>
                     * @tparam states The number of fields that need to be read to create the Type type, default 1
                     * @tparam IsOpenChar The type used to determine if the open character was encountered, default is_character_noop<Char>
                     * @tparam IsCloseChar The type used to determine if the close character was encountered, default is_character_noop<Char>
                     * @tparam IsSpace The type used to skip space-like characters when processing the input stream, default is_space
                     */
                    template<
                        typename Type,
                        typename Char = char,
                        typename Reader = reader<Type,Char>,
                        int states = 1,
                        typename IsOpenChar = valhalla::utils::checkers::is_character_noop<Char>,
                        typename IsCloseChar = valhalla::utils::checkers::is_character_noop<Char>,
                        typename IsSpace = valhalla::utils::checkers::is_space
                    >
                    class dataLoader {
                        Type & m_type;
                    public:
                        dataLoader() = default;
                        dataLoader(Type & type) : m_type(type) {}

                        friend std::basic_istream<Char> & operator>>(std::basic_istream<Char> & in, dataLoader & dataloader) {
                            valhalla::utils::checkers::skip_spaces<Char, IsSpace> skipSpace;
                            IsOpenChar isOpenChar;
                            IsCloseChar isCloseChar;

                            skipSpace(in); // skip space-like input
                            if (isOpenChar(in)) {
                                skipSpace(in); // skip space-like input

                                dataReader<Type,Char,Reader,states> reader(dataloader.m_type);
                                while (isCloseChar(in) == false) {
                                    do {
                                        std::streamoff pos = in.tellg();
                                        in >> reader;
                                        if (in.tellg() == pos) {
                                            throw std::runtime_error("No input was processed");
                                        } // if
                                        skipSpace(in); // skip space-like input
                                    } while (reader());
                                } // while

                                skipSpace(in); // skip space-like input
                                return in;
                            } // if

                            throw std::runtime_error("Invalid input data encountered no open character found - dataLoader v4");
                        }
                    };
                } // v4
            } // loader
        } // loaders
    } // utils
} // valhalla

#endif
