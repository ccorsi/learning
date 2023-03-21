/**
 * @file debugtests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains the tests for the debug class
 * @version 0.2
 * @date 2022-12-26
 * 
 * @copyright Copyright (c) 2022 Claudio Corsi
 * 
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include "debug.h"

#include <iostream>
#include <fstream>
#include <cstdlib>

#include "gtest/gtest.h"
#include "gmock/gmock.h"

TEST(DebugTestSuite, DebugOut) {
    const int entries = 5;
    int count = 0;

    while (count++ < entries) {
        LOGMSG("Writing Log Entry");
    }

    std::ifstream file("debug.txt");

    std::string line;

    count = 0;

    while (std::getline(file, line)) {
        // std::cout << "line=\"" << line << "\"" << std::endl;
        if (line.find("LOG:") != std::string::npos && line.find("Writing Log Entry") != std::string::npos) {
            count++;
        } // if
    } // while

    file.close();

    ASSERT_EQ(count, entries);
}

int main(int argc, char** argv) {
    // std::cout << "Setting DEBUGTEST to 1" << std::endl;
#ifdef _WIN32
    _putenv("DEBUGTEST=1");
#else
    putenv("DEBUGTEST=1");
#endif
    // std::cout << "Set DEBUGTEST to 1" << std::endl;
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
