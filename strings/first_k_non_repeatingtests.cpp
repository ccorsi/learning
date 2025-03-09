/**
 * @file first_k_non_repeatingtests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains tests to the problem https://www.techiedelight.com/?problem=FirstKNonRepeating
 * @version 0.1
 * @date 2025-02-22
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
#include "first_k_non_repeating.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::utils::readers;
using namespace valhalla::utils;
using namespace valhalla::strings::first_k_non_repeating;

// Test Fixture Data Class
class FirstKNonRepeatingData {
    std::string m_s;
    int m_k;
    std::vector<char> m_expected;

public:
    FirstKNonRepeatingData() = default;

    std::string get_s() { return m_s; }
    int get_k() { return m_k; }
    std::vector<char> const & get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const FirstKNonRepeatingData &);
    friend std::istream& operator>>(std::istream&, FirstKNonRepeatingData &);

};

std::ostream& operator<<(std::ostream& out, const FirstKNonRepeatingData & data) {
    out << "FirstKNonRepeatingData [ s=\"" << data.m_s << "\", k=" << data.m_k << ", expected={";
    for (char chr : data.m_expected) {
        out << " '" << chr << '\'';
    }
    out << " } ]";

    return out;
}

struct VectorCharReader {
    std::basic_istream<char> & operator()(std::basic_istream<char> & in, std::vector<char> & vec, int state) {
        char chr;

        ::loaders::loader::v6::dataLoader<
            char,
            char,
            ::loaders::loader::v6::reader<char,char>,
            1,
            ::checkers::is_character<char, '\''>,
            ::checkers::is_character<char, '\''>,
            ::checkers::is_space_or<','>,
            ::checkers::is_space_or<','>
        > CharLoader(chr);
        in >> CharLoader;

        vec.push_back(chr);

        return in;
    }
};

std::istream& operator>>(std::istream& in, FirstKNonRepeatingData &data) {
    ::loaders::loader::v6::dataLoader<
        std::string,
        char,
        StringReader,
        1,
        ::checkers::is_character<char, '"'>,
        ::checkers::is_character<char, '"'>,
        ::checkers::is_space_or<','>,
        ::checkers::is_space_noop<char>
    > SLoader(data.m_s);
    in >> SLoader;

    ::loaders::loader::v6::dataLoader<int,char> KLoader(data.m_k);
    in >> KLoader;

    ::loaders::loader::v6::dataLoader<
        std::vector<char>,
        char,
        VectorCharReader,
        1,
        ::checkers::is_character<char, '['>,
        ::checkers::is_character<char, ']'>,
        ::checkers::is_space_or<','>,
        ::checkers::is_space_or<','>
    > ExpectedLoader(data.m_expected);
    in >> ExpectedLoader;

    return in;
}

// Test Fixture Class
class FirstKNonRepeatingFixture :
    public testing::TestWithParam<FirstKNonRepeatingData> {
};

// Parameterized Test Definition
TEST_P(FirstKNonRepeatingFixture, FirstKNonRepeatingTests) {
    FirstKNonRepeatingData data = GetParam();

    Solution solution;

    ASSERT_EQ(solution.findFirstKNonRepeating(data.get_s(), data.get_k()), data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(FirstKNonRepeatingTests, FirstKNonRepeatingFixture, testing::ValuesIn(
    Loader<FirstKNonRepeatingData>()(find_path("strings/data/first_k_non_repeating.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
