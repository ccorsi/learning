/**
 * @file longest_common_subsequence_twotests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains tests to the problem https://www.techiedelight.com/?problem=LongestCommonSubsequenceII
 * @version 0.1
 * @date 2026-05-22
 *
 * @copyright Copyright (c) 2026 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include <iostream>

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "paths.h"
#include "loaders.h"
#include "readers.h"
#include "longest_common_subsequence_two.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::utils::readers;
using namespace valhalla::utils;
using namespace valhalla::dynamic_programming::longest_common_subsequence_two;

// Test Fixture Data Class
class LongestCommonSubsequenceTwoData {
    std::string m_x, m_y;
    std::set<std::string> m_expected;
public:
    LongestCommonSubsequenceTwoData() = default;

    std::string get_x() { return m_x; }
    std::string get_y() { return m_y; }
    std::set<std::string> const & get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const LongestCommonSubsequenceTwoData &);
    friend std::istream& operator>>(std::istream&, LongestCommonSubsequenceTwoData &);

    friend struct CombinedReader;
};

std::ostream& operator<<(std::ostream& out, const LongestCommonSubsequenceTwoData & data) {
    out << "LongestCommonSubsequenceTwoData [ X=\"" << data.m_x << "\" Y=\"" << data.m_y;
    out << " expected=[";
    for (const std::string & str : data.m_expected)
        out << " \"" << str << "\"";
    out << " ] ]";

    return out;
}

struct SetLCSReader {
    std::basic_istream<char> & operator()(std::basic_istream<char> & in, std::set<std::string> & data, int state) {
        switch (state) {
            case 0: {
                // load the string and add it to the passed set
                std::string str;

                ::loaders::loader::v6::dataLoader<
                    std::string,
                    char,
                    StringReader,
                    1,
                    ::checkers::is_character<char, '"'>,
                    ::checkers::is_character<char, '"'>,
                    ::checkers::is_space_or<','>
                > StringLoader(str);
                in >> StringLoader;

                // add the populated string to the passed set
                data.insert(str);
                break;
            }
            default:
                throw std::runtime_error("INVALID STATE");
        } // switch (state)

        return in;
    }
};

struct CombinedReader {
    std::basic_istream<char> & operator()(std::basic_istream<char> & in, LongestCommonSubsequenceTwoData & data, int state) {
        // std::cout << "Processing state = " << state << "\n";
        switch (state) {
            case 0: {
                // Read the X string
                ::loaders::loader::v6::dataLoader<
                    std::string,
                    char,
                    StringReader,
                    1,
                    ::checkers::is_character<char, '"'>,
                    ::checkers::is_character<char, '"'>,
                    ::checkers::is_space_or<','>
                > XLoader(data.m_x);
                in >> XLoader;
                // std::cout << "Populated the x = " << data.m_x << "\n";
                break;
            }
            case 1: {
                // Read the Y string
                ::loaders::loader::v6::dataLoader<
                    std::string,
                    char,
                    StringReader,
                    1,
                    ::checkers::is_character<char, '"'>,
                    ::checkers::is_character<char, '"'>,
                    ::checkers::is_space_or<','>
                > YLoader(data.m_y);
                in >> YLoader;
                // std::cout << "Populated the y = " << data.m_y << "\n";
                break;
            }
            case 2: {
                // Read the expected set of valid results
                ::loaders::loader::v6::dataLoader<
                    std::set<std::string>,
                    char,
                    SetLCSReader,
                    1,
                    ::checkers::is_character<char, '{'>,
                    ::checkers::is_character<char, '}'>,
                    ::checkers::is_space_or<','>
                > VectorLoader(data.m_expected);
                // std::cout << "Populating set\n";
                in >> VectorLoader;
                // std::cout << "Populated set\n";
                // for (auto & str : data.m_expected) {
                //     std::cout << str << "\n";
                // } // for (auto & str : data.m_expected)
                break;
            }
            default:
                throw std::runtime_error("INVALID STATE");
        } // switch (state)

        return in;
    }
};

std::istream& operator>>(std::istream& in, LongestCommonSubsequenceTwoData &data) {
    ::loaders::loader::v6::dataLoader<
        LongestCommonSubsequenceTwoData,
        char,
        CombinedReader,
        3,
        ::checkers::is_character<char, '{'>,
        ::checkers::is_character<char, '}'>,
        ::checkers::is_space_or<','>
    > DataLoader(data);
    in >> DataLoader;

    return in;
}

// Test Fixture Class
class LongestCommonSubsequenceTwoFixture :
    public testing::TestWithParam<LongestCommonSubsequenceTwoData> {
};

// Parameterized Test Definition
TEST_P(LongestCommonSubsequenceTwoFixture, LongestCommonSubsequenceTwoTests) {
    LongestCommonSubsequenceTwoData data = GetParam();

    Solution solution;

    EXPECT_THAT(data.get_expected(), ::testing::Contains(solution.findLCS(data.get_x(), data.get_y())));
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(LongestCommonSubsequenceTwoTests, LongestCommonSubsequenceTwoFixture, testing::ValuesIn(
    Loader<LongestCommonSubsequenceTwoData>()(find_path("dynamic_programming/data/longest_common_subsequence_two.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
