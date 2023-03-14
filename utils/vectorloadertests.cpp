/**
 * @file vectorloadertests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains different tests for the vectorLoader class
 * @version 0.1
 * @date 2023-03-08
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include <sstream>
#include <algorithm>
#include <cstdarg>

#include "vector_loader.h"
#include "checkers.h"

#include "gtest/gtest.h"
#include "gmock/gmock.h"

using namespace valhalla::utils::loaders::vectors;
using namespace valhalla::utils::checkers;

TEST(VectorLoaderTestSuite, VectorLoaderCharTest) {
    std::vector<char> input;
    vectorLoader<char> loader(input, '[', ']');

    std::istringstream in(std::string("[ a b c ]"));

    in >> loader;

    std::vector<char> expected = { 'a', 'b', 'c' };

    ASSERT_EQ(input, expected);
}

TEST(VectorLoaderTestSuite, VectorLoaderWCharTest) {
    std::vector<wchar_t> input;
    vectorLoader<wchar_t,
        std::vector<wchar_t>,
        wchar_t,
        valhalla::utils::checkers::is_wspace> loader(input, '[', ']');

    std::vector<wchar_t> chars = { '[', ' ', 'a', ' ', 'b', ' ', 'c', ']'};
    std::wstring data(chars.begin(), chars.end());

    std::wistringstream in(data);

    in >> loader;

    std::vector<wchar_t> expected = { 'a', 'b', 'c' };

    ASSERT_EQ(input, expected);
}

TEST(VectorLoaderTestSuite, VectorLoaderWithSkipCommaTest) {
    std::vector<char> input;

    vectorLoader<char,
                 std::vector<char>,
                 char,
                 is_space_or<','>> loader(input, '[', ']');

    std::istringstream in(std::string("[a,b,c]"));

    in >> loader;

    std::vector<char> expected = { 'a', 'b', 'c' };

    ASSERT_EQ(input, expected);
}

TEST(VectorLoaderTestSuite, VectorLoaderWithUserDefinedSkipTest) {
    std::vector<char> input;

    vectorLoader<char,
                 std::vector<char>,
                 char,
                 is_space_or<'\''>> loader(input, '[', ']');

    std::istringstream in(std::string("['a' 'b' 'c']"));

    in >> loader;

    std::vector<char> expected = { 'a', 'b', 'c' };

    ASSERT_EQ(input, expected);
}

struct skip_from {
    bool operator()(int chr) {
        static std::vector<char> chars = {'\'', ','};
        return std::isspace(chr) != 0 || std::find(chars.begin(), chars.end(), static_cast<char>(chr)) != chars.end();
    }
};

TEST(VectorLoaderTestSuite, VectorLoaderWithUserDefinedSkipsTest) {
    std::vector<char> input;

    vectorLoader<char,
                 std::vector<char>,
                 char,
                 is_space_or<'\'', ','>> loader(input, '[', ']');

    std::istringstream in(std::string("['a', 'b', 'c']"));

    in >> loader;

    std::vector<char> expected = { 'a', 'b', 'c' };

    ASSERT_EQ(input, expected);
}

TEST(VectorLoaderTestSuite, VectorLoaderWithLeadingSpacesTest) {
    std::vector<char> input;
    vectorLoader<char> loader(input, '[', ']');

    std::istringstream in(std::string(" [ a b c ]"));

    in >> loader;

    std::vector<char> expected = { 'a', 'b', 'c' };

    ASSERT_EQ(input, expected);
}

TEST(VectorLoaderTestSuite, VectorLoaderWithEndingSpacesTest) {
    std::vector<char> input;
    vectorLoader<char> loader(input, '[', ']');

    std::istringstream in(std::string("[ a b c ]  "));

    in >> loader;

    std::vector<char> expected = { 'a', 'b', 'c' };

    ASSERT_EQ(input, expected);
}

TEST(VectorLoaderTestSuite, VectorLoaderWithVariableLengthSpacesTest) {
    std::vector<char> input;
    vectorLoader<char> loader(input, '[', ']');

    std::istringstream in(std::string("    [     a  b c]    "));

    in >> loader;

    std::vector<char> expected = { 'a', 'b', 'c' };

    ASSERT_EQ(input, expected);
}

TEST(VectorLoaderTestSuite, VectorLoaderEmptyVectorTest) {
    std::vector<char> input;
    vectorLoader<char> loader(input, '[', ']');

    std::istringstream in(std::string("[]"));

    in >> loader;

    std::vector<char> expected = {};

    ASSERT_EQ(input, expected);
}

TEST(VectorLoaderTestSuite, VectorLoaderEmptyVectorWithSpacesTest) {
    std::vector<char> input;
    vectorLoader<char> loader(input, '[', ']');

    std::istringstream in(std::string("  [ ] \n"));

    in >> loader;

    std::vector<char> expected = {};

    ASSERT_EQ(input, expected);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
