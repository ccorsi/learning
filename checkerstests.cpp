/**
 * @file checkerstests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains different tests that will be used to test the different checkers implementations.
 * @version 0.1
 * @date 2024-03-04
 *
 * @copyright Copyright (c) 2024 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include <string>
#include <sstream>

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "checkers.h"

using namespace valhalla::checkers;

/*******************************************
             IS_SPACE TESTS
********************************************/
TEST(CheckersTestSuite, IsSpaceCheckerTest) {
    std::stringstream in("    1");
    skip_spaces<char, is_space> skipSpace;

    skipSpace(in);

    std::string actual;
    std::getline(in, actual);

    ASSERT_EQ(actual, "1");
}

TEST(CheckersTestSuite, IsSpaceWithEndingSpaceCheckerTest) {
    std::stringstream in("    1  ");
    skip_spaces<char, is_space> skipSpace;

    skipSpace(in);

    std::string actual;
    std::getline(in, actual);

    ASSERT_EQ(actual, "1  ");
}

TEST(CheckersTestSuite, IsSpaceOrCheckerTest) {
    std::stringstream in("  ,  1");
    skip_spaces<char, is_space_or<','>> skipSpace;

    skipSpace(in);

    std::string actual;
    std::getline(in, actual);

    ASSERT_EQ(actual, "1");
}

TEST(CheckersTestSuite, IsSpaceOrWithEndingSpacesCheckerTest) {
    std::stringstream in("  ,  1,  ");
    skip_spaces<char, is_space_or<','>> skipSpace;

    skipSpace(in);

    std::string actual;
    std::getline(in, actual);

    ASSERT_EQ(actual, "1,  ");
}

TEST(CheckersTestSuite, IsSpaceOrMultipleCheckerTest) {
    std::stringstream in("  ,.;  1");
    skip_spaces<char, is_space_or<',', '[', ']', '.', ';'>> skipSpace;

    skipSpace(in);

    std::string actual;
    std::getline(in, actual);

    ASSERT_EQ(actual, "1");
}

TEST(CheckersTestSuite, IsSpaceBaseThrowsRuntimeErrorExceptionTest) {
    is_space_base<double, int> check;

    ASSERT_THROW(check('i'), std::runtime_error);
}

struct MyString { static const std::string str; };
const std::string MyString::str = "abc";
struct MyWString { static const std::wstring str; };
const std::wstring MyWString::str = L"abc";

TEST(CheckersTestSuite, UserDefinedContainerTypeTests) {
    skip_chars<MyString> chars;
    skip_characters<MyString> schars;
    skip_wcharacters<MyWString> wchars;

    MyString::str.npos;
    EXPECT_TRUE(chars('a')) << "chars('a') = " << chars('a');
    EXPECT_TRUE(schars('a')) << "schars('a') = " << schars('a');
    EXPECT_TRUE(wchars(L'a')) << "wchars('a') = " << wchars(L'a');
    EXPECT_FALSE(chars('d')) << "chars('d') = " << chars('d');
    EXPECT_FALSE(schars('d')) << "schars('d') = " << schars('d');
    EXPECT_FALSE(wchars(L'd')) << "wchars('d') = " << wchars(L'd');
    EXPECT_TRUE(chars(' ')) << "chars(' ') = " << chars(' ');
    EXPECT_TRUE(schars(' ')) << "schars(' ') = " << schars(' ');
    ASSERT_TRUE(wchars(L' ')) << "wchars(' ') = " << wchars(L' ');
}

/**************************************************************
                      IS CHARACTER TESTS
***************************************************************/

TEST(CheckersTestSuite, IsCharacterCharMultipleChoicesTest) {
    is_character<char, '\'', '"'> check;
    std::stringstream ss("'\" ");

    EXPECT_TRUE(check(ss));
    EXPECT_TRUE(check(ss));
    ASSERT_FALSE(check(ss));
}

TEST(CheckersTestSuite, IsCharacterWChar_tMultipleChoicesTest) {
    is_character<wchar_t, '\'', '"'> check;
    std::wstringstream ss(L"'\" ");

    EXPECT_TRUE(check(ss));
    EXPECT_TRUE(check(ss));
    ASSERT_FALSE(check(ss));
}

TEST(CheckersTestSuite, IsCharacterNoopCharTest) {
    is_character_noop<char> check;
    std::stringstream ss(" ");

    EXPECT_TRUE(check(ss));
    ASSERT_EQ(' ', static_cast<char>(ss.get()));
    ASSERT_EQ(std::string::traits_type::eof(), ss.get());
}

TEST(CheckersTestSuite, IsCharacterNoopWchar_tTest) {
    is_character_noop<wchar_t> check;
    std::wstringstream ss(L" ");

    EXPECT_TRUE(check(ss));
    ASSERT_EQ(' ', static_cast<char>(ss.get()));
    ASSERT_EQ(std::wstring::traits_type::eof(), ss.get());
}

TEST(CheckersTestSuite, IsNoCharacterCharTest) {
    is_no_character<char> check;
    std::stringstream ss(" ");

    EXPECT_FALSE(check(ss));
    ASSERT_TRUE(check(ss));
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
