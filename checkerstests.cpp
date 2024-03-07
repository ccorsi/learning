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

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "checkers.h"

using namespace valhalla::checkers;

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

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
