/**
 * @file shortest_unique_prefixtests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains test for the problem https://www.techiedelight.com/?problem=ShortestUniquePrefix
 * @version 0.1
 * @date 2025-03-09
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
#include "shortest_unique_prefix.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::utils::readers;
using namespace valhalla::utils;
using namespace valhalla::trie::shortest_unique_prefix;

// Test Fixture Data Class
class ShortestUniquePrefixData {
    std::vector<std::string> m_input;
    std::vector<std::string> m_expected;
public:
    ShortestUniquePrefixData() = default;

    std::vector<std::string> const & get_input() { return m_input; }
    std::vector<std::string> const & get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const ShortestUniquePrefixData &);
    friend std::istream& operator>>(std::istream&, ShortestUniquePrefixData &);

    friend struct CombinedReader;
};

std::ostream& operator<<(std::ostream& out, const ShortestUniquePrefixData & data) {
    out << "ShortestUniquePrefixData [ input={";
    for (auto & word : data.m_input)
        out << " \"" << word << '"';
    out << " }, expected={";
    for (auto & word : data.m_expected)
        out << " \"" << word << '"';
    out << " } ]";

    return out;
}

struct VectorStringReader {
    std::basic_istream<char> & operator()(std::basic_istream<char> & in, std::vector<std::string> & vec, int state) {
        std::string str;

        ::loaders::loader::v6::dataLoader<
            std::string,
            char,
            StringReader,
            1,
            ::checkers::is_character<char, '"'>,
            ::checkers::is_character<char, '"'>,
            ::checkers::is_space
        > StringLoader(str);
        in >> StringLoader;

        vec.push_back(str);

        return in;
    }
};

struct CombinedReader {
    std::basic_istream<char> & operator()(std::basic_istream<char> & in, ShortestUniquePrefixData & data, int state) {
        std::vector<std::string> * input;
        switch (state) {
            case 0:
                input = & data.m_input;
            break;
            case 1:
                input = & data.m_expected;
            break;
            default:
                throw std::runtime_error("INVALID STATE");
        } // switch (state)

        ::loaders::loader::v6::dataLoader<
            std::vector<std::string>,
            char,
            VectorStringReader,
            1,
            ::checkers::is_character<char, '{'>,
            ::checkers::is_character<char, '}'>,
            ::checkers::is_space_or<','>
        > InputLoader(*input);
        in >> InputLoader;

        return in;
    }
};

std::istream& operator>>(std::istream& in, ShortestUniquePrefixData &data) {
    ::loaders::loader::v6::dataLoader<
        ShortestUniquePrefixData,
        char,
        CombinedReader,
        2,
        ::checkers::is_character<char, '{'>,
        ::checkers::is_character<char, '}'>,
        ::checkers::is_space_or<','>
    > CombinedLoader(data);
    return in >> CombinedLoader;
}

// Test Fixture Class
class ShortestUniquePrefixFixture :
    public testing::TestWithParam<ShortestUniquePrefixData> {
};

// Parameterized Test Definition
TEST_P(ShortestUniquePrefixFixture, ShortestUniquePrefixTests) {
    ShortestUniquePrefixData data = GetParam();

    Solution solution;

    ASSERT_EQ(solution.findShortestUniquePrefix(data.get_input()), data.get_expected());

}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(ShortestUniquePrefixTests, ShortestUniquePrefixFixture, testing::ValuesIn(
    Loader<ShortestUniquePrefixData>()(find_path("trie/data/shortest_unique_prefix.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
