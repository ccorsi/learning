/**
 * @file maploadertests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains tests for the mapLoader template implementation.
 * @version 0.1
 * @date 2023-06-01
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include <sstream>
#include <unordered_map>

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "map_loader.h"

using namespace valhalla::utils;

TEST(MapLoaderTestSuite, MapLoaderTest) {
    std::map<char,char> data, expected = { { 'A', 'B'}, { 'C', 'D' } };
    std::stringstream in("{ 'A':'B', 'C' : 'D' }");

    loaders::map::mapLoader<
        char,
        char,
        std::map<char,char>,
        char,
        '{',
        '}',
        ':',
        checkers::is_space_or<',','\''>
    > loader(data);

    in >> loader;

    ASSERT_EQ(data, expected);
}

TEST(MapLoaderTestSuite, UnorderedMapLoaderTest) {
    std::unordered_map<char,char> data, expected = { { 'A', 'B'}, { 'C', 'D' } };
    std::stringstream in("{ 'A':'B', 'C' : 'D' }");

    loaders::map::mapLoader<
        char,
        char,
        std::unordered_map<char,char>,
        char,
        '{',
        '}',
        ':',
        checkers::is_space_or<',','\''>
    > loader(data);

    in >> loader;

    ASSERT_EQ(data, expected);
}

TEST(MapLoaderTestSuite, DefaultMapLoaderTest) {
    std::map<char,char> data, expected = { { 'A', 'B'}, { 'C', 'D' } };
    std::stringstream in("{ A : B C : D }");

    loaders::map::mapLoader<char,char> loader(data);

    in >> loader;

    ASSERT_EQ(data, expected);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
