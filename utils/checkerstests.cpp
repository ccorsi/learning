/**
 * @file checkerstests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains tests for the different checkers template implementations
 * @version 0.1
 * @date 2023-04-12
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include <iostream>
#include <sstream>

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "checkers.h"

using namespace valhalla::utils::checkers;

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

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
