/**
 * @file lexical_minimal_string_rotationtests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains tests to the problem https://www.techiedelight.com/?problem=LexicalMinimalStringRotation
 * @version 0.1
 * @date 2023-06-26
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */
#include <iostream>

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "paths.h"
#include "loaders.h"
#include "lexical_minimal_string_rotation.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::utils;
using namespace valhalla::strings::lexical_minimal_string_rotation;

// Test Fixture Data Class
class LexicalMinimalStringRotationData {
    std::string m_s, m_expected;
public:
    LexicalMinimalStringRotationData() = default;

    std::string const & get_s() { return m_s; }
    std::string const & get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const LexicalMinimalStringRotationData &);
    friend std::istream& operator>>(std::istream&, LexicalMinimalStringRotationData &);

};

std::ostream& operator<<(std::ostream& out, const LexicalMinimalStringRotationData & data) {
    return out << "LexicalMinimalStringRotationData [ s=\"" << data.m_s << "\" expected=\""
        << data.m_expected << "\" ]";
}

struct StringReader {
    std::basic_istream<char> & operator()(std::basic_istream<char> & in, std::string & str, int state) {
        if (static_cast<char>(in.peek()) != '"') {
            str += static_cast<char>(in.get());
        }

        return in;
    }
};

std::istream& operator>>(std::istream& in, LexicalMinimalStringRotationData &data) {
    ::loaders::loader::v5::dataLoader<
        std::string,
        char,
        StringReader,
        1,
        ::checkers::is_character<char,'"'>,
        ::checkers::is_character<char,'"'>,
        ::checkers::is_space_or<','>,
        ::checkers::is_space_noop<int>
    > sLoader(data.m_s);
    in >> sLoader;

    ::loaders::loader::v5::dataLoader<
        std::string,
        char,
        StringReader,
        1,
        ::checkers::is_character<char,'"'>,
        ::checkers::is_character<char,'"'>,
        ::checkers::is_space_or<','>,
        ::checkers::is_space_noop<int>
    > expectedLoader(data.m_expected);
    in >> expectedLoader;

    return in;
}

// Test Fixture Class
class LexicalMinimalStringRotationFixture :
    public testing::TestWithParam<LexicalMinimalStringRotationData> {
};

// Parameterized Test Definition
TEST_P(LexicalMinimalStringRotationFixture, LexicalMinimalStringRotationTests) {
    LexicalMinimalStringRotationData data = GetParam();

    Solution solution;

    std::string actual = solution.findLexicalMinRotation(data.get_s());

    ASSERT_EQ(actual, data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(LexicalMinimalStringRotationTests, LexicalMinimalStringRotationFixture, testing::ValuesIn(
    Loader<LexicalMinimalStringRotationData>()(find_path("strings/data/lexical_minimal_string_rotation.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
