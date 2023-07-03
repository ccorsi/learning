/**
 * @file lexicographic_permutationstests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains tests to the problem https://www.techiedelight.com/?problem=LexicographicPermutations
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
#include "lexicographic_permutations.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::utils;
using namespace valhalla::strings::lexicographic_permutations;

// Test Fixture Data Class
class LexicographicPermutationsData {
    std::string m_s;
    std::unordered_set<std::string> m_expected;
public:
    LexicographicPermutationsData() = default;

    std::string const & get_s() { return m_s; }
    std::unordered_set<std::string> const & get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const LexicographicPermutationsData &);
    friend std::istream& operator>>(std::istream&, LexicographicPermutationsData &);

};

std::ostream& operator<<(std::ostream& out, const LexicographicPermutationsData & data) {
    out << "LexicographicPermutationsData [ s=\"" << data.m_s << "\" expected={";
    for (std::string value : data.m_expected) {
        out << " \"" << value << "\"";
    } // for
    return out << " } ]";
}

struct StringReader {
    std::basic_istream<char> & operator()(std::basic_istream<char> & in, std::string & str, int state) {
        if (static_cast<char>(in.peek()) != '"') {
            str += static_cast<char>(in.get());
        }

        return in;
    }
};

struct UnorderedSetReader {
    std::basic_istream<char> & operator()(std::basic_istream<char> & in, std::unordered_set<std::string> & uset, int state) {
        std::string entry;

        ::loaders::loader::v5::dataLoader<
            std::string,
            char,
            StringReader,
            1,
            ::checkers::is_character<char,'"'>,
            ::checkers::is_character<char,'"'>,
            ::checkers::is_space_or<','>,
            ::checkers::is_space_noop<int>
        > entryLoader(entry);
        in >> entryLoader;

        uset.insert(entry);

        return in;
    }
};

std::istream& operator>>(std::istream& in, LexicographicPermutationsData &data) {
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
        std::unordered_set<std::string>,
        char,
        UnorderedSetReader,
        1,
        ::checkers::is_character<char,'{'>,
        ::checkers::is_character<char,'}'>,
        ::checkers::is_space_or<','>
    > expectedLoader(data.m_expected);
    in >> expectedLoader;

    return in;
}

// Test Fixture Class
class LexicographicPermutationsFixture :
    public testing::TestWithParam<LexicographicPermutationsData> {
};

// Parameterized Test Definition
TEST_P(LexicographicPermutationsFixture, LexicographicPermutationsTests) {
    LexicographicPermutationsData data = GetParam();

    Solution solution;

    std::unordered_set<std::string> actual = solution.findLexicographicPermutations(data.get_s());

    ASSERT_EQ(actual, data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(LexicographicPermutationsTests, LexicographicPermutationsFixture, testing::ValuesIn(
    Loader<LexicographicPermutationsData>()(find_path("strings/data/lexicographic_permutations.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
