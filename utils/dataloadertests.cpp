/**
 * @file dataloadertests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains tests to the different dataLoader template class versions
 * @version 0.1
 * @date 2023-06-05
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

/******************************************************************************************
 *
 *  The following different version of the dataLoader implementation will be required to
 *  implement the following types of tests to determine which of the different versions
 *  will be able to minimize the amount of work that is required to load the particular
 *  type of instances.  This thus includes the following types that are going to be loaded:
 *
 *      - primitive types, mainly int
 *      - simple object containing a single field
 *      - simple object containing two or more fields
 *      - complex object containing one or more non-primitive type fields
 *      - container containing a primitive and non-primitive type
 *      - container of container of primitive and non-primitve type
 *      - map containing a primitive and non-primitive type
 *      - map of map of primitive and non-primitve type
 *
 ******************************************************************************************/
#include <iostream>
#include <sstream>

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "loaders.h"

using namespace valhalla::utils;

/******************************************************************************************
 *
 *  Version 1 Tests Status
 *
 *      [x] primitive types, mainly int
 *      [x] simple object containing a single field
 *      [x] simple object containing two or more fields
 *      [x] complex object containing one or more non-primitive type fields
 *      [ ] container containing a primitive
 *      [ ] container containing a non-primitive type
 *      [ ] container of container of primitive
 *      [x] container of container of non-primitve type
 *      [ ] map containing a primitive
 *      [ ] map containing a non-primitive type
 *      [ ] map of map of primitive
 *      [ ] map of map of non-primitve type
 *
 ******************************************************************************************/

template<typename Type>
class TypeReader {
    Type & m_value;
public:
    TypeReader() = default;
    TypeReader(Type & value) : m_value(value) {}

    friend std::istream & operator>>(std::istream & in, TypeReader & reader) {
        valhalla::utils::checkers::skip_spaces<char,valhalla::utils::checkers::is_space> skipSpace;

        skipSpace(in);
        in >> reader.m_value;
        skipSpace(in);

        return in;
    }

};

TEST(DataLoaderTestSuite, IntegerDataLoaderV1Test) {
    int actual, expected = 10;
    std::stringstream in("(10)");

    valhalla::utils::loaders::loader::v1::dataLoader<
        int,
        TypeReader<int>,
        char,
        valhalla::utils::checkers::is_character<char, '('>,
        valhalla::utils::checkers::is_character<char, ')'>,
        valhalla::utils::checkers::is_space
    > intDataLoader(actual);

    in >> intDataLoader;

    ASSERT_EQ(actual, expected);
}

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

TEST(DataLoaderTestSuite, IntegerDataDataLoaderV1Test) {
    IntegerData actual, expected(10);
    std::stringstream in("(10)");

    valhalla::utils::loaders::loader::v1::dataLoader<
        IntegerData,
        TypeReader<IntegerData>,
        char,
        valhalla::utils::checkers::is_character<char, '('>,
        valhalla::utils::checkers::is_character<char, ')'>,
        valhalla::utils::checkers::is_space
    > intDataLoader(actual);

    in >> intDataLoader;

    ASSERT_EQ(actual, expected);
}

class CompoundData {
    int m_value;
    long m_a_year;
public:
    CompoundData() = default;
    CompoundData(int value, long year) :  m_value(value), m_a_year(year) {}

    void set_value(int value) { m_value = value; }
    void set_year(long year) { m_a_year = year; }

    friend std::istream & operator>>(std::istream & in, CompoundData & data) {
        return in >> data.m_value >> data.m_a_year;
    }

    friend inline bool operator==(const CompoundData & lhs, const CompoundData & rhs) {
        return lhs.m_value == rhs.m_value && lhs.m_a_year == rhs.m_a_year;
    }
};

TEST(DataLoaderTestSuite, CompoundDataDataLoaderV1Test) {
    CompoundData actual, expected(10,1900);
    std::stringstream in("(10 1900)");

    valhalla::utils::loaders::loader::v1::dataLoader<
        CompoundData,
        TypeReader<CompoundData>,
        char,
        valhalla::utils::checkers::is_character<char, '('>,
        valhalla::utils::checkers::is_character<char, ')'>,
        valhalla::utils::checkers::is_space
    > intDataLoader(actual);

    in >> intDataLoader;

    ASSERT_EQ(actual, expected);
}

class ComplexDataType {
    std::string m_name;
    int m_age;
    long m_a_year;
public:
    ComplexDataType() = default;
    ComplexDataType(std::string & name, int age, long year) : m_name(name), m_age(age), m_a_year(year) {}
    ComplexDataType(std::string name, int age, long year) : m_name(name), m_age(age), m_a_year(year) {}

    friend std::istream & operator>>(std::istream & in, ComplexDataType & data) {

        ::loaders::primitive::primitiveLoader<
          std::string,
          char,
          ::checkers::is_space_or<','>
        > nameLoader(&data.m_name);

        ::loaders::primitive::primitiveLoader<
          int,
          char,
          ::checkers::is_space_or<','>
        > ageLoader(&data.m_age);

        ::loaders::primitive::primitiveLoader<
          long,
          char,
          ::checkers::is_space_or<','>
        > yearLoader(&data.m_a_year);

        return in >> nameLoader >> ageLoader >> yearLoader;
    }

    friend bool operator==(const ComplexDataType & lhs, const ComplexDataType & rhs);

    friend std::basic_ostream<char> & operator<<(std::basic_ostream<char> & out, const ComplexDataType & data) {
        return out << "ComplexDataType[ name=\"" << data.m_name << "\" age=" << data.m_age << " year=" << data.m_a_year << " ]";
    }
};

inline bool operator==(const ComplexDataType & lhs, const ComplexDataType & rhs) {
    return lhs.m_name == rhs.m_name && lhs.m_age == rhs.m_age && lhs.m_a_year == rhs.m_a_year;
}

TEST(DataLoaderTestSuite, ComplexDataTypeDataLoaderV1Test) {
    ComplexDataType actual, expected(std::string("Me"), 10,1900);
    std::stringstream in("(Me 10, 1900)");

    valhalla::utils::loaders::loader::v1::dataLoader<
        ComplexDataType,
        TypeReader<ComplexDataType>,
        char,
        valhalla::utils::checkers::is_character<char, '('>,
        valhalla::utils::checkers::is_character<char, ')'>,
        valhalla::utils::checkers::is_space_or<','>
    > intDataLoader(actual);

    in >> intDataLoader;

    ASSERT_EQ(actual, expected);
}

TEST(DataLoaderTestSuite, ComplexDataTypeUsingTypeReaderDataLoaderV1Test) {
    ComplexDataType actual, expected(std::string("Me"), 10,1900);
    std::stringstream in("(Me 10, 1900)");

    valhalla::utils::loaders::loader::v1::dataLoader<
        ComplexDataType,
        valhalla::utils::loaders::loader::v1::typeReader<ComplexDataType, char, valhalla::utils::checkers::is_space_or<','>>,
        char,
        valhalla::utils::checkers::is_character<char, '('>,
        valhalla::utils::checkers::is_character<char, ')'>,
        valhalla::utils::checkers::is_space_or<','>
    > complexDataTypeDataLoader(actual);

    in >> complexDataTypeDataLoader;

    ASSERT_EQ(actual, expected);
}

class VectorOfVectorDataType {
    std::vector<std::vector<ComplexDataType>> & m_container;
public:
    VectorOfVectorDataType() = default;
    VectorOfVectorDataType(std::vector<std::vector<ComplexDataType>> & container) : m_container(container) {}

    friend std::istream & operator>>(std::istream & in, VectorOfVectorDataType & data) {
        valhalla::utils::checkers::skip_spaces<char, valhalla::utils::checkers::is_space_or<','>> skipSpace;
        valhalla::utils::checkers::is_character<char, '['> openChar;
        valhalla::utils::checkers::is_character<char, ']'> closeChar;

        skipSpace(in);

        if (openChar(in)) {
            skipSpace(in);
            while(closeChar(in) == false) {
                std::vector<ComplexDataType> value;

                valhalla::utils::loaders::vectors::vectorLoader<
                  ComplexDataType,
                  std::vector<ComplexDataType>,
                  char,
                  ::checkers::is_space_or<',','(',')'>
                > inputLoader(value,'[', ']');
                in >> inputLoader;

                data.m_container.push_back(value);
            } // while
            return in;
        } // if

        throw std::runtime_error("Invalid input encountered");
    }
};

std::istream & operator>>(std::istream & in, std::vector<ComplexDataType> & container) {
    valhalla::utils::checkers::skip_spaces<char, valhalla::utils::checkers::is_space_or<','>> skipSpace;

    skipSpace(in);
    while (static_cast<char>(in.peek()) != ']') {
        ComplexDataType entry;
        valhalla::utils::loaders::loader::v1::typeReader<
            ComplexDataType,
            char,
            valhalla::utils::checkers::is_space_or<','>,
            valhalla::utils::checkers::is_character<char, '('>,
            valhalla::utils::checkers::is_character<char, ')'>
        > reader(entry);
        in >> reader;

        container.push_back(entry);
        skipSpace(in);
    } // while

    return in;
};

std::istream & operator>>(std::istream & in, std::vector<std::vector<ComplexDataType>> & container) {

    valhalla::utils::checkers::skip_spaces<char, valhalla::utils::checkers::is_space_or<','>> skipSpace;

    skipSpace(in);
    while (static_cast<char>(in.peek() != ']')) {
        std::vector<ComplexDataType> entry;

        valhalla::utils::loaders::loader::v1::dataLoader<
            std::vector<ComplexDataType>,
            valhalla::utils::loaders::loader::v1::typeReader<std::vector<ComplexDataType>, char, valhalla::utils::checkers::is_space_or<','>>,
            char,
            valhalla::utils::checkers::is_character<char, '['>,
            valhalla::utils::checkers::is_character<char, ']'>,
            valhalla::utils::checkers::is_space_or<','>
        > complexDataTypeDataLoader(entry);

        in >> complexDataTypeDataLoader;
        container.push_back(entry);

        skipSpace(in);
    }

    return in;
};

TEST(DataLoaderTestSuite, VectorOfVectorComplexDataLoaderV1Test) {
    std::vector<std::vector<ComplexDataType>> actual, expected = { { { std::string("Me"), 10,1900 } } };
    std::stringstream in("[ [ ( Me 10, 1900 ) ] ]");

    valhalla::utils::loaders::loader::v1::dataLoader<
        std::vector<std::vector<ComplexDataType>>,
        valhalla::utils::loaders::loader::v1::typeReader<std::vector<std::vector<ComplexDataType>>, char, valhalla::utils::checkers::is_space_or<','>>,
        char,
        valhalla::utils::checkers::is_character<char, '['>,
        valhalla::utils::checkers::is_character<char, ']'>,
        valhalla::utils::checkers::is_space_or<','>
    > complexDataTypeDataLoader(actual);

    in >> complexDataTypeDataLoader;

    ASSERT_EQ(actual, expected);
}

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

std::istream & operator>>(std::istream & in, A & a) {
    valhalla::utils::checkers::skip_spaces<char, valhalla::utils::checkers::is_space_or<','>> skipSpace;
    int x, y;

    ::loaders::primitive::primitiveLoader<
      int,
      char,
      ::checkers::is_space
    > xLoader(&x);
    in >> xLoader;

    skipSpace(in);

    ::loaders::primitive::primitiveLoader<
      int,
      char,
      ::checkers::is_space
    > yLoader(&y);
    in >> yLoader;

    a = A(x,y);

    return in;
}

std::istream & operator>>(std::istream & in, B & b) {
    valhalla::utils::checkers::skip_spaces<char, valhalla::utils::checkers::is_space_or<','>> skipSpace;
    int x, y;

    ::loaders::primitive::primitiveLoader<
      int,
      char,
      ::checkers::is_space
    > xLoader(&x);
    in >> xLoader;

    skipSpace(in);

    ::loaders::primitive::primitiveLoader<
      int,
      char,
      ::checkers::is_space
    > yLoader(&y);
    in >> yLoader;

    b = B(x,y);

    return in;
}

std::istream & operator>>(std::istream & in, C & c) {
    valhalla::utils::checkers::skip_spaces<char, valhalla::utils::checkers::is_space_or<','>> skipSpace;
    A a;

    valhalla::utils::loaders::loader::v1::dataLoader<
        A,
        valhalla::utils::loaders::loader::v1::typeReader<
            A,
            char,
            valhalla::utils::checkers::is_space_or<','>,
            valhalla::utils::checkers::is_character<char,'{'>,
            valhalla::utils::checkers::is_character<char, '}'>
        >,
        char,
        valhalla::utils::checkers::is_character_noop<char>,
        valhalla::utils::checkers::is_character_noop<char>,
        valhalla::utils::checkers::is_space
    > aLoader(a);
    in >> aLoader;

    skipSpace(in);

    B b;

    valhalla::utils::loaders::loader::v1::dataLoader<
        B,
        valhalla::utils::loaders::loader::v1::typeReader<
            B,
            char,
            valhalla::utils::checkers::is_space_or<','>,
            valhalla::utils::checkers::is_character<char,'{'>,
            valhalla::utils::checkers::is_character<char, '}'>
        >,
        char,
        valhalla::utils::checkers::is_character_noop<char>,
        valhalla::utils::checkers::is_character_noop<char>,
        valhalla::utils::checkers::is_space
    > bLoader(b);
    in >> bLoader;

    c = C(a,b);

    return in;
}

TEST(DataLoaderTestSuite, MultipleLayerObjectDataLoaderV1Test) {
    C actual, expected = { { 10, 11 }, { 12, 13 } };
    std::stringstream in("{ { 10, 11 }, { 12, 13 } }");

    valhalla::utils::loaders::loader::v1::dataLoader<
        C,
        valhalla::utils::loaders::loader::v1::typeReader<
            C,
            char,
            valhalla::utils::checkers::is_space_or<','>,
            valhalla::utils::checkers::is_character_noop<char>,
            valhalla::utils::checkers::is_character_noop<char>
        >,
        char,
        valhalla::utils::checkers::is_character<char,'{'>,
        valhalla::utils::checkers::is_character<char, '}'>,
        valhalla::utils::checkers::is_space_or<','>
    > cLoader(actual);
    in >> cLoader;

    ASSERT_EQ(actual, expected);
}

/******************************************************************************************
 *
 *  Version 2 Tests Status
 *
 *      [ ] primitive types, mainly int
 *      [ ] simple object containing a single field
 *      [x] simple object containing two or more fields
 *      [x] complex object containing one or more non-primitive type fields
 *      [x] container containing a primitive
 *      [ ] container containing a non-primitive type
 *      [ ] container of container of primitive
 *      [ ] container of container of non-primitve type
 *      [x] map containing a primitive
 *      [ ] map containing a non-primitive type
 *      [ ] map of map of primitive
 *      [ ] map of map of non-primitve type
 *
 ******************************************************************************************/

template<int states = 2, typename Char = char>
class AReader : public valhalla::utils::loaders::loader::v2::dataReader<A, Char, states> {
    int m_a_x, m_a_y;
protected:
    std::istream & load(std::istream & in) override {
        switch(this->state()) {
            case 0:
                // Load a
                in >> m_a_x;
                break;
            case 1:
                // Load b
                in >> m_a_y;
                this->get_data() = A(m_a_x,m_a_y);
                break;
        } // switch

        return in;
    }
public:
    AReader() = default;
    AReader(A & a) : valhalla::utils::loaders::loader::v2::dataReader<A, Char, states>(a) {}
};

TEST(DataLoaderTestSuite, DataLoaderV2Test) {
    A actual, expected = { 10, 11 };
    std::stringstream in("{ 10, 11 }");

    valhalla::utils::loaders::loader::v2::dataLoader<
        A,
        char,
        AReader<>,
        valhalla::utils::checkers::is_character<char,'{'>,
        valhalla::utils::checkers::is_character<char,'}'>,
        valhalla::utils::checkers::is_space_or<','>
    > aLoader(actual);
    in >> aLoader;

    ASSERT_EQ(actual, expected);
}

TEST(DataLoaderTestSuite, AFieldDataLoaderV2Test) {
    A actual, expected = { 10, 11 };
    std::stringstream in("{ 10, 11 }");

    valhalla::utils::loaders::loader::v2::dataLoader<
        A,
        char,
        AReader<2>,
        valhalla::utils::checkers::is_character<char,'{'>,
        valhalla::utils::checkers::is_character<char, '}'>,
        valhalla::utils::checkers::is_space_or<','>
    > cLoader(actual);
    in >> cLoader;

    ASSERT_EQ(actual, expected);
}

class CReader : public valhalla::utils::loaders::loader::v2::dataReader<C,char,4> {
    int m_a_x, m_a_y, m_b_x, m_b_y;
protected:
    std::istream & load(std::istream & in) override {
        switch(state()) {
            case 0: // Load m_a_x
                in >> m_a_x;
                break;
            case 1: // Load m_a_y
                in >> m_a_y;
                break;
            case 2: // Load m_b_x
                in >> m_b_x;
                break;
            case 3: // Load m_b_y
                in >> m_b_y;
                get_data() = C(A(m_a_x, m_a_y), B(m_b_x, m_b_y));
                break;
        } // switch

        return in;
    }
public:
    CReader() = default;
    CReader(C & c) : dataReader(c) {}
};

TEST(DataLoaderTestSuite, PiecewisePopulateCObjectDataLoaderV2Test) {
    C actual, expected = { { 10, 11 }, { 12, 13 } };
    std::stringstream in("{ 10, 11, 12, 13 }");

    valhalla::utils::loaders::loader::v2::dataLoader<
        C,
        char,
        CReader,
        valhalla::utils::checkers::is_character<char,'{'>,
        valhalla::utils::checkers::is_character<char, '}'>,
        valhalla::utils::checkers::is_space_or<','>
    > cLoader(actual);
    in >> cLoader;

    ASSERT_EQ(actual, expected);
}

template<typename Type>
class TypeExReader : public valhalla::utils::loaders::loader::v2::dataReader<Type,char,2> {
    int m_x, y;
protected:
    std::istream & load(std::istream & in) override {
        switch(this->state()) {
            case 0:
                in >> m_x;
                break;
            case 1:
                in >> y;
                this->get_data() = Type(m_x, y);
                break;
        }
        return in;
    }
public:
    TypeExReader() = default;
    TypeExReader(Type & type) : valhalla::utils::loaders::loader::v2::dataReader<Type,char,2>(type) {}
};

class CReaderEx : public valhalla::utils::loaders::loader::v2::dataReader<C,char,2> {
    A m_a;
    B m_b;

    template<typename Type>
    void load(std::istream & in, Type & type) {
        valhalla::utils::loaders::loader::v2::dataLoader<
            Type,
            char,
            TypeExReader<Type>,
            valhalla::utils::checkers::is_character<char,'{'>,
            valhalla::utils::checkers::is_character<char,'}'>,
            valhalla::utils::checkers::is_space_or<','>
        > loader(type);
        in >> loader;
    }
protected:
    std::istream & load(std::istream & in) override {
        switch(this->state()) {
            case 0: // Load m_a
                load(in, m_a);
                break;
            case 1: // Load m_b
                load(in, m_b);
                this->get_data() = C(m_a, m_b);
                break;
        } // switch

        return in;
    }
public:
    CReaderEx() = default;
    CReaderEx(C & c) : valhalla::utils::loaders::loader::v2::dataReader<C,char,2>(c) {}
};

TEST(DataLoaderTestSuite, PiecewisePopulateCObjectV2DataLoaderV2Test) {
    C actual, expected = { { 10, 11 }, { 12, 13 } };
    std::stringstream in("{ { 10, 11 }, { 12, 13 } }");

    valhalla::utils::loaders::loader::v2::dataLoader<
        C,
        char,
        CReaderEx,
        valhalla::utils::checkers::is_character<char,'{'>,
        valhalla::utils::checkers::is_character<char, '}'>,
        valhalla::utils::checkers::is_space_or<','>
    > cLoader(actual);
    in >> cLoader;

    ASSERT_EQ(actual, expected);
}

class VectorReader : public valhalla::utils::loaders::loader::v2::dataReader<std::vector<int>, char> {
protected:
    std::istream & load(std::istream & in) override {
        int value;
        in >> value;
        this->get_data().push_back(value);
        return in;
    }
public:
    VectorReader() = default;
    VectorReader(std::vector<int> & type) : dataReader(type) {}
};

TEST(DataLoaderTestSuite, ContainerDataLoaderV2Test) {
    std::vector<int> actual, expected = { 1, 2, 3, 4, 5};
    std::stringstream in("{ 1, 2, 3, 4, 5 }");

    valhalla::utils::loaders::loader::v2::dataLoader<
        std::vector<int>,
        char,
        VectorReader,
        valhalla::utils::checkers::is_character<char,'{'>,
        valhalla::utils::checkers::is_character<char,'}'>,
        valhalla::utils::checkers::is_space_or<','>
    > loader(actual);
    in >> loader;

    ASSERT_EQ(actual, expected);
}

template<typename Type>
class MapEntryReader : public valhalla::utils::loaders::loader::v2::dataReader<Type,char,2> {
    int key, value;
protected:
    std::istream & load(std::istream & in) override {
        switch(this->state()) {
            case 0:
                in >> key;
                break;
            case 1:
                in >> value;
                this->get_data()[key] = value;
                break;
        } // switch
        return in;
    }
public:
 MapEntryReader() = default;
 MapEntryReader(Type & type) : valhalla::utils::loaders::loader::v2::dataReader<Type,char,2>(type) {}
};

template<typename Type>
class MapReader : public valhalla::utils::loaders::loader::v2::dataReader<Type,char,1> {
protected:
    std::istream & load(std::istream & in) override {
        valhalla::utils::loaders::loader::v2::dataLoader<
            Type,
            char,
            MapEntryReader<Type>,
            valhalla::utils::checkers::is_character<char,'{'>,
            valhalla::utils::checkers::is_character<char,'}'>,
            valhalla::utils::checkers::is_space_or<','>
        > loader(this->get_data());
        return in >> loader;
    }
public:
 MapReader() = default;
 MapReader(Type & type) : valhalla::utils::loaders::loader::v2::dataReader<Type,char,1>(type) {}
};

TEST(DataLoaderTestSuite, MapDataLoaderV2Test) {
    std::map<int,int> actual, expected = { { 1, 2 }, { 3, 4 }, { 5, 6 } };
    std::stringstream in("{ { 1, 2 }, { 3, 4 }, { 5, 6 } }");

    valhalla::utils::loaders::loader::v2::dataLoader<
        std::map<int,int>,
        char,
        MapReader<std::map<int,int>>,
        valhalla::utils::checkers::is_character<char,'{'>,
        valhalla::utils::checkers::is_character<char,'}'>,
        valhalla::utils::checkers::is_space_or<','>
    > loader(actual);
    in >> loader;

    ASSERT_EQ(actual, expected);
}

/******************************************************************************************
 *
 *  Version 3 Tests Status
 *
 *      [x] primitive types, mainly int
 *      [ ] simple object containing a single field
 *      [x] simple object containing two or more fields
 *      [x] complex object containing one or more non-primitive type fields
 *      [x] container containing a primitive
 *      [ ] container containing a non-primitive type
 *      [ ] container of container of primitive
 *      [ ] container of container of non-primitve type
 *      [ ] map containing a primitive
 *      [ ] map containing a non-primitive type
 *      [ ] map of map of primitive
 *      [ ] map of map of non-primitve type
 *
 ******************************************************************************************/

TEST(DataLoaderTestSuite, PrimitiveDataLoaderV3Test) {
    int actual, expected = 10;
    std::stringstream in(" 10 ");

    valhalla::utils::loaders::loader::v3::dataLoader<
        int,
        char,
        valhalla::utils::loaders::loader::v3::dataReader<
            int,
            char,
            valhalla::utils::loaders::loader::v3::reader<int,char>
        >,
        valhalla::utils::checkers::is_character_noop<char>,
        valhalla::utils::checkers::is_no_character<char>,
        valhalla::utils::checkers::is_space
    > loader(actual);
    in >> loader;

    ASSERT_EQ(actual, expected);
}

struct a_reader {
    int m_x;
    std::istream & operator()(std::istream & in, A & a, int state) {
        switch(state) {
            case 0:
                in >> m_x;
                break;
            case 1:
                int y;
                in >> y;
                a = A(m_x, y);
                break;
            default:
                throw std::runtime_error("Invalid state passed");
        } // switch

        return in;
    }
};

TEST(DataLoaderTestSuite, ADataLoaderV3Test) {
    A actual, expected = { 10, 11 };
    std::stringstream in(" { 10, 11 } ");

    valhalla::utils::loaders::loader::v3::dataLoader<
        A,
        char,
        valhalla::utils::loaders::loader::v3::dataReader<
            A,
            char,
            a_reader,
            2
        >,
        valhalla::utils::checkers::is_character<char,'{'>,
        valhalla::utils::checkers::is_character<char,'}'>,
        valhalla::utils::checkers::is_space_or<','>
    > loader(actual);
    in >> loader;

    ASSERT_EQ(actual, expected);
}

struct b_reader {
    int m_x;
    std::istream & operator()(std::istream & in, B & b, int state) {
        switch(state) {
            case 0:
                in >> m_x;
                break;
            case 1:
                int y;
                in >> y;
                b = B(m_x, y);
                break;
            default:
                throw std::runtime_error("Invalid state passed");
        } // switch

        return in;
    }
};

struct c_reader {
    A m_a;
    std::istream & operator()(std::istream & in, C & c, int state) {
        switch(state) {
            case 0:
                {
                    valhalla::utils::loaders::loader::v3::dataLoader<
                        A,
                        char,
                        valhalla::utils::loaders::loader::v3::dataReader<
                            A,
                            char,
                            a_reader,
                            2
                        >,
                        valhalla::utils::checkers::is_character<char,'{'>,
                        valhalla::utils::checkers::is_character<char,'}'>,
                        valhalla::utils::checkers::is_space_or<','>
                    > loader(m_a);
                    in >> loader;
                }
                break;
            case 1:
                {
                    B b;
                    valhalla::utils::loaders::loader::v3::dataLoader<
                        B,
                        char,
                        valhalla::utils::loaders::loader::v3::dataReader<
                            B,
                            char,
                            b_reader,
                            2
                        >,
                        valhalla::utils::checkers::is_character<char,'{'>,
                        valhalla::utils::checkers::is_character<char,'}'>,
                        valhalla::utils::checkers::is_space_or<','>
                    > loader(b);
                    in >> loader;
                    c = C(m_a, b);
                }
                break;
            default:
                throw std::runtime_error("Invalid state passed");
        } // switch

        return in;
    }
};

TEST(DataLoaderTestSuite, CDataLoaderV3Test) {
    C actual, expected = { { 10, 11 }, { 12, 13 } };
    std::stringstream in(" { { 10, 11 }, { 12, 13 } } ");

    valhalla::utils::loaders::loader::v3::dataLoader<
        C,
        char,
        valhalla::utils::loaders::loader::v3::dataReader<
            C,
            char,
            c_reader,
            2
        >,
        valhalla::utils::checkers::is_character<char,'{'>,
        valhalla::utils::checkers::is_character<char,'}'>,
        valhalla::utils::checkers::is_space_or<','>
    > loader(actual);
    in >> loader;

    ASSERT_EQ(actual, expected);
}

class vector_reader {
public:
    std::basic_istream<char> & operator()(std::basic_istream<char> & in, std::vector<int> & vec, int state) {
        int value;

        valhalla::utils::loaders::loader::v3::dataLoader<
            int,
            char,
            valhalla::utils::loaders::loader::v3::dataReader<
                int,
                char,
                valhalla::utils::loaders::loader::v3::reader<int,char>
            >,
            valhalla::utils::checkers::is_character_noop<char>,
            valhalla::utils::checkers::is_no_character<char>,
            valhalla::utils::checkers::is_space_or<','>
        > loader(value);
        in >> loader;

        vec.push_back(value);

        return in;
    }
};

TEST(DataLoaderTestSuite, VectorDataLoaderV3Test) {
    std::vector<int> actual, expected = { 10, 11, 12, 13 };
    std::stringstream in(" { 10, 11, 12, 13 } ");

    valhalla::utils::loaders::loader::v3::dataLoader<
        std::vector<int>,
        char,
        valhalla::utils::loaders::loader::v3::dataReader<
            std::vector<int>,
            char,
            vector_reader,
            1
        >,
        valhalla::utils::checkers::is_character<char,'{'>,
        valhalla::utils::checkers::is_character<char,'}'>,
        valhalla::utils::checkers::is_space_or<','>
    > loader(actual);
    in >> loader;

    ASSERT_EQ(actual, expected);
}

/******************************************************************************************
 *
 *  Version 4 Tests Status
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
 *
 ******************************************************************************************/

TEST(DataLoaderTestSuite, IntegerDataLoaderV4Test) {
    int actual, expected = 13;
    std::stringstream in(" 13 ");

    valhalla::utils::loaders::loader::v4::dataLoader<
        int,
        char,
        valhalla::utils::loaders::loader::v4::reader<int,char>,
        1,
        valhalla::utils::checkers::is_character_noop<char>,
        valhalla::utils::checkers::is_no_character<char>,
        valhalla::utils::checkers::is_space_or<','>
    > loader(actual);
    in >> loader;

    ASSERT_EQ(actual, expected);
}

TEST(DataLoaderTestSuite, IntegerDataObjectDataLoaderV4Test) {
    IntegerData actual, expected = { 13 };
    std::stringstream in(" { 13 } ");

    valhalla::utils::loaders::loader::v4::dataLoader<
        IntegerData,
        char,
        valhalla::utils::loaders::loader::v4::reader<IntegerData,char>,
        1,
        valhalla::utils::checkers::is_character<char,'{'>,
        valhalla::utils::checkers::is_character<char,'}'>,
        valhalla::utils::checkers::is_space_or<','>
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

TEST(DataLoaderTestSuite, AObjectDataLoaderV4Test) {
    A actual, expected = { 13, 15 };
    std::stringstream in(" { 13, 15 } ");

    valhalla::utils::loaders::loader::v4::dataLoader<
        A,
        char,
        AObjectReader,
        2,
        valhalla::utils::checkers::is_character<char,'{'>,
        valhalla::utils::checkers::is_character<char,'}'>,
        valhalla::utils::checkers::is_space_or<','>
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
                    valhalla::utils::loaders::loader::v4::dataLoader<
                        A,
                        char,
                        AObjectReader,
                        2,
                        valhalla::utils::checkers::is_character<char,'{'>,
                        valhalla::utils::checkers::is_character<char,'}'>,
                        valhalla::utils::checkers::is_space_or<','>
                    > loader(m_a);
                    in >> loader;
                }
                break;
            case 1:
                {
                    B b;
                    valhalla::utils::loaders::loader::v4::dataLoader<
                        B,
                        char,
                        BObjectReader,
                        2,
                        valhalla::utils::checkers::is_character<char,'{'>,
                        valhalla::utils::checkers::is_character<char,'}'>,
                        valhalla::utils::checkers::is_space_or<','>
                    > loader(b);
                    in >> loader;
                    c = C(m_a,b);
                }
                break;
        } // switch
        return in;
    }
};

TEST(DataLoaderTestSuite, CObjectDataLoaderV4Test) {
    C actual, expected = { { 13, 15 }, { 17, 21 } };
    std::stringstream in(" { { 13, 15 }, { 17, 21 } } ");

    valhalla::utils::loaders::loader::v4::dataLoader<
        C,
        char,
        CObjectReader,
        2,
        valhalla::utils::checkers::is_character<char,'{'>,
        valhalla::utils::checkers::is_character<char,'}'>,
        valhalla::utils::checkers::is_space_or<','>
    > loader(actual);
    in >> loader;

    ASSERT_EQ(actual, expected);
}

struct IntegerVectorReader {
    std::istream & operator()(std::istream & in, std::vector<int> & vec, int state) {
        int value;
        in >> value;
        vec.push_back(value);
        return in;
    }
};

TEST(DataLoaderTestSuite, IntegerVectorDataLoaderV4Test) {
    std::vector<int> actual, expected = { 13, 15, 17, 21 };
    std::stringstream in(" { 13, 15, 17, 21 } ");

    valhalla::utils::loaders::loader::v4::dataLoader<
        std::vector<int>,
        char,
        IntegerVectorReader,
        1,
        valhalla::utils::checkers::is_character<char,'{'>,
        valhalla::utils::checkers::is_character<char,'}'>,
        valhalla::utils::checkers::is_space_or<','>
    > loader(actual);
    in >> loader;

    ASSERT_EQ(actual, expected);
}

struct AVectorReader {
    std::istream & operator()(std::istream & in, std::vector<A> & vec, int state) {
        A a;
        valhalla::utils::loaders::loader::v4::dataLoader<
            A,
            char,
            AObjectReader,
            2,
            valhalla::utils::checkers::is_character<char,'{'>,
            valhalla::utils::checkers::is_character<char,'}'>,
            valhalla::utils::checkers::is_space_or<','>
        > loader(a);
        in >> loader;
        vec.push_back(a);
        return in;
    }
};

TEST(DataLoaderTestSuite, AVectorDataLoaderV4Test) {
    std::vector<A> actual, expected = { { 13, 15 }, { 17, 21 } };
    std::stringstream in(" { { 13, 15 }, { 17, 21 } } ");

    valhalla::utils::loaders::loader::v4::dataLoader<
        std::vector<A>,
        char,
        AVectorReader,
        1,
        valhalla::utils::checkers::is_character<char,'{'>,
        valhalla::utils::checkers::is_character<char,'}'>,
        valhalla::utils::checkers::is_space_or<','>
    > loader(actual);
    in >> loader;

    ASSERT_EQ(actual, expected);
}

struct IntegerVectorVectorReader {
    std::istream & operator()(std::istream & in, std::vector<std::vector<int>> & vecvec, int state) {
        std::vector<int> vec;

        valhalla::utils::loaders::loader::v4::dataLoader<
            std::vector<int>,
            char,
            IntegerVectorReader,
            1,
            valhalla::utils::checkers::is_character<char,'{'>,
            valhalla::utils::checkers::is_character<char,'}'>,
            valhalla::utils::checkers::is_space_or<','>
        > loader(vec);
        in >> loader;

        vecvec.push_back(vec);

        return in;
    }
};

TEST(DataLoaderTestSuite, IntegerVectorVectorDataLoaderV4Test) {
    std::vector<std::vector<int>> actual, expected = { { 13, 15 }, { 17, 21 } };
    std::stringstream in(" { { 13, 15 }, { 17, 21 } } ");

    valhalla::utils::loaders::loader::v4::dataLoader<
        std::vector<std::vector<int>>,
        char,
        IntegerVectorVectorReader,
        1,
        valhalla::utils::checkers::is_character<char,'{'>,
        valhalla::utils::checkers::is_character<char,'}'>,
        valhalla::utils::checkers::is_space_or<','>
    > loader(actual);
    in >> loader;

    ASSERT_EQ(actual, expected);
}

struct AVectorVectorReader {
    std::istream & operator()(std::istream & in, std::vector<std::vector<A>> & vecvec, int state) {
        std::vector<A> vec;

        valhalla::utils::loaders::loader::v4::dataLoader<
            std::vector<A>,
            char,
            AVectorReader,
            1,
            valhalla::utils::checkers::is_character<char,'{'>,
            valhalla::utils::checkers::is_character<char,'}'>,
            valhalla::utils::checkers::is_space_or<','>
        > loader(vec);
        in >> loader;

        vecvec.push_back(vec);

        return in;
    }
};

TEST(DataLoaderTestSuite, AVectorVectorDataLoaderV4Test) {
    std::vector<std::vector<A>> actual, expected = { { { 13, 15 }, { 9, 10 } }, { { 17, 21 }, { 1, 3 } } };
    std::stringstream in(" { { { 13, 15 }, { 9, 10 } }, { { 17, 21 }, { 1, 3 } } } ");

    valhalla::utils::loaders::loader::v4::dataLoader<
        std::vector<std::vector<A>>,
        char,
        AVectorVectorReader,
        1,
        valhalla::utils::checkers::is_character<char,'{'>,
        valhalla::utils::checkers::is_character<char,'}'>,
        valhalla::utils::checkers::is_space_or<','>
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

        valhalla::utils::loaders::loader::v4::dataLoader<
            int,
            char,
            valhalla::utils::loaders::loader::v4::reader<int,char>,
            1,
            valhalla::utils::checkers::is_character_noop<char>,
            valhalla::utils::checkers::is_no_character<char>
        > loader(*value);
        in >> loader;

        return in;
    }
};

struct IntegerMapReader {
    std::istream & operator()(std::istream & in, std::map<int,int> & dict, int state) {
        std::pair<int,int> entry;

        valhalla::utils::loaders::loader::v4::dataLoader<
            std::pair<int,int>,
            char,
            IntegerPairReader,
            2,
            valhalla::utils::checkers::is_character<char,'{'>,
            valhalla::utils::checkers::is_character<char,'}'>,
            valhalla::utils::checkers::is_space_or<','>
        > loader(entry);
        in >> loader;

        dict[entry.first] = entry.second;

        return in;
    }
};

TEST(DataLoaderTestSuite, IntegerIntegerMapDataLoaderV4Test) {
    std::map<int,int> actual, expected = { { 13, 15 }, { 9, 10 }, { 17, 21 }, { 1, 3 } };
    std::stringstream in(" { { 13, 15 }, { 9, 10 }, { 17, 21 }, { 1, 3 } } ");

    valhalla::utils::loaders::loader::v4::dataLoader<
        std::map<int,int>,
        char,
        IntegerMapReader,
        1,
        valhalla::utils::checkers::is_character<char,'{'>,
        valhalla::utils::checkers::is_character<char,'}'>,
        valhalla::utils::checkers::is_space_or<','>
    > loader(actual);
    in >> loader;

    ASSERT_EQ(actual, expected);
}

struct IntegerAPairReader {
    std::istream & operator()(std::istream & in, std::pair<int,A> & entry, int state) {
        switch(state) {
            case 0:
                {
                    valhalla::utils::loaders::loader::v4::dataLoader<
                        int,
                        char,
                        valhalla::utils::loaders::loader::v4::reader<int,char>,
                        1,
                        valhalla::utils::checkers::is_character_noop<char>,
                        valhalla::utils::checkers::is_no_character<char>
                    > loader(entry.first);
                    in >> loader;
                }
                break;
            case 1:
                {
                    valhalla::utils::loaders::loader::v4::dataLoader<
                        A,
                        char,
                        AObjectReader,
                        2,
                        valhalla::utils::checkers::is_character<char,'{'>,
                        valhalla::utils::checkers::is_character<char,'}'>,
                        valhalla::utils::checkers::is_space_or<','>
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

        valhalla::utils::loaders::loader::v4::dataLoader<
            std::pair<int,A>,
            char,
            IntegerAPairReader,
            2,
            valhalla::utils::checkers::is_character<char,'{'>,
            valhalla::utils::checkers::is_character<char,'}'>,
            valhalla::utils::checkers::is_space_or<','>
        > loader(entry);
        in >> loader;

        dict[entry.first] = entry.second;

        return in;
    }
};

TEST(DataLoaderTestSuite, IntegerAMapDataLoaderV4Test) {
    std::map<int,A> actual, expected = { { 13, { 15, 16 } }, { 9, { 10, 11 } }, { 17, { 21, 22 } }, { 1, { 3, 4 } } };
    std::stringstream in(" { { 13, { 15, 16 } }, { 9, { 10, 11 } }, { 17, { 21, 22 } }, { 1, { 3, 4 } } } ");

    valhalla::utils::loaders::loader::v4::dataLoader<
        std::map<int,A>,
        char,
        IntegerAMapReader,
        1,
        valhalla::utils::checkers::is_character<char,'{'>,
        valhalla::utils::checkers::is_character<char,'}'>,
        valhalla::utils::checkers::is_space_or<','>
    > loader(actual);
    in >> loader;

    ASSERT_EQ(actual, expected);
}

struct IntegerMapPairReader {
    std::istream & operator()(std::istream & in, std::pair<int,std::map<int,int>> & entry, int state) {
        switch (state) {
            case 0:
                {
                    valhalla::utils::loaders::loader::v4::dataLoader<
                        int,
                        char,
                        valhalla::utils::loaders::loader::v4::reader<int,char>,
                        1,
                        valhalla::utils::checkers::is_character_noop<char>,
                        valhalla::utils::checkers::is_no_character<char>
                    > loader(entry.first);
                    in >> loader;
                }
                break;

            case 1:
                {
                    valhalla::utils::loaders::loader::v4::dataLoader<
                        std::map<int,int>,
                        char,
                        IntegerMapReader,
                        1,
                        valhalla::utils::checkers::is_character<char,'{'>,
                        valhalla::utils::checkers::is_character<char,'}'>,
                        valhalla::utils::checkers::is_space_or<','>
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

        valhalla::utils::loaders::loader::v4::dataLoader<
            std::pair<int, std::map<int,int>>,
            char,
            IntegerMapPairReader,
            2,
            valhalla::utils::checkers::is_character<char,'{'>,
            valhalla::utils::checkers::is_character<char,'}'>,
            valhalla::utils::checkers::is_space_or<','>
        > loader(entry);
        in >> loader;

        dict[entry.first] = entry.second;

        return in;
    }
};

TEST(DataLoaderTestSuite, IntegerIntegerMapMapDataLoaderV4Test) {
    std::map<int, std::map<int,int>> actual,
        expected = { { 1, { { 13, 15 } } }, { 2, { { 9, 10 } } }, { 3, { { 17, 21 } } }, { 4, { { 1, 3 } } } };
    std::stringstream in(" { { 1, { { 13, 15 } } }, { 2, { { 9, 10 } } }, { 3, { { 17, 21 } } }, { 4, { { 1, 3 } } } } ");

    valhalla::utils::loaders::loader::v4::dataLoader<
        std::map<int, std::map<int,int>>,
        char,
        IntegerMapMapReader,
        1,
        valhalla::utils::checkers::is_character<char,'{'>,
        valhalla::utils::checkers::is_character<char,'}'>,
        valhalla::utils::checkers::is_space_or<','>
    > loader(actual);
    in >> loader;

    ASSERT_EQ(actual, expected);
}

struct IntegerAMapPairReader {
    std::istream & operator()(std::istream & in, std::pair<int,std::map<int,A>> & entry, int state) {
        switch (state) {
            case 0:
                {
                    valhalla::utils::loaders::loader::v4::dataLoader<
                        int,
                        char,
                        valhalla::utils::loaders::loader::v4::reader<int,char>,
                        1,
                        valhalla::utils::checkers::is_character_noop<char>,
                        valhalla::utils::checkers::is_no_character<char>
                    > loader(entry.first);
                    in >> loader;
                }
                break;

            case 1:
                {
                    valhalla::utils::loaders::loader::v4::dataLoader<
                        std::map<int,A>,
                        char,
                        IntegerAMapReader,
                        1,
                        valhalla::utils::checkers::is_character<char,'{'>,
                        valhalla::utils::checkers::is_character<char,'}'>,
                        valhalla::utils::checkers::is_space_or<','>
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

        valhalla::utils::loaders::loader::v4::dataLoader<
            std::pair<int, std::map<int,A>>,
            char,
            IntegerAMapPairReader,
            2,
            valhalla::utils::checkers::is_character<char,'{'>,
            valhalla::utils::checkers::is_character<char,'}'>,
            valhalla::utils::checkers::is_space_or<','>
        > loader(entry);
        in >> loader;

        dict[entry.first] = entry.second;

        return in;
    }
};

TEST(DataLoaderTestSuite, IntegerAMapMapDataLoaderV4Test) {
    std::map<int, std::map<int,A>> actual,
        expected = { { 1, { { 13, { 15, 16 } } } }, { 2, { { 9, { 10, 11 } } } } };
    std::stringstream in(" { { 1, { { 13, { 15, 16 } } } }, { 2, { { 9, { 10, 11 } } } } } ");

    valhalla::utils::loaders::loader::v4::dataLoader<
        std::map<int, std::map<int,A>>,
        char,
        IntegerAMapMapReader,
        1,
        valhalla::utils::checkers::is_character<char,'{'>,
        valhalla::utils::checkers::is_character<char,'}'>,
        valhalla::utils::checkers::is_space_or<','>
    > loader(actual);
    in >> loader;

    ASSERT_EQ(actual, expected);
}

/******************************************************************************************
 *
 *  Version 5 Tests Status
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
 *
 ******************************************************************************************/

TEST(DataLoaderTestSuite, IntegerDataLoaderV5Test) {
    int actual, expected = 13;
    std::stringstream in(" 13 ");

    valhalla::utils::loaders::loader::v5::dataLoader<
        int,
        char,
        valhalla::utils::loaders::loader::v5::reader<int,char>,
        1,
        valhalla::utils::checkers::is_character_noop<char>,
        valhalla::utils::checkers::is_no_character<char>,
        valhalla::utils::checkers::is_space_or<','>
    > loader(actual);
    in >> loader;

    ASSERT_EQ(actual, expected);
}

TEST(DataLoaderTestSuite, IntegerDataObjectDataLoaderV5Test) {
    IntegerData actual, expected = { 13 };
    std::stringstream in(" { 13 } ");

    valhalla::utils::loaders::loader::v5::dataLoader<
        IntegerData,
        char,
        valhalla::utils::loaders::loader::v5::reader<IntegerData,char>,
        1,
        valhalla::utils::checkers::is_character<char,'{'>,
        valhalla::utils::checkers::is_character<char,'}'>,
        valhalla::utils::checkers::is_space_or<','>
    > loader(actual);
    in >> loader;

    ASSERT_EQ(actual, expected);
}

TEST(DataLoaderTestSuite, AObjectDataLoaderV5Test) {
    A actual, expected = { 13, 15 };
    std::stringstream in(" { 13, 15 } ");

    valhalla::utils::loaders::loader::v5::dataLoader<
        A,
        char,
        AObjectReader,
        2,
        valhalla::utils::checkers::is_character<char,'{'>,
        valhalla::utils::checkers::is_character<char,'}'>,
        valhalla::utils::checkers::is_space_or<','>
    > loader(actual);
    in >> loader;

    ASSERT_EQ(actual, expected);
}

class CObjectReaderV5 {
    A m_a;
public:
    std::istream & operator()(std::istream & in, C & c, int state) {
        switch(state) {
            case 0:
                {
                    valhalla::utils::loaders::loader::v5::dataLoader<
                        A,
                        char,
                        AObjectReader,
                        2,
                        valhalla::utils::checkers::is_character<char,'{'>,
                        valhalla::utils::checkers::is_character<char,'}'>,
                        valhalla::utils::checkers::is_space_or<','>
                    > loader(m_a);
                    in >> loader;
                }
                break;
            case 1:
                {
                    B b;
                    valhalla::utils::loaders::loader::v5::dataLoader<
                        B,
                        char,
                        BObjectReader,
                        2,
                        valhalla::utils::checkers::is_character<char,'{'>,
                        valhalla::utils::checkers::is_character<char,'}'>,
                        valhalla::utils::checkers::is_space_or<','>
                    > loader(b);
                    in >> loader;
                    c = C(m_a,b);
                }
                break;
        } // switch
        return in;
    }
};

TEST(DataLoaderTestSuite, CObjectDataLoaderV5Test) {
    C actual, expected = { { 13, 15 }, { 17, 21 } };
    std::stringstream in(" { { 13, 15 }, { 17, 21 } } ");

    valhalla::utils::loaders::loader::v5::dataLoader<
        C,
        char,
        CObjectReaderV5,
        2,
        valhalla::utils::checkers::is_character<char,'{'>,
        valhalla::utils::checkers::is_character<char,'}'>,
        valhalla::utils::checkers::is_space_or<','>
    > loader(actual);
    in >> loader;

    ASSERT_EQ(actual, expected);
}

TEST(DataLoaderTestSuite, IntegerVectorDataLoaderV5Test) {
    std::vector<int> actual, expected = { 13, 15, 17, 21 };
    std::stringstream in(" { 13, 15, 17, 21 } ");

    valhalla::utils::loaders::loader::v5::dataLoader<
        std::vector<int>,
        char,
        IntegerVectorReader,
        1,
        valhalla::utils::checkers::is_character<char,'{'>,
        valhalla::utils::checkers::is_character<char,'}'>,
        valhalla::utils::checkers::is_space_or<','>
    > loader(actual);
    in >> loader;

    ASSERT_EQ(actual, expected);
}

struct AVectorReaderV5 {
    std::istream & operator()(std::istream & in, std::vector<A> & vec, int state) {
        A a;
        valhalla::utils::loaders::loader::v5::dataLoader<
            A,
            char,
            AObjectReader,
            2,
            valhalla::utils::checkers::is_character<char,'{'>,
            valhalla::utils::checkers::is_character<char,'}'>,
            valhalla::utils::checkers::is_space_or<','>
        > loader(a);
        in >> loader;
        vec.push_back(a);
        return in;
    }
};

TEST(DataLoaderTestSuite, AVectorDataLoaderV5Test) {
    std::vector<A> actual, expected = { { 13, 15 }, { 17, 21 } };
    std::stringstream in(" { { 13, 15 }, { 17, 21 } } ");

    valhalla::utils::loaders::loader::v5::dataLoader<
        std::vector<A>,
        char,
        AVectorReaderV5,
        1,
        valhalla::utils::checkers::is_character<char,'{'>,
        valhalla::utils::checkers::is_character<char,'}'>,
        valhalla::utils::checkers::is_space_or<','>
    > loader(actual);
    in >> loader;

    ASSERT_EQ(actual, expected);
}

struct IntegerVectorVectorReaderV5 {
    std::istream & operator()(std::istream & in, std::vector<std::vector<int>> & vecvec, int state) {
        std::vector<int> vec;

        valhalla::utils::loaders::loader::v5::dataLoader<
            std::vector<int>,
            char,
            IntegerVectorReader,
            1,
            valhalla::utils::checkers::is_character<char,'{'>,
            valhalla::utils::checkers::is_character<char,'}'>,
            valhalla::utils::checkers::is_space_or<','>
        > loader(vec);
        in >> loader;

        vecvec.push_back(vec);

        return in;
    }
};

TEST(DataLoaderTestSuite, IntegerVectorVectorDataLoaderV5Test) {
    std::vector<std::vector<int>> actual, expected = { { 13, 15 }, { 17, 21 } };
    std::stringstream in(" { { 13, 15 }, { 17, 21 } } ");

    valhalla::utils::loaders::loader::v5::dataLoader<
        std::vector<std::vector<int>>,
        char,
        IntegerVectorVectorReaderV5,
        1,
        valhalla::utils::checkers::is_character<char,'{'>,
        valhalla::utils::checkers::is_character<char,'}'>,
        valhalla::utils::checkers::is_space_or<','>
    > loader(actual);
    in >> loader;

    ASSERT_EQ(actual, expected);
}

struct AVectorVectorReaderV5 {
    std::istream & operator()(std::istream & in, std::vector<std::vector<A>> & vecvec, int state) {
        std::vector<A> vec;

        valhalla::utils::loaders::loader::v5::dataLoader<
            std::vector<A>,
            char,
            AVectorReaderV5,
            1,
            valhalla::utils::checkers::is_character<char,'{'>,
            valhalla::utils::checkers::is_character<char,'}'>,
            valhalla::utils::checkers::is_space_or<','>
        > loader(vec);
        in >> loader;

        vecvec.push_back(vec);

        return in;
    }
};

TEST(DataLoaderTestSuite, AVectorVectorDataLoaderV5Test) {
    std::vector<std::vector<A>> actual, expected = { { { 13, 15 }, { 9, 10 } }, { { 17, 21 }, { 1, 3 } } };
    std::stringstream in(" { { { 13, 15 }, { 9, 10 } }, { { 17, 21 }, { 1, 3 } } } ");

    valhalla::utils::loaders::loader::v5::dataLoader<
        std::vector<std::vector<A>>,
        char,
        AVectorVectorReaderV5,
        1,
        valhalla::utils::checkers::is_character<char,'{'>,
        valhalla::utils::checkers::is_character<char,'}'>,
        valhalla::utils::checkers::is_space_or<','>
    > loader(actual);
    in >> loader;

    ASSERT_EQ(actual, expected);
}

struct IntegerPairReaderV5 {
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

        valhalla::utils::loaders::loader::v5::dataLoader<
            int,
            char,
            valhalla::utils::loaders::loader::v5::reader<int,char>,
            1,
            valhalla::utils::checkers::is_character_noop<char>,
            valhalla::utils::checkers::is_no_character<char>
        > loader(*value);
        in >> loader;

        return in;
    }
};

struct IntegerMapReaderV5 {
    std::istream & operator()(std::istream & in, std::map<int,int> & dict, int state) {
        std::pair<int,int> entry;

        valhalla::utils::loaders::loader::v5::dataLoader<
            std::pair<int,int>,
            char,
            IntegerPairReaderV5,
            2,
            valhalla::utils::checkers::is_character<char,'{'>,
            valhalla::utils::checkers::is_character<char,'}'>,
            valhalla::utils::checkers::is_space_or<','>
        > loader(entry);
        in >> loader;

        dict[entry.first] = entry.second;

        return in;
    }
};

TEST(DataLoaderTestSuite, IntegerIntegerMapDataLoaderV5Test) {
    std::map<int,int> actual, expected = { { 13, 15 }, { 9, 10 }, { 17, 21 }, { 1, 3 } };
    std::stringstream in(" { { 13, 15 }, { 9, 10 }, { 17, 21 }, { 1, 3 } } ");

    valhalla::utils::loaders::loader::v5::dataLoader<
        std::map<int,int>,
        char,
        IntegerMapReaderV5,
        1,
        valhalla::utils::checkers::is_character<char,'{'>,
        valhalla::utils::checkers::is_character<char,'}'>,
        valhalla::utils::checkers::is_space_or<','>
    > loader(actual);
    in >> loader;

    ASSERT_EQ(actual, expected);
}

struct IntegerAPairReaderV5 {
    std::istream & operator()(std::istream & in, std::pair<int,A> & entry, int state) {
        switch(state) {
            case 0:
                {
                    valhalla::utils::loaders::loader::v5::dataLoader<
                        int,
                        char,
                        valhalla::utils::loaders::loader::v5::reader<int,char>,
                        1,
                        valhalla::utils::checkers::is_character_noop<char>,
                        valhalla::utils::checkers::is_no_character<char>
                    > loader(entry.first);
                    in >> loader;
                }
                break;
            case 1:
                {
                    valhalla::utils::loaders::loader::v5::dataLoader<
                        A,
                        char,
                        AObjectReader,
                        2,
                        valhalla::utils::checkers::is_character<char,'{'>,
                        valhalla::utils::checkers::is_character<char,'}'>,
                        valhalla::utils::checkers::is_space_or<','>
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

struct IntegerAMapReaderV5 {
    std::istream & operator()(std::istream & in, std::map<int,A> & dict, int state) {
        std::pair<int,A> entry;

        valhalla::utils::loaders::loader::v5::dataLoader<
            std::pair<int,A>,
            char,
            IntegerAPairReaderV5,
            2,
            valhalla::utils::checkers::is_character<char,'{'>,
            valhalla::utils::checkers::is_character<char,'}'>,
            valhalla::utils::checkers::is_space_or<','>
        > loader(entry);
        in >> loader;

        dict[entry.first] = entry.second;

        return in;
    }
};

TEST(DataLoaderTestSuite, IntegerAMapDataLoaderV5Test) {
    std::map<int,A> actual, expected = { { 13, { 15, 16 } }, { 9, { 10, 11 } }, { 17, { 21, 22 } }, { 1, { 3, 4 } } };
    std::stringstream in(" { { 13, { 15, 16 } }, { 9, { 10, 11 } }, { 17, { 21, 22 } }, { 1, { 3, 4 } } } ");

    valhalla::utils::loaders::loader::v5::dataLoader<
        std::map<int,A>,
        char,
        IntegerAMapReaderV5,
        1,
        valhalla::utils::checkers::is_character<char,'{'>,
        valhalla::utils::checkers::is_character<char,'}'>,
        valhalla::utils::checkers::is_space_or<','>
    > loader(actual);
    in >> loader;

    ASSERT_EQ(actual, expected);
}

struct IntegerMapPairReaderV5 {
    std::istream & operator()(std::istream & in, std::pair<int,std::map<int,int>> & entry, int state) {
        switch (state) {
            case 0:
                {
                    valhalla::utils::loaders::loader::v5::dataLoader<
                        int,
                        char,
                        valhalla::utils::loaders::loader::v5::reader<int,char>,
                        1,
                        valhalla::utils::checkers::is_character_noop<char>,
                        valhalla::utils::checkers::is_no_character<char>
                    > loader(entry.first);
                    in >> loader;
                }
                break;

            case 1:
                {
                    valhalla::utils::loaders::loader::v5::dataLoader<
                        std::map<int,int>,
                        char,
                        IntegerMapReaderV5,
                        1,
                        valhalla::utils::checkers::is_character<char,'{'>,
                        valhalla::utils::checkers::is_character<char,'}'>,
                        valhalla::utils::checkers::is_space_or<','>
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

struct IntegerMapMapReaderV5 {
    std::istream & operator()(std::istream & in, std::map<int,std::map<int,int>> & dict, int state) {
        std::pair<int,std::map<int,int>> entry;

        valhalla::utils::loaders::loader::v5::dataLoader<
            std::pair<int, std::map<int,int>>,
            char,
            IntegerMapPairReaderV5,
            2,
            valhalla::utils::checkers::is_character<char,'{'>,
            valhalla::utils::checkers::is_character<char,'}'>,
            valhalla::utils::checkers::is_space_or<','>
        > loader(entry);
        in >> loader;

        dict[entry.first] = entry.second;

        return in;
    }
};

TEST(DataLoaderTestSuite, IntegerIntegerMapMapDataLoaderV5Test) {
    std::map<int, std::map<int,int>> actual,
        expected = { { 1, { { 13, 15 } } }, { 2, { { 9, 10 } } }, { 3, { { 17, 21 } } }, { 4, { { 1, 3 } } } };
    std::stringstream in(" { { 1, { { 13, 15 } } }, { 2, { { 9, 10 } } }, { 3, { { 17, 21 } } }, { 4, { { 1, 3 } } } } ");

    valhalla::utils::loaders::loader::v5::dataLoader<
        std::map<int, std::map<int,int>>,
        char,
        IntegerMapMapReaderV5,
        1,
        valhalla::utils::checkers::is_character<char,'{'>,
        valhalla::utils::checkers::is_character<char,'}'>,
        valhalla::utils::checkers::is_space_or<','>
    > loader(actual);
    in >> loader;

    ASSERT_EQ(actual, expected);
}

struct IntegerAMapPairReaderV5 {
    std::istream & operator()(std::istream & in, std::pair<int,std::map<int,A>> & entry, int state) {
        switch (state) {
            case 0:
                {
                    valhalla::utils::loaders::loader::v5::dataLoader<
                        int,
                        char,
                        valhalla::utils::loaders::loader::v5::reader<int,char>,
                        1,
                        valhalla::utils::checkers::is_character_noop<char>,
                        valhalla::utils::checkers::is_no_character<char>
                    > loader(entry.first);
                    in >> loader;
                }
                break;

            case 1:
                {
                    valhalla::utils::loaders::loader::v5::dataLoader<
                        std::map<int,A>,
                        char,
                        IntegerAMapReaderV5,
                        1,
                        valhalla::utils::checkers::is_character<char,'{'>,
                        valhalla::utils::checkers::is_character<char,'}'>,
                        valhalla::utils::checkers::is_space_or<','>
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

struct IntegerAMapMapReaderV5 {
    std::istream & operator()(std::istream & in, std::map<int, std::map<int,A>> & dict, int state) {
        std::pair<int,std::map<int,A>> entry;

        valhalla::utils::loaders::loader::v5::dataLoader<
            std::pair<int, std::map<int,A>>,
            char,
            IntegerAMapPairReaderV5,
            2,
            valhalla::utils::checkers::is_character<char,'{'>,
            valhalla::utils::checkers::is_character<char,'}'>,
            valhalla::utils::checkers::is_space_or<','>
        > loader(entry);
        in >> loader;

        dict[entry.first] = entry.second;

        return in;
    }
};

TEST(DataLoaderTestSuite, IntegerAMapMapDataLoaderV5Test) {
    std::map<int, std::map<int,A>> actual,
        expected = { { 1, { { 13, { 15, 16 } } } }, { 2, { { 9, { 10, 11 } } } } };
    std::stringstream in(" { { 1, { { 13, { 15, 16 } } } }, { 2, { { 9, { 10, 11 } } } } } ");

    valhalla::utils::loaders::loader::v5::dataLoader<
        std::map<int, std::map<int,A>>,
        char,
        IntegerAMapMapReaderV5,
        1,
        valhalla::utils::checkers::is_character<char,'{'>,
        valhalla::utils::checkers::is_character<char,'}'>,
        valhalla::utils::checkers::is_space_or<','>
    > loader(actual);
    in >> loader;

    ASSERT_EQ(actual, expected);
}

struct StringReaderV5 {
    std::basic_istream<char> & operator()(std::basic_istream<char> & in, std::string & str, int state) {

        if (static_cast<char>(in.peek()) != '"') {
            str += static_cast<char>(in.get());
        }

        return in;
    }
};

TEST(DataLoaderTestSuite, SimpleStringDataLoaderV5Test) {
    std::string actual,
        expected = "simple";
    std::stringstream in(" \"simple\" ");

    valhalla::utils::loaders::loader::v5::dataLoader<
        std::string,
        char,
        StringReaderV5,
        1,
        valhalla::utils::checkers::is_character<char,'"'>,
        valhalla::utils::checkers::is_character<char,'"'>,
        valhalla::utils::checkers::is_space_or<','>,
        valhalla::utils::checkers::is_space_noop<char>
    > loader(actual);
    in >> loader;

    ASSERT_EQ(actual, expected);
}

TEST(DataLoaderTestSuite, ComplexStringDataLoaderV5Test) {
    std::string actual,
        expected = "This is a string with spaces in-between open and close characters";
    std::stringstream in(" \"This is a string with spaces in-between open and close characters\" ");

    valhalla::utils::loaders::loader::v5::dataLoader<
        std::string,
        char,
        StringReaderV5,
        1,
        valhalla::utils::checkers::is_character<char,'"'>,
        valhalla::utils::checkers::is_character<char,'"'>,
        valhalla::utils::checkers::is_space_or<','>,
        valhalla::utils::checkers::is_space_noop<char>
    > loader(actual);
    in >> loader;

    ASSERT_EQ(actual, expected);
}

struct TupleStringReaderV5 {
    std::basic_istream<char> & operator()(std::basic_istream<char> & in, std::tuple<std::string> & tup, int state) {
        std::string entry;

        ::loaders::loader::v5::dataLoader<
            std::string,
            char,
            StringReaderV5,
            1,
            ::checkers::is_character<char,'"'>,
            ::checkers::is_character<char,'"'>,
            ::checkers::is_space_or<','>,
            ::checkers::is_space_noop<int>
        > entryLoader(entry);
        in >> entryLoader;

        tup = std::tuple<std::string>(entry);

        return in;
    }
};

TEST(DataLoaderTestSuite, SimpleTupleDataLoaderV5Test) {
    std::tuple<std::string> actual,
        expected = std::tuple<std::string>("This is a string with spaces in-between open and close characters");
    std::stringstream in(" ( \"This is a string with spaces in-between open and close characters\" ) ");

    valhalla::utils::loaders::loader::v5::dataLoader<
        std::tuple<std::string>,
        char,
        TupleStringReaderV5,
        1,
        valhalla::utils::checkers::is_character<char,'('>,
        valhalla::utils::checkers::is_character<char,')'>,
        valhalla::utils::checkers::is_space_or<','>
    > loader(actual);
    in >> loader;

    ASSERT_EQ(actual, expected);
}

struct ComplexTupleReaderV5 {
    std::basic_istream<char> & operator()(std::basic_istream<char> & in, std::tuple<std::string,int,long> & tup, int state) {
        std::string eone;

        ::loaders::loader::v5::dataLoader<
            std::string,
            char,
            StringReaderV5,
            1,
            ::checkers::is_character<char,'"'>,
            ::checkers::is_character<char,'"'>,
            ::checkers::is_space_or<','>,
            ::checkers::is_space_noop<int>
        > entryLoader(eone);
        in >> entryLoader;

        int etwo;

        ::loaders::loader::v5::dataLoader<
            int,
            char,
            loaders::loader::v5::reader<int,char>,
            1,
            ::checkers::is_character_noop<char>,
            ::checkers::is_no_character<char>,
            ::checkers::is_space_or<','>
        > etwoLoader(etwo);
        in >> etwoLoader;

        long ethree;

        ::loaders::loader::v5::dataLoader<
            long,
            char,
            loaders::loader::v5::reader<long,char>,
            1,
            ::checkers::is_character_noop<char>,
            ::checkers::is_no_character<char>,
            ::checkers::is_space_or<','>
        > ethreeLoader(ethree);
        in >> ethreeLoader;

        tup = {eone, etwo, ethree};

        return in;
    }
};

TEST(DataLoaderTestSuite, ComplexTupleDataLoaderV5Test) {
    std::tuple<std::string,int,long> actual,
        expected = {"This is a string with spaces in-between open and close characters", 101, 1003 };
    std::stringstream in(" ( \"This is a string with spaces in-between open and close characters\", 101, 1003 ) ");

    valhalla::utils::loaders::loader::v5::dataLoader<
        std::tuple<std::string,int,long>,
        char,
        ComplexTupleReaderV5,
        1,
        valhalla::utils::checkers::is_character<char,'('>,
        valhalla::utils::checkers::is_character<char,')'>,
        valhalla::utils::checkers::is_space_or<','>
    > loader(actual);
    in >> loader;

    ASSERT_EQ(actual, expected);
}

/******************************************************************************************
 *
 *  Version 6 Tests Status
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

TEST(DataLoaderTestSuite, IntegerDataLoaderV6Test) {
    int actual, expected = 13;
    std::stringstream in(" 13 ");

    valhalla::utils::loaders::loader::v6::dataLoader<
        int,
        char
    > loader(actual);
    in >> loader;

    ASSERT_EQ(actual, expected);
}

TEST(DataLoaderTestSuite, IntegerDataObjectDataLoaderV6Test) {
    IntegerData actual, expected = { 13 };
    std::stringstream in(" { 13 } ");

    valhalla::utils::loaders::loader::v6::dataLoader<
        IntegerData,
        char,
        valhalla::utils::loaders::loader::v6::reader<IntegerData,char>,
        1,
        valhalla::utils::checkers::is_character<char,'{'>,
        valhalla::utils::checkers::is_character<char,'}'>,
        valhalla::utils::checkers::is_space_or<','>
    > loader(actual);
    in >> loader;

    ASSERT_EQ(actual, expected);
}

TEST(DataLoaderTestSuite, AObjectDataLoaderV6Test) {
    A actual, expected = { 13, 15 };
    std::stringstream in(" { 13, 15 } ");

    valhalla::utils::loaders::loader::v6::dataLoader<
        A,
        char,
        AObjectReader,
        2,
        valhalla::utils::checkers::is_character<char,'{'>,
        valhalla::utils::checkers::is_character<char,'}'>,
        valhalla::utils::checkers::is_space_or<','>
    > loader(actual);
    in >> loader;

    ASSERT_EQ(actual, expected);
}

class CObjectReaderV6 {
    A m_a;
public:
    std::istream & operator()(std::istream & in, C & c, int state) {
        switch(state) {
            case 0:
                {
                    valhalla::utils::loaders::loader::v6::dataLoader<
                        A,
                        char,
                        AObjectReader,
                        2,
                        valhalla::utils::checkers::is_character<char,'{'>,
                        valhalla::utils::checkers::is_character<char,'}'>,
                        valhalla::utils::checkers::is_space_or<','>
                    > loader(m_a);
                    in >> loader;
                }
                break;
            case 1:
                {
                    B b;
                    valhalla::utils::loaders::loader::v6::dataLoader<
                        B,
                        char,
                        BObjectReader,
                        2,
                        valhalla::utils::checkers::is_character<char,'{'>,
                        valhalla::utils::checkers::is_character<char,'}'>,
                        valhalla::utils::checkers::is_space_or<','>
                    > loader(b);
                    in >> loader;
                    c = C(m_a,b);
                }
                break;
        } // switch
        return in;
    }
};

TEST(DataLoaderTestSuite, CObjectDataLoaderV6Test) {
    C actual, expected = { { 13, 15 }, { 17, 21 } };
    std::stringstream in(" { { 13, 15 }, { 17, 21 } } ");

    valhalla::utils::loaders::loader::v6::dataLoader<
        C,
        char,
        CObjectReaderV6,
        2,
        valhalla::utils::checkers::is_character<char,'{'>,
        valhalla::utils::checkers::is_character<char,'}'>,
        valhalla::utils::checkers::is_space_or<','>
    > loader(actual);
    in >> loader;

    ASSERT_EQ(actual, expected);
}

TEST(DataLoaderTestSuite, IntegerVectorDataLoaderV6Test) {
    std::vector<int> actual, expected = { 13, 15, 17, 21 };
    std::stringstream in(" { 13, 15, 17, 21 } ");

    valhalla::utils::loaders::loader::v6::dataLoader<
        std::vector<int>,
        char,
        IntegerVectorReader,
        1,
        valhalla::utils::checkers::is_character<char,'{'>,
        valhalla::utils::checkers::is_character<char,'}'>,
        valhalla::utils::checkers::is_space_or<','>
    > loader(actual);
    in >> loader;

    ASSERT_EQ(actual, expected);
}

struct AVectorReaderV6 {
    std::istream & operator()(std::istream & in, std::vector<A> & vec, int state) {
        A a;
        valhalla::utils::loaders::loader::v6::dataLoader<
            A,
            char,
            AObjectReader,
            2,
            valhalla::utils::checkers::is_character<char,'{'>,
            valhalla::utils::checkers::is_character<char,'}'>,
            valhalla::utils::checkers::is_space_or<','>
        > loader(a);
        in >> loader;
        vec.push_back(a);
        return in;
    }
};

TEST(DataLoaderTestSuite, AVectorDataLoaderV6Test) {
    std::vector<A> actual, expected = { { 13, 15 }, { 17, 21 } };
    std::stringstream in(" { { 13, 15 }, { 17, 21 } } ");

    valhalla::utils::loaders::loader::v6::dataLoader<
        std::vector<A>,
        char,
        AVectorReaderV6,
        1,
        valhalla::utils::checkers::is_character<char,'{'>,
        valhalla::utils::checkers::is_character<char,'}'>,
        valhalla::utils::checkers::is_space_or<','>
    > loader(actual);
    in >> loader;

    ASSERT_EQ(actual, expected);
}

struct IntegerVectorVectorReaderV6 {
    std::istream & operator()(std::istream & in, std::vector<std::vector<int>> & vecvec, int state) {
        std::vector<int> vec;

        valhalla::utils::loaders::loader::v6::dataLoader<
            std::vector<int>,
            char,
            IntegerVectorReader,
            1,
            valhalla::utils::checkers::is_character<char,'{'>,
            valhalla::utils::checkers::is_character<char,'}'>,
            valhalla::utils::checkers::is_space_or<','>
        > loader(vec);
        in >> loader;

        vecvec.push_back(vec);

        return in;
    }
};

TEST(DataLoaderTestSuite, IntegerVectorVectorDataLoaderV6Test) {
    std::vector<std::vector<int>> actual, expected = { { 13, 15 }, { 17, 21 } };
    std::stringstream in(" { { 13, 15 }, { 17, 21 } } ");

    valhalla::utils::loaders::loader::v6::dataLoader<
        std::vector<std::vector<int>>,
        char,
        IntegerVectorVectorReaderV6,
        1,
        valhalla::utils::checkers::is_character<char,'{'>,
        valhalla::utils::checkers::is_character<char,'}'>,
        valhalla::utils::checkers::is_space_or<','>
    > loader(actual);
    in >> loader;

    ASSERT_EQ(actual, expected);
}

struct AVectorVectorReaderV6 {
    std::istream & operator()(std::istream & in, std::vector<std::vector<A>> & vecvec, int state) {
        std::vector<A> vec;

        valhalla::utils::loaders::loader::v6::dataLoader<
            std::vector<A>,
            char,
            AVectorReaderV6,
            1,
            valhalla::utils::checkers::is_character<char,'{'>,
            valhalla::utils::checkers::is_character<char,'}'>,
            valhalla::utils::checkers::is_space_or<','>
        > loader(vec);
        in >> loader;

        vecvec.push_back(vec);

        return in;
    }
};

TEST(DataLoaderTestSuite, AVectorVectorDataLoaderV6Test) {
    std::vector<std::vector<A>> actual, expected = { { { 13, 15 }, { 9, 10 } }, { { 17, 21 }, { 1, 3 } } };
    std::stringstream in(" { { { 13, 15 }, { 9, 10 } }, { { 17, 21 }, { 1, 3 } } } ");

    valhalla::utils::loaders::loader::v6::dataLoader<
        std::vector<std::vector<A>>,
        char,
        AVectorVectorReaderV6,
        1,
        valhalla::utils::checkers::is_character<char,'{'>,
        valhalla::utils::checkers::is_character<char,'}'>,
        valhalla::utils::checkers::is_space_or<','>
    > loader(actual);
    in >> loader;

    ASSERT_EQ(actual, expected);
}

struct IntegerPairReaderV6 {
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

        valhalla::utils::loaders::loader::v6::dataLoader<
            int,
            char,
            valhalla::utils::loaders::loader::v6::reader<int,char>,
            1,
            valhalla::utils::checkers::is_character_noop<char>,
            valhalla::utils::checkers::is_no_character<char>
        > loader(*value);
        in >> loader;

        return in;
    }
};

struct IntegerMapReaderV6 {
    std::istream & operator()(std::istream & in, std::map<int,int> & dict, int state) {
        std::pair<int,int> entry;

        valhalla::utils::loaders::loader::v6::dataLoader<
            std::pair<int,int>,
            char,
            IntegerPairReaderV6,
            2,
            valhalla::utils::checkers::is_character<char,'{'>,
            valhalla::utils::checkers::is_character<char,'}'>,
            valhalla::utils::checkers::is_space_or<','>
        > loader(entry);
        in >> loader;

        dict[entry.first] = entry.second;

        return in;
    }
};

TEST(DataLoaderTestSuite, IntegerIntegerMapDataLoaderV6Test) {
    std::map<int,int> actual, expected = { { 13, 15 }, { 9, 10 }, { 17, 21 }, { 1, 3 } };
    std::stringstream in(" { { 13, 15 }, { 9, 10 }, { 17, 21 }, { 1, 3 } } ");

    valhalla::utils::loaders::loader::v6::dataLoader<
        std::map<int,int>,
        char,
        IntegerMapReaderV6,
        1,
        valhalla::utils::checkers::is_character<char,'{'>,
        valhalla::utils::checkers::is_character<char,'}'>,
        valhalla::utils::checkers::is_space_or<','>
    > loader(actual);
    in >> loader;

    ASSERT_EQ(actual, expected);
}

struct IntegerAPairReaderV6 {
    std::istream & operator()(std::istream & in, std::pair<int,A> & entry, int state) {
        switch(state) {
            case 0:
                {
                    valhalla::utils::loaders::loader::v6::dataLoader<
                        int,
                        char,
                        valhalla::utils::loaders::loader::v6::reader<int,char>,
                        1,
                        valhalla::utils::checkers::is_character_noop<char>,
                        valhalla::utils::checkers::is_no_character<char>
                    > loader(entry.first);
                    in >> loader;
                }
                break;
            case 1:
                {
                    valhalla::utils::loaders::loader::v6::dataLoader<
                        A,
                        char,
                        AObjectReader,
                        2,
                        valhalla::utils::checkers::is_character<char,'{'>,
                        valhalla::utils::checkers::is_character<char,'}'>,
                        valhalla::utils::checkers::is_space_or<','>
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

struct IntegerAMapReaderV6 {
    std::istream & operator()(std::istream & in, std::map<int,A> & dict, int state) {
        std::pair<int,A> entry;

        valhalla::utils::loaders::loader::v6::dataLoader<
            std::pair<int,A>,
            char,
            IntegerAPairReaderV6,
            2,
            valhalla::utils::checkers::is_character<char,'{'>,
            valhalla::utils::checkers::is_character<char,'}'>,
            valhalla::utils::checkers::is_space_or<','>
        > loader(entry);
        in >> loader;

        dict[entry.first] = entry.second;

        return in;
    }
};

TEST(DataLoaderTestSuite, IntegerAMapDataLoaderV6Test) {
    std::map<int,A> actual, expected = { { 13, { 15, 16 } }, { 9, { 10, 11 } }, { 17, { 21, 22 } }, { 1, { 3, 4 } } };
    std::stringstream in(" { { 13, { 15, 16 } }, { 9, { 10, 11 } }, { 17, { 21, 22 } }, { 1, { 3, 4 } } } ");

    valhalla::utils::loaders::loader::v6::dataLoader<
        std::map<int,A>,
        char,
        IntegerAMapReaderV6,
        1,
        valhalla::utils::checkers::is_character<char,'{'>,
        valhalla::utils::checkers::is_character<char,'}'>,
        valhalla::utils::checkers::is_space_or<','>
    > loader(actual);
    in >> loader;

    ASSERT_EQ(actual, expected);
}

struct IntegerMapPairReaderV6 {
    std::istream & operator()(std::istream & in, std::pair<int,std::map<int,int>> & entry, int state) {
        switch (state) {
            case 0:
                {
                    valhalla::utils::loaders::loader::v6::dataLoader<
                        int,
                        char
                    > loader(entry.first);
                    in >> loader;
                }
                break;

            case 1:
                {
                    valhalla::utils::loaders::loader::v6::dataLoader<
                        std::map<int,int>,
                        char,
                        IntegerMapReaderV6,
                        1,
                        valhalla::utils::checkers::is_character<char,'{'>,
                        valhalla::utils::checkers::is_character<char,'}'>,
                        valhalla::utils::checkers::is_space_or<','>
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

struct IntegerMapMapReaderV6 {
    std::istream & operator()(std::istream & in, std::map<int,std::map<int,int>> & dict, int state) {
        std::pair<int,std::map<int,int>> entry;

        valhalla::utils::loaders::loader::v6::dataLoader<
            std::pair<int, std::map<int,int>>,
            char,
            IntegerMapPairReaderV6,
            2,
            valhalla::utils::checkers::is_character<char,'{'>,
            valhalla::utils::checkers::is_character<char,'}'>,
            valhalla::utils::checkers::is_space_or<','>
        > loader(entry);
        in >> loader;

        dict[entry.first] = entry.second;

        return in;
    }
};

TEST(DataLoaderTestSuite, IntegerIntegerMapMapDataLoaderV6Test) {
    std::map<int, std::map<int,int>> actual,
        expected = { { 1, { { 13, 15 } } }, { 2, { { 9, 10 } } }, { 3, { { 17, 21 } } }, { 4, { { 1, 3 } } } };
    std::stringstream in(" { { 1, { { 13, 15 } } }, { 2, { { 9, 10 } } }, { 3, { { 17, 21 } } }, { 4, { { 1, 3 } } } } ");

    valhalla::utils::loaders::loader::v6::dataLoader<
        std::map<int, std::map<int,int>>,
        char,
        IntegerMapMapReaderV6,
        1,
        valhalla::utils::checkers::is_character<char,'{'>,
        valhalla::utils::checkers::is_character<char,'}'>,
        valhalla::utils::checkers::is_space_or<','>
    > loader(actual);
    in >> loader;

    ASSERT_EQ(actual, expected);
}

struct IntegerAMapPairReaderV6 {
    std::istream & operator()(std::istream & in, std::pair<int,std::map<int,A>> & entry, int state) {
        switch (state) {
            case 0:
                {
                    valhalla::utils::loaders::loader::v6::dataLoader<
                        int,
                        char
                    > loader(entry.first);
                    in >> loader;
                }
                break;

            case 1:
                {
                    valhalla::utils::loaders::loader::v6::dataLoader<
                        std::map<int,A>,
                        char,
                        IntegerAMapReaderV6,
                        1,
                        valhalla::utils::checkers::is_character<char,'{'>,
                        valhalla::utils::checkers::is_character<char,'}'>,
                        valhalla::utils::checkers::is_space_or<','>
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

struct IntegerAMapMapReaderV6 {
    std::istream & operator()(std::istream & in, std::map<int, std::map<int,A>> & dict, int state) {
        std::pair<int,std::map<int,A>> entry;

        valhalla::utils::loaders::loader::v6::dataLoader<
            std::pair<int, std::map<int,A>>,
            char,
            IntegerAMapPairReaderV6,
            2,
            valhalla::utils::checkers::is_character<char,'{'>,
            valhalla::utils::checkers::is_character<char,'}'>,
            valhalla::utils::checkers::is_space_or<','>
        > loader(entry);
        in >> loader;

        dict[entry.first] = entry.second;

        return in;
    }
};

TEST(DataLoaderTestSuite, IntegerAMapMapDataLoaderV6Test) {
    std::map<int, std::map<int,A>> actual,
        expected = { { 1, { { 13, { 15, 16 } } } }, { 2, { { 9, { 10, 11 } } } } };
    std::stringstream in(" { { 1, { { 13, { 15, 16 } } } }, { 2, { { 9, { 10, 11 } } } } } ");

    valhalla::utils::loaders::loader::v6::dataLoader<
        std::map<int, std::map<int,A>>,
        char,
        IntegerAMapMapReaderV6,
        1,
        valhalla::utils::checkers::is_character<char,'{'>,
        valhalla::utils::checkers::is_character<char,'}'>,
        valhalla::utils::checkers::is_space_or<','>
    > loader(actual);
    in >> loader;

    ASSERT_EQ(actual, expected);
}

struct StringReaderV6 {
    std::basic_istream<char> & operator()(std::basic_istream<char> & in, std::string & str, int state) {

        while (static_cast<char>(in.peek()) != '"') {
            str += static_cast<char>(in.get());
        }

        return in;
    }
};

TEST(DataLoaderTestSuite, SimpleStringDataLoaderV6Test) {
    std::string actual,
        expected = "simple";
    std::stringstream in(" \"simple\" ");

    valhalla::utils::loaders::loader::v6::dataLoader<
        std::string,
        char,
        StringReaderV6,
        1,
        valhalla::utils::checkers::is_character<char,'"'>,
        valhalla::utils::checkers::is_character<char,'"'>,
        valhalla::utils::checkers::is_space_or<','>,
        valhalla::utils::checkers::is_space_noop<char>
    > loader(actual);
    in >> loader;

    ASSERT_EQ(actual, expected);
}

TEST(DataLoaderTestSuite, ComplexStringDataLoaderV6Test) {
    std::string actual,
        expected = "This is a string with spaces in-between open and close characters";
    std::stringstream in(" \"This is a string with spaces in-between open and close characters\" ");

    valhalla::utils::loaders::loader::v6::dataLoader<
        std::string,
        char,
        StringReaderV6,
        1,
        valhalla::utils::checkers::is_character<char,'"'>,
        valhalla::utils::checkers::is_character<char,'"'>,
        valhalla::utils::checkers::is_space_or<','>,
        valhalla::utils::checkers::is_space_noop<char>
    > loader(actual);
    in >> loader;

    ASSERT_EQ(actual, expected);
}

struct TupleStringReaderV6 {
    std::basic_istream<char> & operator()(std::basic_istream<char> & in, std::tuple<std::string> & tup, int state) {
        std::string entry;

        ::loaders::loader::v6::dataLoader<
            std::string,
            char,
            StringReaderV6,
            1,
            ::checkers::is_character<char,'"'>,
            ::checkers::is_character<char,'"'>,
            ::checkers::is_space_or<','>,
            ::checkers::is_space_noop<int>
        > entryLoader(entry);
        in >> entryLoader;

        tup = std::tuple<std::string>(entry);

        return in;
    }
};

TEST(DataLoaderTestSuite, SimpleTupleDataLoaderV6Test) {
    std::tuple<std::string> actual,
        expected = std::tuple<std::string>("This is a string with spaces in-between open and close characters");
    std::stringstream in(" ( \"This is a string with spaces in-between open and close characters\" ) ");

    valhalla::utils::loaders::loader::v6::dataLoader<
        std::tuple<std::string>,
        char,
        TupleStringReaderV6,
        1,
        valhalla::utils::checkers::is_character<char,'('>,
        valhalla::utils::checkers::is_character<char,')'>,
        valhalla::utils::checkers::is_space_or<','>
    > loader(actual);
    in >> loader;

    ASSERT_EQ(actual, expected);
}

struct ComplexTupleReaderV6 {
    std::basic_istream<char> & operator()(std::basic_istream<char> & in, std::tuple<std::string,int,long> & tup, int state) {
        std::string eone;

        ::loaders::loader::v6::dataLoader<
            std::string,
            char,
            StringReaderV6,
            1,
            ::checkers::is_character<char,'"'>,
            ::checkers::is_character<char,'"'>,
            ::checkers::is_space_or<','>,
            ::checkers::is_space_noop<int>
        > entryLoader(eone);
        in >> entryLoader;

        int etwo;

        ::loaders::loader::v6::dataLoader<
            int,
            char
        > etwoLoader(etwo);
        in >> etwoLoader;

        long ethree;

        ::loaders::loader::v6::dataLoader<
            long,
            char,
            loaders::loader::v6::reader<long,char>,
            1,
            ::checkers::is_character_noop<char>,
            ::checkers::is_no_character<char>,
            ::checkers::is_space_or<','>
        > ethreeLoader(ethree);
        in >> ethreeLoader;

        tup = {eone, etwo, ethree};

        return in;
    }
};

TEST(DataLoaderTestSuite, ComplexTupleDataLoaderV6Test) {
    std::tuple<std::string,int,long> actual,
        expected = {"This is a string with spaces in-between open and close characters", 101, 1003 };
    std::stringstream in(" ( \"This is a string with spaces in-between open and close characters\", 101, 1003 ) ");

    valhalla::utils::loaders::loader::v6::dataLoader<
        std::tuple<std::string,int,long>,
        char,
        ComplexTupleReaderV6,
        1,
        valhalla::utils::checkers::is_character<char,'('>,
        valhalla::utils::checkers::is_character<char,')'>,
        valhalla::utils::checkers::is_space_or<','>
    > loader(actual);
    in >> loader;

    ASSERT_EQ(actual, expected);
}

TEST(DataLoaderTestSuite, StringWithLeadingSpacesV6Test) {
    std::string actual, expected = "  string contains preceeding spaces.";
    std::stringstream in(" \"  string contains preceeding spaces.\"  ");

    ::loaders::loader::v6::dataLoader<
        std::string,
        char,
        StringReaderV6,
        1,
        ::checkers::is_character<char,'"'>,
        ::checkers::is_character<char,'"'>
    > loader(actual);
    in >> loader;

    ASSERT_EQ(actual, expected);
}

TEST(DataLoaderTestSuite, StringWithTrailingSpacesV6Test) {
    std::string actual, expected = "string contains preceeding spaces.   ";
    std::stringstream in(" \"string contains preceeding spaces.   \"  ");

    ::loaders::loader::v6::dataLoader<
        std::string,
        char,
        StringReaderV6,
        1,
        ::checkers::is_character<char,'"'>,
        ::checkers::is_character<char,'"'>
    > loader(actual);
    in >> loader;

    ASSERT_EQ(actual, expected);
}

TEST(DataLoaderTestSuite, StringWithLeadingAndTrailingSpacesV6Test) {
    std::string actual, expected = "  string contains preceeding spaces.    ";
    std::stringstream in(" \"  string contains preceeding spaces.    \"  ");

    ::loaders::loader::v6::dataLoader<
        std::string,
        char,
        StringReaderV6,
        1,
        ::checkers::is_character<char,'"'>,
        ::checkers::is_character<char,'"'>
    > loader(actual);
    in >> loader;

    ASSERT_EQ(actual, expected);
}

struct StringWithEscapeCharacterReaderV6 {
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

TEST(DataLoaderTestSuite, StringWithEscapeCharactersV6Test) {
    std::string actual, expected = "  string contains \"preceeding\" spaces.    ";
    std::stringstream in(" \"  string contains \\\"preceeding\\\" spaces.    \"  ");

    ::loaders::loader::v6::dataLoader<
        std::string,
        char,
        StringWithEscapeCharacterReaderV6,
        1,
        ::checkers::is_character<char,'"'>,
        ::checkers::is_character<char,'"'>
    > loader(actual);
    in >> loader;

    ASSERT_EQ(actual, expected);
}

struct StringWithDynamicEscapeCharacterReaderV6 {
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

TEST(DataLoaderTestSuite, StringWithDynamicEscapeCharactersV6Test) {
    std::string actual, expected = "  string contains \"preceeding\" spaces.    ";
    std::stringstream in(" \"  string contains \\\"preceeding\\\" spaces.    \"  ");

    ::loaders::loader::v6::dataLoader<
        std::string,
        char,
        StringWithDynamicEscapeCharacterReaderV6,
        1,
        ::checkers::is_character_noop<char>,
        ::checkers::is_no_character<char>
    > loader(actual);
    in >> loader;

    ASSERT_EQ(actual, expected);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
