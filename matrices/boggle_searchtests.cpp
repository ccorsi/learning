/**
 * @file boggle_searchtests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains tests to the problem https://www.techiedelight.com/?problem=BoggleSearch
 * @version 0.1
 * @date 2023-06-20
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
#include "boggle_search.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::utils;
using namespace valhalla::matrices::boggle_search;

// Test Fixture Data Class
class BoggleSearchData {
    std::vector<std::vector<char>> m_input;
    std::unordered_set<std::string> m_words;
    std::unordered_set<std::string> m_expected;
public:
    BoggleSearchData() = default;

    std::vector<std::vector<char>> const & get_input() { return m_input; }
    std::unordered_set<std::string> const & get_words() { return m_words; }
    std::unordered_set<std::string> const & get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const BoggleSearchData &);
    friend std::istream& operator>>(std::istream&, BoggleSearchData &);

};

std::ostream& operator<<(std::ostream& out, const BoggleSearchData & data) {
    out << "BoggleSearchData [ boards=[";
    for (std::vector<char> values : data.m_input) {
        out << " [";
        for (char value : values) {
            out << " '" << value << "'";
        } // for
        out << " ]";
    } // for
    out << " ] words={";
    for (std::string value : data.m_words) {
        out << " \"" << value << "\"";
    } // for
    out << " } expected={";
    for (std::string value : data.m_expected) {
        out << " \"" << value << "\"";
    } // for
    return out << " } ]";
}

struct StringReader {
    std::basic_istream<char> & operator()(std::basic_istream<char> & in, std::string & word, int state) {

        while (static_cast<char>(in.peek()) != '"') {
            word += static_cast<char>(in.get());
        } // while

        return in;
    }
};

struct UnorderedSetReader {
    std::basic_istream<char> & operator()(std::basic_istream<char> & in, std::unordered_set<std::string> & uset, int state) {
        std::string entry;

        ::loaders::loader::v4::dataLoader<
            std::string,
            char,
            StringReader,
            1,
            ::checkers::is_character<char,'"'>,
            ::checkers::is_character<char,'"'>,
            ::checkers::is_space_or<','>
        > entryLoader(entry);
        in >> entryLoader;

        uset.insert(entry);

        return in;
    }
};

struct VectorReader {
    std::basic_istream<char> & operator()(std::basic_istream<char> & in, std::vector<char> & vec, int state) {
        char entry;

        ::loaders::loader::v4::dataLoader<
            char,
            char,
            loader::v4::reader<char,char>,
            1,
            ::checkers::is_character<char,'\''>,
            ::checkers::is_character<char,'\''>,
            ::checkers::is_space_or<','>
        > entryLoader(entry);
        in >> entryLoader;

        vec.push_back(entry);

        return in;
    }
};

struct VectorVectorReader {
    std::basic_istream<char> & operator()(std::basic_istream<char> & in, std::vector<std::vector<char>> & vecvec, int state) {
        std::vector<char> entry;

        ::loaders::loader::v4::dataLoader<
            std::vector<char>,
            char,
            VectorReader,
            1,
            ::checkers::is_character<char,'['>,
            ::checkers::is_character<char,']'>,
            ::checkers::is_space_or<','>
        > entryLoader(entry);
        in >> entryLoader;

        vecvec.push_back(entry);

        return in;
    }
};

std::istream& operator>>(std::istream& in, BoggleSearchData &data) {
    ::loaders::loader::v4::dataLoader<
        std::vector<std::vector<char>>,
        char,
        VectorVectorReader,
        1,
        ::checkers::is_character<char,'['>,
        ::checkers::is_character<char,']'>,
        ::checkers::is_space_or<','>
    > boardsLoader(data.m_input);
    in >> boardsLoader;

    ::loaders::loader::v4::dataLoader<
        std::unordered_set<std::string>,
        char,
        UnorderedSetReader,
        1,
        ::checkers::is_character<char,'['>,
        ::checkers::is_character<char,']'>,
        ::checkers::is_space_or<','>
    > wordsLoader(data.m_words);
    in >> wordsLoader;

    ::loaders::loader::v4::dataLoader<
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
class BoggleSearchFixture :
    public testing::TestWithParam<BoggleSearchData> {
};

// Parameterized Test Definition
TEST_P(BoggleSearchFixture, BoggleSearchTests) {
    BoggleSearchData data = GetParam();

    Solution solution;

    std::unordered_set<std::string> actual = solution.searchBoggle(data.get_input(), data.get_words());

    ASSERT_EQ(actual, data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(BoggleSearchTests, BoggleSearchFixture, testing::ValuesIn(
    Loader<BoggleSearchData>()(find_path("matrices/data/boggle_search.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
