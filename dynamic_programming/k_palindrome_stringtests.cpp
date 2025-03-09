/**
 * @file k_palindrome_stringtests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains the tests to the problem https://www.techiedelight.com/?problem=KPalindromeString
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
#include "k_palindrome_string.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::utils::readers;
using namespace valhalla::utils;
using namespace valhalla::dynamic_programming::k_palindrome_string;

// Test Fixture Data Class
class KPalindromeStringData {
    std::string m_s;
    int m_k;
    bool m_expected;
public:
    // KPalindromeStringData() = default;
    KPalindromeStringData() : m_k(-1), m_expected(false) {}

    std::string get_s() { return m_s; }
    int get_k() { return m_k; }
    bool get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const KPalindromeStringData &);
    friend std::istream& operator>>(std::istream&, KPalindromeStringData &);

    friend struct CombinedReader;
};

std::ostream& operator<<(std::ostream& out, const KPalindromeStringData & data) {
    out << "KPalindromeStringData [ s=\"" << data.m_s << "\", k=" << data.m_k << ", expected=";
    out << (data.m_expected ? "true" : "false" ) << " ]";

    return out;
}

struct CombinedReader {
    std::basic_istream<char> & operator()(std::basic_istream<char> & in, KPalindromeStringData & data, int state) {
        switch(state) {
            case 0:
            {
                ::loaders::loader::v6::dataLoader<
                    std::string,
                    char,
                    StringReader,
                    1,
                    ::checkers::is_character<char, '"'>,
                    ::checkers::is_character<char, '"'>,
                    ::checkers::is_space,
                    ::checkers::is_space_noop<char>
                > SLoader(data.m_s);
                in >> SLoader;
            }
            break;
            case 1:
                in >> data.m_k;
            break;
            case 2:
                in >> data.m_expected;
            break;
            default:
                throw std::runtime_error("Invalid state");
        }

        return in;
    }
};

std::istream& operator>>(std::istream& in, KPalindromeStringData &data) {

    ::loaders::loader::v6::dataLoader<
        KPalindromeStringData,
        char,
        CombinedReader,
        3,
        ::checkers::is_character_noop<char>,
        ::checkers::is_no_character<char>,
        ::checkers::is_space_or<','>
    > DataLoader(data);
    in >> DataLoader;

    // ::loaders::loader::v6::dataLoader<
    //     std::string,
    //     char,
    //     StringReader,
    //     1,
    //     ::checkers::is_character<char, '"'>,
    //     ::checkers::is_character<char, '"'>,
    //     ::checkers::is_space_or<','>,
    //     ::checkers::is_space_noop<char>
    // > SLoader(data.m_s);
    // in >> SLoader;

    // ::loaders::loader::v6::dataLoader<int,char> KLoader(data.m_k);
    // in >> KLoader;

    // ::loaders::loader::v6::dataLoader<bool,char> ExpectedLoader(data.m_expected);
    // in >> ExpectedLoader;

    return in;
}

// Test Fixture Class
class KPalindromeStringFixture :
    public testing::TestWithParam<KPalindromeStringData> {
};

// Parameterized Test Definition
TEST_P(KPalindromeStringFixture, KPalindromeStringTests) {
    KPalindromeStringData data = GetParam();

    Solution solution;

    ASSERT_EQ(solution.isKPalindromeString(data.get_s(), data.get_k()), data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(KPalindromeStringTests, KPalindromeStringFixture, testing::ValuesIn(
    Loader<KPalindromeStringData>()(find_path("dynamic_programming/data/k_palindrome_string.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
