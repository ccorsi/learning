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
            char,
            reader<int,char>,
            1,
            is_character_noop<char>,
            is_no_character<char>
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
                        char,
                        reader<int,char>,
                        1,
                        is_character_noop<char>,
                        is_no_character<char>
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

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
