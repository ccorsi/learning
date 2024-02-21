/**
 * @file permutationstests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains tests to the problem https://www.techiedelight.com/?problem=Permutations
 * @version 0.1
 * @date 2023-06-24
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
#include "permutations.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::utils;
using namespace valhalla::strings::permutations;

// Test Fixture Data Class
class PermutationsData {
    std::string m_s;
    std::vector<std::string> m_expected;
public:
    PermutationsData() = default;

    std::string const & get_s() { return m_s; }
    std::vector<std::string> const & get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const PermutationsData &);
    friend std::istream& operator>>(std::istream&, PermutationsData &);

};

std::ostream& operator<<(std::ostream& out, const PermutationsData & data) {
    out << "PermutationsData [ s=\"" << data.m_s << "\" expected=[";
    for (std::string value : data.m_expected) {
        out << " \"" << value << "\"";
    } // for
    return out << " ] ]";
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

std::istream& operator>>(std::istream& in, PermutationsData &data) {
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
        std::vector<std::string>,
        char,
        VectorReader,
        1,
        ::checkers::is_character<char,'['>,
        ::checkers::is_character<char,']'>,
        ::checkers::is_space_or<','>,
        ::checkers::is_space_or<','>
    > expectedLoader(data.m_expected);
    in >> expectedLoader;

    return in;
}

// Test Fixture Class
class PermutationsFixture :
    public testing::TestWithParam<PermutationsData> {
};

// Parameterized Test Definition
TEST_P(PermutationsFixture, PermutationsTests) {
    PermutationsData data = GetParam();

    Solution solution;

    std::vector<std::string> actual = solution.findPermutations(data.get_s());

    ASSERT_EQ(actual, data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(PermutationsTests, PermutationsFixture, testing::ValuesIn(
    Loader<PermutationsData>()(find_path("strings/data/permutations.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}