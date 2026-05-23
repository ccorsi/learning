/**
 * @file longest_common_subsequencetests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains the tests to the problem https://www.techiedelight.com/?problem=LongestCommonSubsequence
 * @version 0.1
 * @date 2026-05-03
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
#include "longest_common_subsequence.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::utils::readers;
using namespace valhalla::utils;
using namespace valhalla::dynamic_programming::longest_common_subsequence;

// Test Fixture Data Class
class LongestCommonSubsequenceData {
    std::string m_X, m_Y;
    int m_expected;
public:
    LongestCommonSubsequenceData() = default;

    inline std::string get_X() { return m_X; }
    inline std::string get_Y() { return m_Y; }
    inline int get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const LongestCommonSubsequenceData &);
    friend std::istream& operator>>(std::istream&, LongestCommonSubsequenceData &);

    friend struct LongestCommonSubsequenceDataReader;
};

struct LongestCommonSubsequenceDataReader {
    std::basic_istream<char> & operator()(std::basic_istream<char> & in, LongestCommonSubsequenceData & data, int state) {
        switch (state) {
            case 0: {
                ::loaders::loader::v6::dataLoader<
                    std::string,
                    char,
                    StringReader,
                    1,
                    ::checkers::is_character<char, '"'>,
                    ::checkers::is_character<char, '"'>,
                    ::checkers::is_space_or<','>,
                    ::checkers::is_space_noop<char>
                > StringLoader(data.m_X);
                in >> StringLoader;
                break;
            }
            case 1: {
                ::loaders::loader::v6::dataLoader<
                    std::string,
                    char,
                    StringReader,
                    1,
                    ::checkers::is_character<char, '"'>,
                    ::checkers::is_character<char, '"'>,
                    ::checkers::is_space_or<','>,
                    ::checkers::is_space_noop<char>
                > StringLoader(data.m_Y);
                in >> StringLoader;
                break;
            }
            case 2:
                in >> data.m_expected;
                break;
            default:
                throw std::runtime_error("INVALID STATE");
        } // switch (state)

        return in;
    }
};

std::ostream& operator<<(std::ostream& out, const LongestCommonSubsequenceData & data) {
    out << "LongestCommonSubsequenceData [ X=" << data.m_X << " Y=" << data.m_Y;
    out << " expected=" << data.m_expected << " ]";

    return out;
}

std::istream& operator>>(std::istream& in, LongestCommonSubsequenceData &data) {
    ::loaders::loader::v6::dataLoader<
        LongestCommonSubsequenceData,
        char,
        LongestCommonSubsequenceDataReader,
        3,
        ::checkers::is_character<char, '{'>,
        ::checkers::is_character<char, '}'>,
        ::checkers::is_space_or<','>
    > DataLoader(data);
    in >> DataLoader;

    return in;
}

// Test Fixture Class
class LongestCommonSubsequenceFixture :
    public testing::TestWithParam<LongestCommonSubsequenceData> {
};

// Parameterized Test Definition
TEST_P(LongestCommonSubsequenceFixture, LongestCommonSubsequenceTests) {
    LongestCommonSubsequenceData data = GetParam();

    Solution solution;

    ASSERT_EQ(solution.findLCSLength(data.get_X(), data.get_Y()), data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(LongestCommonSubsequenceTests, LongestCommonSubsequenceFixture, testing::ValuesIn(
    Loader<LongestCommonSubsequenceData>()(find_path("dynamic_programming/data/longest_common_subsequence.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
