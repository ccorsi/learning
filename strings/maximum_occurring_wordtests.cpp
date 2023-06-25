/**
 * @file maximum_occurring_wordtests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains tests to the problem https://www.techiedelight.com/?problem=MaximumOccurringWord
 * @version 0.1
 * @date 2023-06-24
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */
#include <iostream>
#include <set>

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "paths.h"
#include "loaders.h"
#include "maximum_occurring_word.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::utils;
using namespace valhalla::strings::maximum_occurring_word;

// Test Fixture Data Class
class MaximumOccurringWordData {
    std::vector<std::string> m_words;
    std::set<std::string> m_expected;
public:
    MaximumOccurringWordData() = default;

    std::vector<std::string> const & get_words() { return m_words; }
    std::set<std::string> const & get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const MaximumOccurringWordData &);
    friend std::istream& operator>>(std::istream&, MaximumOccurringWordData &);

};

std::ostream& operator<<(std::ostream& out, const MaximumOccurringWordData & data) {
    out << "MaximumOccurringWordData [ words=[";
    for (std::string value : data.m_words) {
        out << " \"" << value << "\"";
    } // for
    out << " ] expected={";
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

struct VectorReader {
    std::basic_istream<char> & operator()(std::basic_istream<char> & in, std::vector<std::string> & vec, int state) {
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

        vec.push_back(entry);

        return in;
    }
};

struct SetReader {
    std::basic_istream<char> & operator()(std::basic_istream<char> & in, std::set<std::string> & sset, int state) {
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

        sset.insert(entry);

        return in;
    }
};

std::istream& operator>>(std::istream& in, MaximumOccurringWordData &data) {
    ::loaders::loader::v5::dataLoader<
        std::vector<std::string>,
        char,
        VectorReader,
        1,
        ::checkers::is_character<char,'['>,
        ::checkers::is_character<char,']'>,
        ::checkers::is_space_or<','>,
        ::checkers::is_space_or<','>
    > wordsLoader(data.m_words);
    in >> wordsLoader;

    ::loaders::loader::v5::dataLoader<
        std::set<std::string>,
        char,
        SetReader,
        1,
        ::checkers::is_character<char,'{'>,
        ::checkers::is_character<char,'}'>,
        ::checkers::is_space_or<','>,
        ::checkers::is_space_or<','>
    > expectedLoader(data.m_expected);
    in >> expectedLoader;

    return in;
}

// Test Fixture Class
class MaximumOccurringWordFixture :
    public testing::TestWithParam<MaximumOccurringWordData> {
};

// Parameterized Test Definition
TEST_P(MaximumOccurringWordFixture, MaximumOccurringWordTests) {
    MaximumOccurringWordData data = GetParam();

    Solution solution;

    std::string actual = solution.lexigraphicSort(data.get_words());

    ASSERT_THAT(actual, testing::AnyOfArray(data.get_expected()));
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(MaximumOccurringWordTests, MaximumOccurringWordFixture, testing::ValuesIn(
    Loader<MaximumOccurringWordData>()(find_path("strings/data/maximum_occurring_word.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
