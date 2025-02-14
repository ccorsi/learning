/**
 * @file readerstests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief The contains different tests for the defined Reader struct within the readers.h include file
 * @version 0.1
 * @date 2025-02-04
 *
 * @copyright Copyright (c) 2025 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "paths.h"
#include "loaders.h"
#include "readers.h"

using namespace valhalla::utils::readers;
using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::utils;

TEST(ReadersTestSuite, StringReaderTest) {
    std::string str;
    std::string expected = "This is a string";
    std::istringstream in(" \"This is a string\" ");

    ::loaders::loader::v6::dataLoader<
        std::string,
        char,
        StringReader,
        1,
        ::checkers::is_character<char,'"'>,
        ::checkers::is_character<char, '"'>,
        ::checkers::is_space_or<','>,
        ::checkers::is_space_noop<char>
    > StringLoader(str);
    in >> StringLoader;

    ASSERT_EQ(str, expected);
}

TEST(ReadersTestSuite, WStringReaderTest) {
    std::wstring str;
    std::wstring expected = L"This is a string";
    std::wistringstream in(L" \"This is a string\" ");

    ::loaders::loader::v6::dataLoader<
        std::wstring,
        wchar_t,
        WStringReader,
        1,
        ::checkers::is_character<wchar_t,L'"'>,
        ::checkers::is_character<wchar_t, L'"'>,
        ::checkers::is_wspace_or<','>,
        ::checkers::is_space_noop<wchar_t>
    > StringLoader(str);
    in >> StringLoader;

    ASSERT_EQ(str, expected);
}

TEST(ReadersTestSuite, VectorReaderTest) {
    std::vector<int> vec;
    std::vector<int> expected = { 1, 2, 3 };
    std::istringstream in(" { 1, 2, 3 }");

    ::loaders::loader::v6::dataLoader<
        std::vector<int>,
        char,
        VectorReader<int>,
        1,
        ::checkers::is_character<char, '{'>,
        ::checkers::is_character<char, '}'>,
        ::checkers::is_space_or<','>
    > VectorLoader(vec);
    in >> VectorLoader;

    ASSERT_EQ(vec, expected);
}

TEST(ReadersTestSuite, WVectorReaderTest) {
    std::vector<int> vec;
    std::vector<int> expected = { 1, 2, 3 };
    std::wistringstream in(L" { 1, 2, 3 } ");

    ::loaders::loader::v6::dataLoader<
        std::vector<int>,
        wchar_t,
        WVectorReader<int>,
        1,
        ::checkers::is_character<wchar_t, '{'>,
        ::checkers::is_character<wchar_t, '}'>,
        ::checkers::is_wspace_or<','>
    > VectorLoader(vec);
    in >> VectorLoader;

    ASSERT_EQ(vec, expected);
}

TEST(ReadersTestSuite, SetReaderTest) {
    std::set<int> set;
    std::set<int> expected = { 1, 2, 3 };
    std::istringstream in(" { 1, 2, 3 }");

    ::loaders::loader::v6::dataLoader<
        std::set<int>,
        char,
        SetReader<int>,
        1,
        ::checkers::is_character<char, '{'>,
        ::checkers::is_character<char, '}'>,
        ::checkers::is_space_or<','>
    > SetLoader(set);
    in >> SetLoader;

    ASSERT_EQ(set, expected);
}

TEST(ReadersTestSuite, WSetReaderTest) {
    std::set<int> set;
    std::set<int> expected = { 1, 2, 3 };
    std::wistringstream in(L" { 1, 2, 3 }");

    ::loaders::loader::v6::dataLoader<
        std::set<int>,
        wchar_t,
        WSetReader<int>,
        1,
        ::checkers::is_character<wchar_t, '{'>,
        ::checkers::is_character<wchar_t, '}'>,
        ::checkers::is_wspace_or<','>
    > SetLoader(set);
    in >> SetLoader;

    ASSERT_EQ(set, expected);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
