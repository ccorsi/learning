/**
 * @file rotated_palindrometests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains tests to the problem https://www.techiedelight.com/?problem=RotatedPalindrome
 * @version 0.1
 * @date 2023-01-02
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "rotated_palindrome.h"

using namespace valhalla::strings::rotated_palindrome;

TEST(RotatedPalindromeTestSuite, EmptyString) {
    Solution solution;

    std::string str;

    ASSERT_TRUE(solution.exists(str)) << "an empty string is a palindrome";
}

TEST(RotatedPalindromeTestSuite, SingleCharacterString) {
    Solution solution;

    std::string str("A");

    ASSERT_TRUE(solution.exists(str)) << "a single character is a palindrome";
}

TEST(RotatedPalindromeTestSuite, InvalidTwoCharacterString) {
    Solution solution;

    std::string str("AB");

    ASSERT_FALSE(solution.exists(str)) << "not a palindrome string";
}

TEST(RotatedPalindromeTestSuite, ValidTwoCharacterString) {
    Solution solution;

    std::string str("AA");

    ASSERT_TRUE(solution.exists(str)) << "it is a palindrome string";
}

TEST(RotatedPalindromeTestSuite, InvalidThreeCharacterString) {
    Solution solution;

    std::string str("ABC");

    ASSERT_FALSE(solution.exists(str)) << "not a palindrome string";
}

TEST(RotatedPalindromeTestSuite, ValidThreeCharacterString) {
    Solution solution;

    std::string str("ABA");

    ASSERT_TRUE(solution.exists(str)) << "it is a palindrome string";
}

TEST(RotatedPalindromeTestSuite, ValidRotatedThreeCharacterString) {
    Solution solution;

    std::string str("BAA");

    ASSERT_TRUE(solution.exists(str)) << "it is a palindrome string";
}

TEST(RotatedPalindromeTestSuite, ValidRotatedSevenCharacterString) {
    Solution solution;

    std::string str("CBAABCD");

    ASSERT_TRUE(solution.exists(str)) << "it is a palindrome string";
}

TEST(RotatedPalindromeTestSuite, ValidRotatedSixCharacterString) {
    Solution solution;

    std::string str("BAABCC");

    ASSERT_TRUE(solution.exists(str)) << "it is a palindrome string";
}

TEST(RotatedPalindromeTestSuite, InvalidFiveCharacterString) {
    Solution solution;

    std::string str("DCABC");

    ASSERT_FALSE(solution.exists(str)) << "not a palindrome string";
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}