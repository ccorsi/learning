/**
 * @file dataloadertests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains different tests for the data loader template class.
 * @version 0.1
 * @date 2024-03-04
 *
 * @copyright Copyright (c) 2024 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include <iostream>
#include <sstream>

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "data_loader.h"

using namespace valhalla::checkers;
using namespace valhalla::loader;

/******************************************************************************************
 *
 *  Data Loader Tests Status
 *
 *      [x] primitive types, mainly int
 *      [x] simple object containing a single field
 *      [x] simple object containing two or more fields
 *      [x] complex object containing one or more non-primitive type fields
 *      [x] container containing a primitive
 *      [x] container containing a non-primitive type
 *      [x] container of container of primitive
 *      [x] container of container of non-primitve type
 *      [x] map containing a primitive
 *      [x] map containing a non-primitive type
 *      [x] map of map of primitive
 *      [x] map of map of non-primitve type
 *      [x] load a simple string
 *      [x] load a complex string with space-like characters
 *      [x] load a simple tuple
 *      [x] load a complex tuple
 *      [x] load string with leading white spaces
 *      [x] load string with trailing white spaces
 *      [x] load string with leading and trailing white spaces
 *      [x] load string with open/close character establish during runtime
 *      [x] load binary data into uint8_t
 *      [x] load binary data into uint16_t
 *      [x] load binary data into uint32_t
 *      [x] load binary data into uint64_t
 *      [x] load binary data into a complex class definition
 *
 ******************************************************************************************/

class IntegerData {
    int m_value;
public:
    IntegerData() = default;
    IntegerData(int value) :  m_value(value) {}

    friend std::istream & operator>>(std::istream & in, IntegerData & data) {
        return in >> data.m_value;
    }

    friend inline bool operator==(const IntegerData & lhs, const IntegerData & rhs) {
        return lhs.m_value == rhs.m_value;
    }

    friend inline std::ostream & operator<<(std::ostream & out, IntegerData & data) {
        return out << data.m_value;
    }
};

class A {
    int x,y;
public:
    A() = default;
    A(int a, int b) : x(a), y(b) {}

    friend inline bool operator==(const A & rhs, const A & lhs) {
        return rhs.x == lhs.x && rhs.y == lhs.y;
    }

    friend std::ostream & operator<<(std::ostream & out, const A & a) {
        return out << "A[ x=" << a.x << " y=" << a.y << " ]";
    }
};

class B {
    int x, y;
public:
    B() = default;
    B(int a, int b) : x(a), y(b) {}

    friend inline bool operator==(const B & rhs, const B & lhs) {
        return rhs.x == lhs.x && rhs.y == lhs.y;
    }

    friend std::ostream & operator<<(std::ostream & out, const B & b) {
        return out << "B[ x=" << b.x << " y=" << b.y << " ]";
    }
};

class C {
    A a;
    B b;
public:
    C() = default;
    C(A x, B y) : a(x), b(y) {}

    friend inline bool operator==(const C & rhs, const C & lhs) {
        return rhs.a == lhs.a && rhs.b == lhs.b;
    }

    friend std::ostream & operator<<(std::ostream & out, const C & c) {
        return out << "C[ x=" << c.a << " b=" << c.b << " ]";
    }
};

TEST(DataLoaderTestSuite, IntegerDataLoaderTest) {
    int actual, expected = 13;
    std::stringstream in(" 13 ");

    dataLoader<
        int,
        char
    > loader(actual);
    in >> loader;

    ASSERT_EQ(actual, expected);
}

TEST(DataLoaderTestSuite, IntegerDataObjectDataLoaderTest) {
    IntegerData actual, expected = { 13 };
    std::stringstream in(" { 13 } ");

    dataLoader<
        IntegerData,
        char,
        reader<IntegerData,char>,
        1,
        is_character<char,'{'>,
        is_character<char,'}'>,
        is_space_or<','>
    > loader(actual);
    in >> loader;

    ASSERT_EQ(actual, expected);
}

class AObjectReader {
    int m_x;
public:
    std::istream & operator()(std::istream & in, A & a, int state) {
        switch(state) {
            case 0:
                in >> m_x;
                break;
            case 1:
                int y;
                in >> y;
                a = A(m_x,y);
                break;
        } // switch
        return in;
    }
};

TEST(DataLoaderTestSuite, AObjectDataLoaderTest) {
    A actual, expected = { 13, 15 };
    std::stringstream in(" { 13, 15 } ");

    dataLoader<
        A,
        char,
        AObjectReader,
        2,
        is_character<char,'{'>,
        is_character<char,'}'>,
        is_space_or<','>
    > loader(actual);
    in >> loader;

    ASSERT_EQ(actual, expected);
}

class BObjectReader {
    int m_x;
public:
    std::istream & operator()(std::istream & in, B & b, int state) {
        switch(state) {
            case 0:
                in >> m_x;
                break;
            case 1:
                int y;
                in >> y;
                b = B(m_x,y);
                break;
        } // switch
        return in;
    }
};

class CObjectReader {
    A m_a;
public:
    std::istream & operator()(std::istream & in, C & c, int state) {
        switch(state) {
            case 0:
                {
                    dataLoader<
                        A,
                        char,
                        AObjectReader,
                        2,
                        is_character<char,'{'>,
                        is_character<char,'}'>,
                        is_space_or<','>
                    > loader(m_a);
                    in >> loader;
                }
                break;
            case 1:
                {
                    B b;
                    dataLoader<
                        B,
                        char,
                        BObjectReader,
                        2,
                        is_character<char,'{'>,
                        is_character<char,'}'>,
                        is_space_or<','>
                    > loader(b);
                    in >> loader;
                    c = C(m_a,b);
                }
                break;
        } // switch
        return in;
    }
};

struct IntegerVectorReader {
    std::istream & operator()(std::istream & in, std::vector<int> & vec, int state) {
        int value;
        in >> value;
        vec.push_back(value);
        return in;
    }
};

TEST(DataLoaderTestSuite, CObjectDataLoaderTest) {
    C actual, expected = { { 13, 15 }, { 17, 21 } };
    std::stringstream in(" { { 13, 15 }, { 17, 21 } } ");

    dataLoader<
        C,
        char,
        CObjectReader,
        2,
        is_character<char,'{'>,
        is_character<char,'}'>,
        is_space_or<','>
    > loader(actual);
    in >> loader;

    ASSERT_EQ(actual, expected);
}

TEST(DataLoaderTestSuite, IntegerVectorDataLoaderTest) {
    std::vector<int> actual, expected = { 13, 15, 17, 21 };
    std::stringstream in(" { 13, 15, 17, 21 } ");

    dataLoader<
        std::vector<int>,
        char,
        IntegerVectorReader,
        1,
        is_character<char,'{'>,
        is_character<char,'}'>,
        is_space_or<','>
    > loader(actual);
    in >> loader;

    ASSERT_EQ(actual, expected);
}

struct AVectorReader {
    std::istream & operator()(std::istream & in, std::vector<A> & vec, int state) {
        A a;
        dataLoader<
            A,
            char,
            AObjectReader,
            2,
            is_character<char,'{'>,
            is_character<char,'}'>,
            is_space_or<','>
        > loader(a);
        in >> loader;
        vec.push_back(a);
        return in;
    }
};

TEST(DataLoaderTestSuite, AVectorDataLoaderTest) {
    std::vector<A> actual, expected = { { 13, 15 }, { 17, 21 } };
    std::stringstream in(" { { 13, 15 }, { 17, 21 } } ");

    dataLoader<
        std::vector<A>,
        char,
        AVectorReader,
        1,
        is_character<char,'{'>,
        is_character<char,'}'>,
        is_space_or<','>
    > loader(actual);
    in >> loader;

    ASSERT_EQ(actual, expected);
}

struct IntegerVectorVectorReader {
    std::istream & operator()(std::istream & in, std::vector<std::vector<int>> & vecvec, int state) {
        std::vector<int> vec;

        dataLoader<
            std::vector<int>,
            char,
            IntegerVectorReader,
            1,
            is_character<char,'{'>,
            is_character<char,'}'>,
            is_space_or<','>
        > loader(vec);
        in >> loader;

        vecvec.push_back(vec);

        return in;
    }
};

TEST(DataLoaderTestSuite, IntegerVectorVectorDataLoaderTest) {
    std::vector<std::vector<int>> actual, expected = { { 13, 15 }, { 17, 21 } };
    std::stringstream in(" { { 13, 15 }, { 17, 21 } } ");

    dataLoader<
        std::vector<std::vector<int>>,
        char,
        IntegerVectorVectorReader,
        1,
        is_character<char,'{'>,
        is_character<char,'}'>,
        is_space_or<','>
    > loader(actual);
    in >> loader;

    ASSERT_EQ(actual, expected);
}

struct AVectorVectorReader {
    std::istream & operator()(std::istream & in, std::vector<std::vector<A>> & vecvec, int state) {
        std::vector<A> vec;

        dataLoader<
            std::vector<A>,
            char,
            AVectorReader,
            1,
            is_character<char,'{'>,
            is_character<char,'}'>,
            is_space_or<','>
        > loader(vec);
        in >> loader;

        vecvec.push_back(vec);

        return in;
    }
};

TEST(DataLoaderTestSuite, AVectorVectorDataLoaderTest) {
    std::vector<std::vector<A>> actual, expected = { { { 13, 15 }, { 9, 10 } }, { { 17, 21 }, { 1, 3 } } };
    std::stringstream in(" { { { 13, 15 }, { 9, 10 } }, { { 17, 21 }, { 1, 3 } } } ");

    dataLoader<
        std::vector<std::vector<A>>,
        char,
        AVectorVectorReader,
        1,
        is_character<char,'{'>,
        is_character<char,'}'>,
        is_space_or<','>
    > loader(actual);
    in >> loader;

    ASSERT_EQ(actual, expected);
}

struct IntegerPairReader {
    std::istream & operator()(std::istream & in, std::pair<int,int> & entry, int state) {
        int * value = nullptr;
        switch(state) {
            case 0:
                value = &entry.first;
                break;
            case 1:
                value = &entry.second;
                break;
            default:
                throw std::runtime_error("Invalid state was passed");
        } // switch

        dataLoader<
            int,
            char
        > loader(*value);
        in >> loader;

        return in;
    }
};

struct IntegerMapReader {
    std::istream & operator()(std::istream & in, std::map<int,int> & dict, int state) {
        std::pair<int,int> entry;

        dataLoader<
            std::pair<int,int>,
            char,
            IntegerPairReader,
            2,
            is_character<char,'{'>,
            is_character<char,'}'>,
            is_space_or<','>
        > loader(entry);
        in >> loader;

        dict[entry.first] = entry.second;

        return in;
    }
};

TEST(DataLoaderTestSuite, IntegerIntegerMapDataLoaderTest) {
    std::map<int,int> actual, expected = { { 13, 15 }, { 9, 10 }, { 17, 21 }, { 1, 3 } };
    std::stringstream in(" { { 13, 15 }, { 9, 10 }, { 17, 21 }, { 1, 3 } } ");

    dataLoader<
        std::map<int,int>,
        char,
        IntegerMapReader,
        1,
        is_character<char,'{'>,
        is_character<char,'}'>,
        is_space_or<','>
    > loader(actual);
    in >> loader;

    ASSERT_EQ(actual, expected);
}

struct IntegerAPairReader {
    std::istream & operator()(std::istream & in, std::pair<int,A> & entry, int state) {
        switch(state) {
            case 0:
                {
                    dataLoader<
                        int,
                        char
                    > loader(entry.first);
                    in >> loader;
                }
                break;
            case 1:
                {
                    dataLoader<
                        A,
                        char,
                        AObjectReader,
                        2,
                        is_character<char,'{'>,
                        is_character<char,'}'>,
                        is_space_or<','>
                    > loader(entry.second);
                    in >> loader;
                }
                break;
            default:
                throw std::runtime_error("Invalid state was passed");
        } // switch

        return in;
    }
};

struct IntegerAMapReader {
    std::istream & operator()(std::istream & in, std::map<int,A> & dict, int state) {
        std::pair<int,A> entry;

        dataLoader<
            std::pair<int,A>,
            char,
            IntegerAPairReader,
            2,
            is_character<char,'{'>,
            is_character<char,'}'>,
            is_space_or<','>
        > loader(entry);
        in >> loader;

        dict[entry.first] = entry.second;

        return in;
    }
};

TEST(DataLoaderTestSuite, IntegerAMapDataLoaderTest) {
    std::map<int,A> actual, expected = { { 13, { 15, 16 } }, { 9, { 10, 11 } }, { 17, { 21, 22 } }, { 1, { 3, 4 } } };
    std::stringstream in(" { { 13, { 15, 16 } }, { 9, { 10, 11 } }, { 17, { 21, 22 } }, { 1, { 3, 4 } } } ");

    dataLoader<
        std::map<int,A>,
        char,
        IntegerAMapReader,
        1,
        is_character<char,'{'>,
        is_character<char,'}'>,
        is_space_or<','>
    > loader(actual);
    in >> loader;

    ASSERT_EQ(actual, expected);
}

struct IntegerMapPairReader {
    std::istream & operator()(std::istream & in, std::pair<int,std::map<int,int>> & entry, int state) {
        switch (state) {
            case 0:
                {
                    dataLoader<
                        int,
                        char
                    > loader(entry.first);
                    in >> loader;
                }
                break;

            case 1:
                {
                    dataLoader<
                        std::map<int,int>,
                        char,
                        IntegerMapReader,
                        1,
                        is_character<char,'{'>,
                        is_character<char,'}'>,
                        is_space_or<','>
                    > loader(entry.second);
                    in >> loader;
                }
                break;

            default:
                throw std::runtime_error("IntegerMapPairReader invalid state was passed");
        } // switch

        return in;
    }
};

struct IntegerMapMapReader {
    std::istream & operator()(std::istream & in, std::map<int,std::map<int,int>> & dict, int state) {
        std::pair<int,std::map<int,int>> entry;

        dataLoader<
            std::pair<int, std::map<int,int>>,
            char,
            IntegerMapPairReader,
            2,
            is_character<char,'{'>,
            is_character<char,'}'>,
            is_space_or<','>
        > loader(entry);
        in >> loader;

        dict[entry.first] = entry.second;

        return in;
    }
};

TEST(DataLoaderTestSuite, IntegerIntegerMapMapDataLoaderTest) {
    std::map<int, std::map<int,int>> actual,
        expected = { { 1, { { 13, 15 } } }, { 2, { { 9, 10 } } }, { 3, { { 17, 21 } } }, { 4, { { 1, 3 } } } };
    std::stringstream in(" { { 1, { { 13, 15 } } }, { 2, { { 9, 10 } } }, { 3, { { 17, 21 } } }, { 4, { { 1, 3 } } } } ");

    dataLoader<
        std::map<int, std::map<int,int>>,
        char,
        IntegerMapMapReader,
        1,
        is_character<char,'{'>,
        is_character<char,'}'>,
        is_space_or<','>
    > loader(actual);
    in >> loader;

    ASSERT_EQ(actual, expected);
}

struct IntegerAMapPairReader {
    std::istream & operator()(std::istream & in, std::pair<int,std::map<int,A>> & entry, int state) {
        switch (state) {
            case 0:
                {
                    dataLoader<
                        int,
                        char
                    > loader(entry.first);
                    in >> loader;
                }
                break;

            case 1:
                {
                    dataLoader<
                        std::map<int,A>,
                        char,
                        IntegerAMapReader,
                        1,
                        is_character<char,'{'>,
                        is_character<char,'}'>,
                        is_space_or<','>
                    > loader(entry.second);
                    in >> loader;
                }
                break;

            default:
                throw std::runtime_error("IntegerMapPairReader invalid state was passed");
        } // switch

        return in;
    }
};

struct IntegerAMapMapReader {
    std::istream & operator()(std::istream & in, std::map<int, std::map<int,A>> & dict, int state) {
        std::pair<int,std::map<int,A>> entry;

        dataLoader<
            std::pair<int, std::map<int,A>>,
            char,
            IntegerAMapPairReader,
            2,
            is_character<char,'{'>,
            is_character<char,'}'>,
            is_space_or<','>
        > loader(entry);
        in >> loader;

        dict[entry.first] = entry.second;

        return in;
    }
};

TEST(DataLoaderTestSuite, IntegerAMapMapDataLoaderTest) {
    std::map<int, std::map<int,A>> actual,
        expected = { { 1, { { 13, { 15, 16 } } } }, { 2, { { 9, { 10, 11 } } } } };
    std::stringstream in(" { { 1, { { 13, { 15, 16 } } } }, { 2, { { 9, { 10, 11 } } } } } ");

    dataLoader<
        std::map<int, std::map<int,A>>,
        char,
        IntegerAMapMapReader,
        1,
        is_character<char,'{'>,
        is_character<char,'}'>,
        is_space_or<','>
    > loader(actual);
    in >> loader;

    ASSERT_EQ(actual, expected);
}

struct StringReader {
    std::basic_istream<char> & operator()(std::basic_istream<char> & in, std::string & str, int state) {

        while (static_cast<char>(in.peek()) != '"') {
            str += static_cast<char>(in.get());
        }

        return in;
    }
};

TEST(DataLoaderTestSuite, SimpleStringDataLoaderTest) {
    std::string actual,
        expected = "simple";
    std::stringstream in(" \"simple\" ");

    dataLoader<
        std::string,
        char,
        StringReader,
        1,
        is_character<char,'"'>,
        is_character<char,'"'>,
        is_space_or<','>,
        is_space_noop<char>
    > loader(actual);
    in >> loader;

    ASSERT_EQ(actual, expected);
}

TEST(DataLoaderTestSuite, ComplexStringDataLoaderTest) {
    std::string actual,
        expected = "This is a string with spaces in-between open and close characters";
    std::stringstream in(" \"This is a string with spaces in-between open and close characters\" ");

    dataLoader<
        std::string,
        char,
        StringReader,
        1,
        is_character<char,'"'>,
        is_character<char,'"'>,
        is_space_or<','>,
        is_space_noop<char>
    > loader(actual);
    in >> loader;

    ASSERT_EQ(actual, expected);
}

struct TupleStringReader {
    std::basic_istream<char> & operator()(std::basic_istream<char> & in, std::tuple<std::string> & tup, int state) {
        std::string entry;

        dataLoader<
            std::string,
            char,
            StringReader,
            1,
            is_character<char,'"'>,
            is_character<char,'"'>,
            is_space_or<','>,
            is_space_noop<int>
        > entryLoader(entry);
        in >> entryLoader;

        tup = std::tuple<std::string>(entry);

        return in;
    }
};

TEST(DataLoaderTestSuite, SimpleTupleDataLoaderTest) {
    std::tuple<std::string> actual,
        expected = std::tuple<std::string>("This is a string with spaces in-between open and close characters");
    std::stringstream in(" ( \"This is a string with spaces in-between open and close characters\" ) ");

    dataLoader<
        std::tuple<std::string>,
        char,
        TupleStringReader,
        1,
        is_character<char,'('>,
        is_character<char,')'>,
        is_space_or<','>
    > loader(actual);
    in >> loader;

    ASSERT_EQ(actual, expected);
}

struct ComplexTupleReader {
    std::basic_istream<char> & operator()(std::basic_istream<char> & in, std::tuple<std::string,int,long> & tup, int state) {
        std::string eone;

        dataLoader<
            std::string,
            char,
            StringReader,
            1,
            is_character<char,'"'>,
            is_character<char,'"'>,
            is_space_or<','>,
            is_space_noop<int>
        > entryLoader(eone);
        in >> entryLoader;

        int etwo;

        dataLoader<
            int,
            char
        > etwoLoader(etwo);
        in >> etwoLoader;

        long ethree;

        dataLoader<
            long,
            char,
            reader<long,char>,
            1,
            is_character_noop<char>,
            is_no_character<char>,
            is_space_or<','>
        > ethreeLoader(ethree);
        in >> ethreeLoader;

        tup = {eone, etwo, ethree};

        return in;
    }
};

TEST(DataLoaderTestSuite, ComplexTupleDataLoaderTest) {
    std::tuple<std::string,int,long> actual,
        expected = {"This is a string with spaces in-between open and close characters", 101, 1003 };
    std::stringstream in(" ( \"This is a string with spaces in-between open and close characters\", 101, 1003 ) ");

    dataLoader<
        std::tuple<std::string,int,long>,
        char,
        ComplexTupleReader,
        1,
        is_character<char,'('>,
        is_character<char,')'>,
        is_space_or<','>
    > loader(actual);
    in >> loader;

    ASSERT_EQ(actual, expected);
}

TEST(DataLoaderTestSuite, StringWithLeadingSpacesTest) {
    std::string actual, expected = "  string contains preceeding spaces.";
    std::stringstream in(" \"  string contains preceeding spaces.\"  ");

    dataLoader<
        std::string,
        char,
        StringReader,
        1,
        is_character<char,'"'>,
        is_character<char,'"'>
    > loader(actual);
    in >> loader;

    ASSERT_EQ(actual, expected);
}

TEST(DataLoaderTestSuite, StringWithTrailingSpacesTest) {
    std::string actual, expected = "string contains preceeding spaces.   ";
    std::stringstream in(" \"string contains preceeding spaces.   \"  ");

    dataLoader<
        std::string,
        char,
        StringReader,
        1,
        is_character<char,'"'>,
        is_character<char,'"'>
    > loader(actual);
    in >> loader;

    ASSERT_EQ(actual, expected);
}

TEST(DataLoaderTestSuite, StringWithLeadingAndTrailingSpacesTest) {
    std::string actual, expected = "  string contains preceeding spaces.    ";
    std::stringstream in(" \"  string contains preceeding spaces.    \"  ");

    dataLoader<
        std::string,
        char,
        StringReader,
        1,
        is_character<char,'"'>,
        is_character<char,'"'>
    > loader(actual);
    in >> loader;

    ASSERT_EQ(actual, expected);
}

struct StringWithEscapeCharacterReader {
    std::basic_istream<char> & operator()(std::basic_istream<char> & in, std::string & str, int state) {

        while (static_cast<char>(in.peek()) != '"') {
            char chr = in.get();
            if (chr == '\\') {
                chr = in.get();
            }
            str += static_cast<char>(chr);
        }

        return in;
    }
};

TEST(DataLoaderTestSuite, StringWithEscapeCharactersTest) {
    std::string actual, expected = "  string contains \"preceeding\" spaces.    ";
    std::stringstream in(" \"  string contains \\\"preceeding\\\" spaces.    \"  ");

    dataLoader<
        std::string,
        char,
        StringWithEscapeCharacterReader,
        1,
        is_character<char,'"'>,
        is_character<char,'"'>
    > loader(actual);
    in >> loader;

    ASSERT_EQ(actual, expected);
}

struct StringWithDynamicEscapeCharacterReader {
    std::basic_istream<char> & operator()(std::basic_istream<char> & in, std::string & str, int state) {
        const char delimiter = in.get();

        while (static_cast<char>(in.peek()) != delimiter) {
            char chr = in.get();
            if (chr == '\\') {
                chr = in.get();
            }
            str += static_cast<char>(chr);
        }

        return in;
    }
};

TEST(DataLoaderTestSuite, StringWithDynamicEscapeCharactersTest) {
    std::string actual, expected = "  string contains \"preceeding\" spaces.    ";
    std::stringstream in(" \"  string contains \\\"preceeding\\\" spaces.    \"  ");

    dataLoader<
        std::string,
        char,
        StringWithDynamicEscapeCharacterReader,
        1,
        is_character_noop<char>,
        is_no_character<char>
    > loader(actual);
    in >> loader;

    ASSERT_EQ(actual, expected);
}

#include <memory>
#include <cstddef>
#include <cstdint>
#include <fstream>

class constant_pool_entry {
    uint16_t m_tag;
public:
    constant_pool_entry(uint16_t tag = 0) : m_tag(tag) {}

    virtual ~constant_pool_entry() {}

    uint16_t tag() { return m_tag; }
};

class constant_class : public constant_pool_entry {
    uint16_t m_name_index;
public:
    constant_class() = default;
    constant_class(uint16_t name_index) : m_name_index(name_index) {
        constant_pool_entry(7);
    }
};

class constant_methodref : public constant_pool_entry {
    uint16_t m_class_index, m_name_and_type_index;
public:
    constant_methodref() = default;
    constant_methodref(uint16_t class_index, uint16_t name_and_type_index) :
        m_class_index(class_index), m_name_and_type_index(name_and_type_index) {
            constant_pool_entry(10);
        }
};

class constant_fieldref : public constant_pool_entry {
    uint16_t m_class_index, m_name_and_type_index;
public:
    constant_fieldref() = default;
    constant_fieldref(uint16_t class_index, uint16_t name_and_type_index) :
        m_class_index(class_index), m_name_and_type_index(name_and_type_index) {
            constant_pool_entry(9);
        }
};

class constant_utf8 : public constant_pool_entry {
    std::vector<uint8_t> m_bytes;
public:
    constant_utf8() = default;
    constant_utf8(std::vector<uint8_t> & bytes) : m_bytes(bytes) {
        constant_pool_entry(1);
    }
};

class constant_name_and_type : public constant_pool_entry {
    uint16_t m_name_index, m_descriptor_index;
public:
    constant_name_and_type() = default;
    constant_name_and_type(uint16_t name_index, uint16_t descriptor_index) :
        m_name_index(name_index), m_descriptor_index(descriptor_index) {
            constant_pool_entry(12);
        }
};

class constant_string : public constant_pool_entry {
    uint16_t m_string_index;
public:
    constant_string() = default;
    constant_string(uint16_t string_index) : m_string_index(string_index) {
        constant_pool_entry(8);
    }
};

class java_attribute {
    uint16_t m_attribute_name_index;
    std::vector<uint8_t> m_info;
public:
    java_attribute() = default;
    java_attribute(uint16_t attribute_name_index, std::vector<uint8_t> & info)
        : m_attribute_name_index(attribute_name_index), m_info(info) {
        }
};

class java_field {
    uint16_t m_access_flags,
        m_name_index,
        m_descriptor_index;
    std::vector<java_attribute> m_attributes;
public:
    java_field() = default;
    java_field(uint16_t access_flags, uint16_t name_index, uint16_t descriptor_index, std::vector<java_attribute> & attributes)
        : m_access_flags(access_flags), m_name_index(name_index), m_descriptor_index(descriptor_index),
        m_attributes(attributes) {
        }
};

class java_method {
    uint16_t m_access_flags,
        m_name_index,
        m_descriptor_index;
    std::vector<java_attribute> m_attributes;
public:
    java_method() = default;
    java_method(uint16_t access_flags, uint16_t name_index, uint16_t descriptor_index, std::vector<java_attribute> & attributes)
        : m_access_flags(access_flags), m_name_index(name_index), m_descriptor_index(descriptor_index),
        m_attributes(attributes) {
        }
};

class java_class {
    static const uint32_t m_magic = 0xCAFEBABE;
    uint16_t m_minor_version,
        m_major_version;
    std::vector<std::unique_ptr<constant_pool_entry>> m_constant_pool;
    uint16_t m_access,
        m_this,
        m_super;
    std::vector<uint16_t> m_interfaces;
    std::vector<java_field> m_fields;
    std::vector<java_method> m_methods;
    std::vector<java_attribute> m_attributes;

public:
    java_class() = default;
    java_class(uint16_t minor_version, uint16_t major_version,
               std::vector<std::unique_ptr<constant_pool_entry>> & constant_pool,
               uint16_t access, uint16_t this_class, uint16_t super,
               std::vector<uint16_t> & interfaces,
               std::vector<java_field> & fields,
               std::vector<java_method> & methods,
               std::vector<java_attribute> & attributes) :
                m_minor_version(minor_version), m_major_version(major_version),
                m_access(access), m_this(this_class),
                m_super(super), m_interfaces(interfaces), m_fields(fields),
                m_methods(methods), m_attributes(attributes) {
                    // Use the standard move call when using unique_ptr type in a template
                    m_constant_pool = std::move(constant_pool);
               }
    uint16_t minor_version() { return m_minor_version; }
    uint16_t major_version() { return m_major_version; }
    uint16_t access() { return m_access; }
    uint16_t class_index() { return m_this; }
    uint16_t super_class_index() { return m_super; }
    std::size_t constant_pool_count() { return m_constant_pool.size() + 1; }
    std::size_t interface_count() { return m_interfaces.size(); }
    std::size_t field_count() { return m_fields.size(); }
    std::size_t method_count() { return m_methods.size(); }
    std::size_t attribute_count() { return m_attributes.size(); }
};

template<typename Type>
struct big_endian_reader {
    std::istream & operator()(std::istream & in, Type & type, int field) {
        const auto size = sizeof(Type);
        // std::cout << "big_endian_reader size: " << size << "\n";
        // std::cout << "tellg: " << in.tellg() << "\n";

        for (int idx = 0 ; idx < size ; idx++) {
            if (in.eof()) {
                throw std::runtime_error("Insufficient input stream for big-endian data");
            } // if (in.eof())

            uint8_t entry = static_cast<uint8_t>(in.get());
            // shift type by8 bits
            type <<= 8;
            // add the read entry
            type += entry;
        } // for (int idx = 0 ; idx < Size ; idx++)
        // std::cout << "value: " << type << ", tellg: " << in.tellg() << "\n";

        return in;
    }
};

template<typename Type>
void load_big_endian_value(std::istream & in, Type & value) {
    dataLoader<
        Type,
        char,
        big_endian_reader<Type>,
        1,
        is_character_noop<char>,
        is_no_character<char>,
        is_space_noop<char>
    > loader(value);
    in >> loader;
}

struct constant_utf8_reader {
    std::istream & operator()(std::istream & in, std::unique_ptr<constant_pool_entry> & entry, int field) {
        uint16_t length;

        load_big_endian_value<uint16_t>(in, length);
        // std::cout << "Constant_Utf8:\n";
        // std::cout << "length: " << length << "\n";

        std::vector<uint8_t> bytes;
        uint8_t value;

        while (length > 0 &&
            (value = static_cast<uint8_t>(in.get()), in.eof() == false)) {
                length--;
                bytes.push_back(value);
        }

        if (length > 0) {
            throw std::runtime_error("Reached eof while populating constant_utf8 entry");
        }

        entry = std::make_unique<constant_utf8>(bytes);

        return in;
    }
};

struct constant_class_reader {
    std::istream & operator()(std::istream & in, std::unique_ptr<constant_pool_entry> & entry, int field) {
        uint16_t name_and_index;

        load_big_endian_value<uint16_t>(in, name_and_index);

        entry = std::make_unique<constant_class>(name_and_index);
        // std::cout << "Constant_Class:\n";
        // std::cout << "name_and_index: " << name_and_index << "\n";

        return in;
    }
};

struct constant_string_reader {
    std::istream & operator()(std::istream & in, std::unique_ptr<constant_pool_entry> & entry, int field) {
        uint16_t string_index;

        load_big_endian_value<uint16_t>(in, string_index);

        entry = std::make_unique<constant_string>(string_index);
        // std::cout << "Constant_String:\n";
        // std::cout << "string_index: " << string_index << "\n";

        return in;
    }
};

template<typename Ref>
struct constant_ref_reader {
    std::istream & operator()(std::istream & in, std::unique_ptr<constant_pool_entry> & entry, int field) {
        uint16_t class_index;

        load_big_endian_value<uint16_t>(in, class_index);

        uint16_t name_and_type_index;

        load_big_endian_value<uint16_t>(in, name_and_type_index);

        entry = std::make_unique<Ref>(class_index, name_and_type_index);
        // std::cout << "class_index: " << class_index << "\n";
        // std::cout << "name_and_type_index: " << name_and_type_index << "\n";

        return in;
    }
};

struct constant_name_and_type_reader {
    std::istream & operator()(std::istream & in, std::unique_ptr<constant_pool_entry> & entry, int field) {
        uint16_t name_index;

        load_big_endian_value<uint16_t>(in, name_index);

        uint16_t descriptor_index;

        load_big_endian_value<uint16_t>(in, descriptor_index);

        entry = std::make_unique<constant_name_and_type>(name_index, descriptor_index);

        // std::cout << "Constant_NameAndType:\n";
        // std::cout << "name_index: " << name_index << "\n";
        // std::cout << "descriptor_index: " << descriptor_index << "\n";

        return in;
    }
};

struct constant_pool_reader {
    std::istream & operator()(std::istream & in, std::vector<std::unique_ptr<constant_pool_entry>> & cp, int field) {
        uint16_t count;

        load_big_endian_value<uint16_t>(in, count);
        // std::cout << "constant_pool count: " << count << "\n";

        while (count-- > 1) {
            uint8_t tag;
            // overkill but just for testing purposes
            load_big_endian_value<uint8_t>(in, tag);
            std::unique_ptr<constant_pool_entry> entry;
            // std::cout << "tag: " << static_cast<int>(tag) << "\n";

            switch(tag) {
                case 1: // Utf8
                {
                    dataLoader<
                        std::unique_ptr<constant_pool_entry>,
                        char,
                        constant_utf8_reader,
                        1,
                        is_character_noop<char>,
                        is_no_character<char>,
                        is_space_noop<char>
                    > loader(entry);
                    in >> loader;
                }
                    break;
                case 7: // Class
                {
                    dataLoader<
                        std::unique_ptr<constant_pool_entry>,
                        char,
                        constant_class_reader,
                        1,
                        is_character_noop<char>,
                        is_no_character<char>,
                        is_space_noop<char>
                    > loader(entry);
                    in >> loader;
                }
                    break;
                case 8: // String
                {
                    dataLoader<
                        std::unique_ptr<constant_pool_entry>,
                        char,
                        constant_string_reader,
                        1,
                        is_character_noop<char>,
                        is_no_character<char>,
                        is_space_noop<char>
                    > loader(entry);
                    in >> loader;
                }
                    break;
                case 9: // FieldRef
                {
                    // std::cout << "Constant_FieldRef:\n";
                    dataLoader<
                        std::unique_ptr<constant_pool_entry>,
                        char,
                        constant_ref_reader<constant_fieldref>,
                        1,
                        is_character_noop<char>,
                        is_no_character<char>,
                        is_space_noop<char>
                    > loader(entry);
                    in >> loader;
                }
                    break;
                case 10: // MethodRef
                {
                    // std::cout << "Constant_MethodRef:\n";
                    dataLoader<
                        std::unique_ptr<constant_pool_entry>,
                        char,
                        constant_ref_reader<constant_methodref>,
                        1,
                        is_character_noop<char>,
                        is_no_character<char>,
                        is_space_noop<char>
                    > loader(entry);
                    in >> loader;
                }
                    break;
                case 12: // NameAndType
                {
                    dataLoader<
                        std::unique_ptr<constant_pool_entry>,
                        char,
                        constant_name_and_type_reader,
                        1,
                        is_character_noop<char>,
                        is_no_character<char>,
                        is_space_noop<char>
                    > loader(entry);
                    in >> loader;
                }
                    break;
                default:
                    std::stringstream msg;
                    msg << "Unknowned constant pool tag: " << tag;
                    // std::cout << "Unknowned constant pool tag: " << tag << "\n";
                    throw std::runtime_error(msg.str());
            }
            // add constant pool entry to constant pool
            cp.push_back(std::move(entry));
        } // while (count-- > 1)
        return in;
    }
};

struct interfaces_reader {
    std::istream & operator()(std::istream & in, std::vector<uint16_t> & interfaces, int field) {
        uint16_t count;

        load_big_endian_value<uint16_t>(in, count);
        // std::cout << "Interface count: " << count << "\n";

        while (count-- > 0) {
            uint16_t entry;

            load_big_endian_value<uint16_t>(in, entry);
            // std::cout << "Interface constant pool entry: " << entry << "\n";

            interfaces.push_back(entry);
        } // while (count-- > 0)

        return in;
    }
};

struct attribute_reader {
    std::istream & operator()(std::istream & in, java_attribute & attribute, int field) {
        uint16_t attribute_name_index;
        uint32_t attribute_length;
        std::vector<uint8_t> info;

        load_big_endian_value<uint16_t>(in, attribute_name_index);
        load_big_endian_value<uint32_t>(in, attribute_length);
        // std::cout << "Attribute:\n";
        // std::cout << "attribute_name_index: " << attribute_name_index << "\n";
        // std::cout << "attribute_length: " << attribute_length << "\n";

        while (attribute_length-- > 0) {
            uint8_t value;
            load_big_endian_value<uint8_t>(in, value);
            info.push_back(value);
        } // while (attribute_length-- > 0)

        attribute = java_attribute(attribute_name_index, info);

        return in;
    }
};

struct attributes_reader {
    std::istream & operator()(std::istream & in, std::vector<java_attribute> & attributes, int field) {
        uint16_t attributes_count;

        load_big_endian_value<uint16_t>(in, attributes_count);
        // std::cout << "Attributes count: " << attributes_count << "\n";

        while (attributes_count-- > 0) {
            java_attribute attribute;

            dataLoader<
                java_attribute,
                char,
                attribute_reader,
                1,
                is_character_noop<char>,
                is_no_character<char>,
                is_space_noop<char>
            > attributeLoader(attribute);
            in >> attributeLoader;

            attributes.push_back(attribute);
        } // while (attributes_count-- > 0)

        return in;
    }
};

struct field_reader {
    std::istream & operator()(std::istream & in, java_field & field, int notused) {
        uint16_t access_flags, name_index, descriptor_index;

        load_big_endian_value<uint16_t>(in, access_flags);
        load_big_endian_value<uint16_t>(in, name_index);
        load_big_endian_value<uint16_t>(in, descriptor_index);
        // std::cout << "field:\n";
        // std::cout << "access_flags: " << std::hex << access_flags << std::dec << "\n";
        // std::cout << "name_index: " << name_index << "\n";
        // std::cout << "descriptor_index: " << descriptor_index << "\n";

        std::vector<java_attribute> attributes;

        dataLoader<
            std::vector<java_attribute>,
            char,
            attributes_reader,
            1,
            is_character_noop<char>,
            is_no_character<char>,
            is_space_noop<char>
        > attributeLoader(attributes);
        in >> attributeLoader;

        field = java_field(access_flags, name_index, descriptor_index, attributes);

        return in;
    }
};

struct fields_reader {
    std::istream & operator()(std::istream & in, std::vector<java_field> & fields, int notused) {
        uint16_t count;

        load_big_endian_value<uint16_t>(in,count);
        // std::cout << "Fields count: " << count << "\n";

        while (count-- > 0) {
            java_field field;

            dataLoader<
                java_field,
                char,
                field_reader,
                1,
                is_character_noop<char>,
                is_no_character<char>,
                is_space_noop<char>
            > fieldLoader(field);
            in >> fieldLoader;

            fields.push_back(field);

        } // while (count-- > 0)

        return in;
    }
};

struct method_reader {
    std::istream & operator()(std::istream & in, java_method & method, int notused) {
        uint16_t access_flags, name_index, descriptor_index;

        load_big_endian_value<uint16_t>(in, access_flags);
        load_big_endian_value<uint16_t>(in, name_index);
        load_big_endian_value<uint16_t>(in, descriptor_index);
        // std::cout << "method:\n";
        // std::cout << "access_flags: " << std::hex << access_flags << std::dec << "\n";
        // std::cout << "name_index: " << name_index << "\n";
        // std::cout << "descriptor_index: " << descriptor_index << "\n";

        std::vector<java_attribute> attributes;

        dataLoader<
            std::vector<java_attribute>,
            char,
            attributes_reader,
            1,
            is_character_noop<char>,
            is_no_character<char>,
            is_space_noop<char>
        > attributeLoader(attributes);
        in >> attributeLoader;

        method = java_method(access_flags, name_index, descriptor_index, attributes);

        return in;
    }
};

struct methods_reader {
    std::istream & operator()(std::istream & in, std::vector<java_method> & methods, int field) {
        uint16_t count;

        load_big_endian_value<uint16_t>(in,count);
        // std::cout << "Methods count: " << count << "\n";

        while (count-- > 0) {
            java_method method;

            dataLoader<
                java_method,
                char,
                method_reader,
                1,
                is_character_noop<char>,
                is_no_character<char>,
                is_space_noop<char>
            > methodLoader(method);
            in >> methodLoader;

            methods.push_back(method);

        } // while (count-- > 0)

        return in;
    }
};

struct java_class_reader {
    std::istream & operator()(std::istream & in, java_class & jc, int field) {
        uint8_t magic[4] = { 0xCA, 0xFE, 0xBA, 0xBE };
        uint8_t input;

        // Check that the magic number is correct
        for (auto idx = 0 ; idx < 4 ; idx++) {
            // Get the next character
            input = static_cast<uint8_t>(in.get());
            // Check that we haven't reached the eof or it is an invalid magic entry
            if (in.eof() || magic[idx] != input) {
                throw std::runtime_error("Invalid java class magic number");
            } // if (in.eof() || magic[idx] != input)
        } // for (auto idx = 0 ; idx < 4 ; idx++)

        uint16_t minor_version, major_version;

        load_big_endian_value<uint16_t>(in, minor_version);
        load_big_endian_value<uint16_t>(in, major_version);

        std::vector<std::unique_ptr<constant_pool_entry>> constant_pool;
        dataLoader<std::vector<std::unique_ptr<constant_pool_entry>>,
            char,
            constant_pool_reader,
            1,
            is_character_noop<char>,
            is_no_character<char>,
            is_space_noop<char>
        > cpLoader(constant_pool);
        in >> cpLoader;

        uint16_t access, this_class, super_class;

        load_big_endian_value<uint16_t>(in, access);
        // std::cout << "access: " << std::hex << access << std::dec << "\n";

        load_big_endian_value<uint16_t>(in, this_class);
        // std::cout << "this_class: " << this_class << "\n";

        load_big_endian_value<uint16_t>(in, super_class);
        // std::cout << "super_class: " << super_class << "\n";

        std::vector<uint16_t> interfaces;
        dataLoader<
            std::vector<uint16_t>,
            char,
            interfaces_reader,
            1,
            is_character_noop<char>,
            is_no_character<char>,
            is_space_noop<char>
        > interfacesLoader(interfaces);
        in >> interfacesLoader;

        std::vector<java_field> fields;
        dataLoader<
            std::vector<java_field>,
            char,
            fields_reader,
            1,
            is_character_noop<char>,
            is_no_character<char>,
            is_space_noop<char>
        > fieldsLoader(fields);
        in >> fieldsLoader;

        std::vector<java_method> methods;
        dataLoader<
            std::vector<java_method>,
            char,
            methods_reader,
            1,
            is_character_noop<char>,
            is_no_character<char>,
            is_space_noop<char>
        > methodsLoader(methods);
        in >> methodsLoader;

        std::vector<java_attribute> attributes;
        dataLoader<
            std::vector<java_attribute>,
            char,
            attributes_reader,
            1,
            is_character_noop<char>,
            is_no_character<char>,
            is_space_noop<char>
        > attributesLoader(attributes);
        in >> attributesLoader;

        jc = java_class(minor_version, major_version, constant_pool, access,
                this_class, super_class, interfaces, fields, methods, attributes);

        return in;
    }
};

TEST(DataLoaderTestSuite, BinaryDataLoadingTest) {
    std::fstream fin{"data/HelloWorld.class",
            fin.binary | fin.in};

    if (fin.is_open() == false) {
        // workaround with executing individual test within vscode
        fin.open("../../data/HelloWorld.class",
            fin.binary | fin.in);
    }

    ASSERT_TRUE(fin.is_open()) << "Unable to open input file";

    java_class jc;
    dataLoader<
        java_class,
        char,
        java_class_reader,
        1,
        is_character_noop<char>,
        is_no_character<char>,
        is_space_noop<char>
    > javaClassLoader(jc);
    fin >> javaClassLoader;

    uint16_t expected = 0;
    EXPECT_EQ(expected, jc.minor_version());
    EXPECT_EQ((expected = 65, expected), jc.major_version());
    EXPECT_EQ((expected = 33, expected), jc.access());
    EXPECT_EQ((expected = 21, expected), jc.class_index());
    EXPECT_EQ((expected = 2, expected), jc.super_class_index());
    std::size_t size = 0;
    EXPECT_EQ(size, jc.interface_count());
    EXPECT_EQ(size, jc.field_count());
    EXPECT_EQ((size = 2, size), jc.method_count());
    ASSERT_EQ((size = 1, size), jc.attribute_count());
}

#include <stack>

template<typename Type>
void create_istream(std::stringstream & ss, Type type) {
    auto size = sizeof(Type);
    std::stack<uint8_t> s;

    while (size-- > 0) {
        uint8_t value = type & 0xff;
        s.push(value);
        type >>= 8;
    } // while (size-- > 0)

    while (s.empty() == false) {
        unsigned char value = static_cast<unsigned char>(s.top()); s.pop();
        ss.write(reinterpret_cast<const char *>(&value), sizeof(value));
    } // while (s.empty() == false)
}

template<typename Type>
void execute_binary_type_test(Type & expected) {
    std::stringstream ss;
    create_istream<Type>(ss,expected);
    std::istream in(ss.rdbuf());
    Type actual;
    load_big_endian_value<Type>(in, actual);
    ASSERT_EQ(actual, expected);
}

TEST(DataLoaderTestSuite, BinaryUInt8_tDataLoadingTest) {
    uint8_t expected = 101;
    execute_binary_type_test<uint8_t>(expected);
}

TEST(DataLoaderTestSuite, BinaryUInt16_tDataLoadingTest) {
    uint16_t expected = 0xfffe;
    execute_binary_type_test(expected);
}

TEST(DataLoaderTestSuite, BinaryUInt32_tDataLoadingTest) {
    uint32_t expected = 0xfffffffe;
    execute_binary_type_test(expected);
}

TEST(DataLoaderTestSuite, BinaryUInt64_tDataLoadingTest) {
    uint64_t expected = 0xfffffffffffffffe;
    execute_binary_type_test(expected);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
