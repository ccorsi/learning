/**
 * @file lexicographic_sortingtests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains the tests to the problem https://www.techiedelight.com/?problem=LexicographicSorting
 * @version 0.1
 * @date 2025-02-23
 *
 * @copyright Copyright (c) 2025 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */
#include <iostream>

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "paths.h"
#include "loaders.h"
#include "readers.h"
#include "lexicographic_sorting.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::utils::readers;
using namespace valhalla::utils;
using namespace valhalla::trie::lexicographic_sorting;

// Test Fixture Data Class
class LexicographicSortingData {
    std::unordered_set<std::string> m_input;
    std::vector<std::string> m_expected;
public:
    LexicographicSortingData() = default;

    std::unordered_set<std::string> const & get_input() { return m_input; }
    std::vector<std::string> const & get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const LexicographicSortingData &);
    friend std::istream& operator>>(std::istream&, LexicographicSortingData &);

};

std::ostream& operator<<(std::ostream& out, const LexicographicSortingData & data) {
    out << "LexicographicSortingData [ word={";
    for (auto & word : data.m_input)
        out << " \"" << word << '"';
    out << " }, expected={";
    for (auto & word : data.m_expected)
        out << " \"" << word << '"';
    out << " } ]";

    return out;
}

struct UnorderedSetStringReader {
    std::basic_istream<char> & operator()(std::basic_istream<char> & in, std::unordered_set<std::string> & container, int state) {
        std::string value;

        ::loaders::loader::v6::dataLoader<
            std::string,
            char,
            StringReader,
            1,
            ::checkers::is_character<char, '"'>,
            ::checkers::is_character<char, '"'>,
            ::checkers::is_space_or<','>,
            ::checkers::is_space_noop<char>
        > StringLoader(value);
        in >> StringLoader;

        container.insert(value);

        return in;
    }
};

struct VectorStringReader {
    std::basic_istream<char> & operator()(std::basic_istream<char> & in, std::vector<std::string> & container, int state) {
        std::string value;

        ::loaders::loader::v6::dataLoader<
            std::string,
            char,
            StringReader,
            1,
            ::checkers::is_character<char, '"'>,
            ::checkers::is_character<char, '"'>,
            ::checkers::is_space_or<','>,
            ::checkers::is_space_noop<char>
        > StringLoader(value);
        in >> StringLoader;

        container.push_back(value);

        return in;
    }
};

std::istream& operator>>(std::istream& in, LexicographicSortingData &data) {
    ::loaders::loader::v6::dataLoader<
        std::unordered_set<std::string>,
        char,
        UnorderedSetStringReader,
        1,
        ::checkers::is_character<char, '{'>,
        ::checkers::is_character<char, '}'>,
        ::checkers::is_space_or<','>,
        ::checkers::is_space_or<','>
    > InputLoader(data.m_input);
    in >> InputLoader;

    ::loaders::loader::v6::dataLoader<
        std::vector<std::string>,
        char,
        VectorStringReader,
        1,
        ::checkers::is_character<char, '{'>,
        ::checkers::is_character<char, '}'>,
        ::checkers::is_space_or<','>,
        ::checkers::is_space_or<','>
    > ExpectedLoader(data.m_expected);
    in >> ExpectedLoader;

    return in;
}

// Test Fixture Class
class LexicographicSortingFixture :
    public testing::TestWithParam<LexicographicSortingData> {
};

// Parameterized Test Definition
TEST_P(LexicographicSortingFixture, LexicographicSortingTests) {
    LexicographicSortingData data = GetParam();

    Solution solution;

    ASSERT_EQ(solution.lexicographicSort(data.get_input()), data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(LexicographicSortingTests, LexicographicSortingFixture, testing::ValuesIn(
    Loader<LexicographicSortingData>()(find_path("trie/data/lexicographic_sorting.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
