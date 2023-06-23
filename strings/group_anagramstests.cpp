/**
 * @file group_anagramstests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains tests to the problem https://www.techiedelight.com/?problem=GroupAnagrams
 * @version 0.1
 * @date 2023-06-23
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
#include "group_anagrams.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::utils;
using namespace valhalla::strings::group_anagrams;

// Test Fixture Data Class
class GroupAnagramsData {
    std::vector<std::string> m_words;
    std::set<std::set<std::string>> m_expected;
public:
    GroupAnagramsData() = default;

    std::vector<std::string> const & get_words() { return m_words; }
    std::set<std::set<std::string>> const & get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const GroupAnagramsData &);
    friend std::istream& operator>>(std::istream&, GroupAnagramsData &);

};

std::ostream& operator<<(std::ostream& out, const GroupAnagramsData & data) {
    out << "GroupAnagramsData [ words=[";
    for (std::string value : data.m_words) {
        out << " \"" << value << "\"";
    } // for
    out << " ] expected={";
    for (std::set<std::string> values : data.m_expected) {
        out << " [";
        for (std::string value : values) {
            out << " \"" << value << "\"";
        } // for
        out << " ]";
    } // for
    return out << " } ]";
}

struct StringReader {
    std::basic_istream<char> & operator()(std::basic_istream<char> & in, std::string & str, int state) {

        str += static_cast<char>(in.get());

        return in;
    }
};

struct VectorReader {
    std::basic_istream<char> & operator()(std::basic_istream<char> & in, std::vector<std::string> & vec, int state) {
        std::string entry;

        ::loaders::loader::v4::dataLoader<
            std::string,
            char,
            StringReader,
            1,
            ::checkers::is_character<char,'"'>,
            ::checkers::is_character<char,'"'>,
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

        sset.insert(entry);

        return in;
    }
};

struct SetSetReader {
    std::basic_istream<char> & operator()(std::basic_istream<char> & in, std::set<std::set<std::string>> & setset, int state) {
        std::set<std::string> entry;

        ::loaders::loader::v4::dataLoader<
            std::set<std::string>,
            char,
            SetReader,
            1,
            ::checkers::is_character<char,'['>,
            ::checkers::is_character<char,']'>,
            ::checkers::is_space_or<','>
        > entryLoader(entry);
        in >> entryLoader;

        setset.insert(entry);

        return in;
    }
};
std::istream& operator>>(std::istream& in, GroupAnagramsData &data) {
    ::loaders::loader::v4::dataLoader<
        std::vector<std::string>,
        char,
        VectorReader,
        1,
        ::checkers::is_character<char,'['>,
        ::checkers::is_character<char,']'>,
        ::checkers::is_space_or<','>
    > wordsLoader(data.m_words);
    in >> wordsLoader;

    ::loaders::loader::v4::dataLoader<
        std::set<std::set<std::string>>,
        char,
        SetSetReader,
        1,
        ::checkers::is_character<char,'{'>,
        ::checkers::is_character<char,'}'>,
        ::checkers::is_space_or<','>
    > expectedLoader(data.m_expected);
    in >> expectedLoader;

    return in;
}

// Test Fixture Class
class GroupAnagramsFixture :
    public testing::TestWithParam<GroupAnagramsData> {
};

// Parameterized Test Definition
TEST_P(GroupAnagramsFixture, GroupAnagramsTests) {
    GroupAnagramsData data = GetParam();

    Solution solution;

    std::set<std::set<std::string>> actual = solution.groupAnagrams(data.get_words());

    ASSERT_EQ(actual, data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(GroupAnagramsTests, GroupAnagramsFixture, testing::ValuesIn(
    Loader<GroupAnagramsData>()(find_path("strings/data/group_anagrams.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
