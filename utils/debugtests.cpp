/**
 * @file debugtests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This is the tests for the debug class
 * @version 0.1
 * @date 2022-12-26
 * 
 * @copyright Copyright (c) 2022 Claudio Corsi
 * 
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include "debug.h"

#include "gtest/gtest.h"
#include "gmock/gmock.h"

TEST(DebugTestSuite, DebugOut) {

}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
