/**
 * @file first_non_repeating_charactertests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains tests to the problem https://www.techiedelight.com/?problem=FirstNonRepeatingCharacter
 * @version 0.1
 * @date 2023-07-02
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
#include "first_non_repeating_character.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::utils;
using namespace valhalla::strings::first_non_repeating_character;

// Test Fixture Data Class
class FirstNonRepeatingCharacterData {
    std::string m_s;
    int m_expected;
public:
    FirstNonRepeatingCharacterData() = default;

    std::string const & get_s() { return m_s; }
    int get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const FirstNonRepeatingCharacterData &);
    friend std::istream& operator>>(std::istream&, FirstNonRepeatingCharacterData &);

};

std::ostream& operator<<(std::ostream& out, const FirstNonRepeatingCharacterData & data) {
    return out << "FirstNonRepeatingCharacterData [ s=\"" << data.m_s << "\" expected="
        << data.m_expected << " ]";
}

struct StringReader {
    std::basic_istream<char> & operator()(std::basic_istream<char> & in, std::string & str, int state) {
        if (static_cast<char>(in.peek()) != '"') {
            str += static_cast<char>(in.get());
        }

        return in;
    }
};

std::istream& operator>>(std::istream& in, FirstNonRepeatingCharacterData &data) {
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
        int,
        char,
        loader::v5::reader<int,char>,
        1,
        ::checkers::is_character_noop<char>,
        ::checkers::is_no_character<char>,
        ::checkers::is_space_or<','>
    > expectedLoader(data.m_expected);
    in >> expectedLoader;

    return in;
}

// Test Fixture Class
class FirstNonRepeatingCharacterFixture :
    public testing::TestWithParam<FirstNonRepeatingCharacterData> {
};

// Parameterized Test Definition
TEST_P(FirstNonRepeatingCharacterFixture, FirstNonRepeatingCharacterTests) {
    FirstNonRepeatingCharacterData data = GetParam();

    Solution solution;

    int actual = solution.findFirstNonRepeating(data.get_s());

    ASSERT_EQ(actual, data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(FirstNonRepeatingCharacterTests, FirstNonRepeatingCharacterFixture, testing::ValuesIn(
    Loader<FirstNonRepeatingCharacterData>()(find_path("strings/data/first_non_repeating_character.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
