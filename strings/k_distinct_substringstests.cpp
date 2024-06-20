/**
 * @file k_distinct_substringstests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains tests to the problem https://www.techiedelight.com/?problem=KDistinctSubstrings
 * @version 0.1
 * @date 2023-07-03
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
#include "k_distinct_substrings.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::utils;
using namespace valhalla::strings::k_distinct_substrings;

// Test Fixture Data Class
class KDistinctSubstringsData {
    std::string m_s;
    int m_k;
    std::unordered_set<std::string> m_expected;
public:
    KDistinctSubstringsData() = default;

    std::string const & get_s() { return m_s; }
    int get_k() { return m_k; }
    std::unordered_set<std::string> const & get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const KDistinctSubstringsData &);
    friend std::istream& operator>>(std::istream&, KDistinctSubstringsData &);

};

std::ostream& operator<<(std::ostream& out, const KDistinctSubstringsData & data) {
    out << "KDistinctSubstringsData [ s=\"" << data.m_s << "\" k=" << data.m_k
        << " expected={";
    for (std::string value : data.m_expected) {
        out << " \"" << value << '"';
    } // for
    out << " } ]";

    return out;
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

std::istream& operator>>(std::istream& in, KDistinctSubstringsData &data) {
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
    > kLoader(data.m_k);
    in >> kLoader;

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
class KDistinctSubstringsFixture :
    public testing::TestWithParam<KDistinctSubstringsData> {
};

// Parameterized Test Definition
TEST_P(KDistinctSubstringsFixture, KDistinctSubstringsTests) {
    KDistinctSubstringsData data = GetParam();

    Solution solution;

    std::unordered_set<std::string> actual = solution.findDistinctSubstrings(data.get_s(), data.get_k());

    ASSERT_EQ(actual, data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(KDistinctSubstringsTests, KDistinctSubstringsFixture, testing::ValuesIn(
    Loader<KDistinctSubstringsData>()(find_path("strings/data/k_distinct_substrings.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}