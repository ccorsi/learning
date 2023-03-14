/**
 * @file setloadertests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains tests for the template set loader class
 * @version 0.1
 * @date 2023-03-08
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include <sstream>
#include <unordered_set>

#include "set_loader.h"

#include "gtest/gtest.h"
#include "gmock/gmock.h"

using namespace valhalla::utils::loaders::set;

TEST(SetLoaderTestSuite, SetLoaderTest) {
    std::set<char> actual;
    setLoader<char> loader(actual, '{', '}');

    std::istringstream in("{1 2 3 4}");

    in >> loader;

    std::set<char> expected = { '1', '2', '3', '4'};

    ASSERT_EQ(actual, expected);
}

TEST(SetLoaderTestSuite, SetLoaderWithSpacesTest) {
    std::set<char> actual;
    setLoader<char> loader(actual, '{', '}');

    std::istringstream in("  {  1    2 3 4 }  ");

    in >> loader;

    std::set<char> expected = { '1', '2', '3', '4'};

    ASSERT_EQ(actual, expected);
}

TEST(SetLoaderTestSuite, SetLoaderSkipQuotesAndCommasTest) {
    std::set<char> actual;
    setLoader<char,std::set<char>,char,valhalla::utils::checkers::is_space_or<'\'',','>> loader(actual, '{', '}');

    std::istringstream in("{'1','2','3','4'}");

    in >> loader;

    std::set<char> expected = { '1', '2', '3', '4'};

    ASSERT_EQ(actual, expected);
}

TEST(SetLoaderTestSuite, SetLoaderSkipQuotesAndCommasMultipleLinesTest) {
    std::set<char> actual;
    setLoader<char,std::set<char>,char,valhalla::utils::checkers::is_space_or<'\'',','>> loader(actual, '{', '}');

    std::istringstream in("{'1','2','3',\n'4'}");

    in >> loader;

    std::set<char> expected = { '1', '2', '3', '4'};

    ASSERT_EQ(actual, expected);
}

TEST(SetLoaderTestSuite, SetLoaderUnorderedSetTest) {
    std::unordered_set<char> actual;
    setLoader<char, std::unordered_set<char>> loader(actual, '{', '}');

    std::istringstream in("{1 2 3 4}");

    in >> loader;

    std::unordered_set<char> expected = { '1', '2', '3', '4'};

    ASSERT_EQ(actual, expected);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
