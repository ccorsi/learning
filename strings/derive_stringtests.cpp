/**
 * @file derive_stringtests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains tests to the problem https://www.techiedelight.com/?problem=DeriveStrings
 * @version 0.1
 * @date 2023-01-01
 * 
 * @copyright Copyright (c) 2023 Claudio Corsi
 * 
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */
#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "derive_string.h"

using namespace valhalla::strings::derive_string;

TEST(DeriveStringTestSuite, DifferentLength) {
    Solution solution;

    std::string left("Two"), right("Three");

    ASSERT_FALSE(solution.exists(left, right)) << "the strings aren't derived from each other";
}

TEST(DeriveStringTestSuite, SameString) {
    Solution solution;

    std::string left("Two"), right("Two");

    ASSERT_TRUE(solution.exists(left, right)) << "the strings are equal";
}

TEST(DeriveStringTestSuite, NoDerivedString) {
    Solution solution;

    std::string left("Two"), right("Six");

    ASSERT_FALSE(solution.exists(left, right)) << "the strings aren't derived from each other";
}

TEST(DeriveStringTestSuite, DerivedString) {
    Solution solution;

    std::string left("ABCD"), right("DABC");

    ASSERT_TRUE(solution.exists(left, right)) << "the strings are derived from each other";
}

TEST(DeriveStringTestSuite, DeriveStringEnds) {
    Solution solution;

    std::string left("ABCDA"), right("DAABC");

    ASSERT_TRUE(solution.exists(left, right)) << "the strings are derived from each other";
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}