/**
 * @file tupleloadertests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains tests for the tupleLoader template implementation
 * @version 0.1
 * @date 2023-06-04
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include <tuple>
#include <sstream>

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "tuple_loader.h"
#include "primitive_loader.h"

using namespace valhalla::utils;

class SingleDataLoader {
    std::tuple<int> & m_tuple;
public:
    SingleDataLoader() = default;
    SingleDataLoader(std::tuple<int> & tuple) : m_tuple(tuple) {}

    friend std::istream & operator>>(std::istream & in, SingleDataLoader & loader) {
        int value;

        ::loaders::primitive::primitiveLoader<
          int,
          char,
          ::checkers::is_space_or<','>
        > valueLoader(&value);
        in >> valueLoader;

        loader.m_tuple = std::tuple<int>(value);

        return in;
    }
};

TEST(TupleTestSuite, SingleTypeTupleTest) {
    std::tuple<int> actual, expected = std::make_tuple<int>(5);
    std::stringstream in("( 5 )");

    valhalla::utils::loaders::tuple::tupleLoader<
        std::tuple<int>,
        SingleDataLoader
    > loader(actual);
    in >> loader;

    ASSERT_EQ(actual, expected);
}

class DoubleDataLoader {
    std::tuple<int,int> & m_tuple;
public:
    DoubleDataLoader() = default;
    DoubleDataLoader(std::tuple<int,int> & tuple) : m_tuple(tuple) {}

    friend std::istream & operator>>(std::istream & in, DoubleDataLoader & loader) {
        int x, y;

        ::loaders::primitive::primitiveLoader<
          int,
          char,
          ::checkers::is_space_or<','>
        > xLoader(&x);
        in >> xLoader;

        ::loaders::primitive::primitiveLoader<
          int,
          char,
          ::checkers::is_space_or<','>
        > yLoader(&y);
        in >> yLoader;

        loader.m_tuple = std::tuple<int,int>(x, y);

        return in;
    }
};

TEST(TupleTestSuite, DoubleTypeTupleTest) {
    std::tuple<int,int> actual, expected = std::make_tuple<int,int>(5,10);
    std::stringstream in("( 5, 10 )");

    valhalla::utils::loaders::tuple::tupleLoader<
        std::tuple<int,int>,
        DoubleDataLoader
    > loader(actual);
    in >> loader;

    ASSERT_EQ(actual, expected);
}

class ComplexDataLoader {
    std::tuple<int,int,std::string,char> & m_tuple;
public:
    ComplexDataLoader() = default;
    ComplexDataLoader(std::tuple<int,int,std::string,char> & tuple) : m_tuple(tuple) {}

    friend std::istream & operator>>(std::istream & in, ComplexDataLoader & loader) {
        int x, y;
        std::string m_name;
        char m_type;

        ::loaders::primitive::primitiveLoader<
          int,
          char,
          ::checkers::is_space_or<','>
        > xLoader(&x);
        in >> xLoader;

        ::loaders::primitive::primitiveLoader<
          int,
          char,
          ::checkers::is_space_or<','>
        > yLoader(&y);
        in >> yLoader;

        ::loaders::primitive::primitiveLoader<
          std::string,
          char,
          ::checkers::is_space_or<','>
        > nameLoader(&m_name);
        in >> nameLoader;

        ::loaders::primitive::primitiveLoader<
          char,
          char,
          ::checkers::is_space_or<',', '\''>
        > typeLoader(&m_type);
        in >> typeLoader;

        loader.m_tuple = std::tuple<int,int,std::string,char>(x, y, m_name, m_type);

        return in;
    }
};

TEST(TupleTestSuite, ComplexTypeTupleTest) {
    std::tuple<int,int,std::string,char> actual, expected = std::make_tuple<int,int>(5,10,"Hello",'A');
    std::stringstream in("( 5, 10, Hello , 'A' )");

    valhalla::utils::loaders::tuple::tupleLoader<
        std::tuple<int,int,std::string,char>,
        ComplexDataLoader
    > loader(actual);
    in >> loader;

    ASSERT_EQ(actual, expected);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
