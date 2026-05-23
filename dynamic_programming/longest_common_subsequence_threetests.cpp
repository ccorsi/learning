/**
 * @file longest_common_subsequence_threetests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains tests for the problem https://www.techiedelight.com/?problem=LongestCommonSubsequenceIII
 * @version 0.1
 * @date 2026-05-21
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
#include "longest_common_subsequence_three.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::utils::readers;
using namespace valhalla::utils;
using namespace valhalla::dynamic_programming::longest_common_subsequence_three;

// Test Fixture Data Class
class LongestCommonSubsequenceThreeData {
    std::string m_x, m_y, m_z;
    int m_expected;
public:
    LongestCommonSubsequenceThreeData() = default;

    std::string get_x() { return m_x; }
    std::string get_y() { return m_y; }
    std::string get_z() { return m_z; }
    int get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const LongestCommonSubsequenceThreeData &);
    friend std::istream& operator>>(std::istream&, LongestCommonSubsequenceThreeData &);

    friend struct CombinedReader;
};

std::ostream& operator<<(std::ostream& out, const LongestCommonSubsequenceThreeData & data) {
    out << "LongestCommonSubsequenceThreeData [ X=\"" << data.m_x << "\" Y=\"" << data.m_y;
    out << "\" Z=\"" << data.m_z << "\" expected=" << data.m_expected << " ]";

    return out;
}

void populate_string(std::basic_istream<char> & in, std::string & str) {
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
} // void populate_string(std::basic_istream & in, std::string & str)

struct CombinedReader {
    std::basic_istream<char> & operator()(std::basic_istream<char> & in, LongestCommonSubsequenceThreeData & data, int state) {
        switch (state) {
            case 0: {
                // populate X
                populate_string(in, data.m_x);
                break;
            }
            case 1: {
                // populate Y
                populate_string(in, data.m_y);
                break;
            }
            case 2: {
                // populate Z
                populate_string(in, data.m_z);
                break;
            }
            case 3: {
                // populate expected
                in >> data.m_expected;
                break;
            }
            default:
                throw std::runtime_error("INVALID STATE");
        } // switch (state)

        return in;
    }
};

std::istream& operator>>(std::istream& in, LongestCommonSubsequenceThreeData &data) {
    ::loaders::loader::v6::dataLoader<
        LongestCommonSubsequenceThreeData,
        char,
        CombinedReader,
        4,
        ::checkers::is_character<char, '{'>,
        ::checkers::is_character<char, '}'>,
        ::checkers::is_space_or<','>
    > DataLoader(data);
    in >> DataLoader;

    return in;
}

// Test Fixture Class
class LongestCommonSubsequenceThreeFixture :
    public testing::TestWithParam<LongestCommonSubsequenceThreeData> {
};

// Parameterized Test Definition
TEST_P(LongestCommonSubsequenceThreeFixture, LongestCommonSubsequenceThreeTests) {
    LongestCommonSubsequenceThreeData data = GetParam();

    Solution solution;

    ASSERT_EQ(solution.findLCS(data.get_x(), data.get_y(), data.get_z()), data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(LongestCommonSubsequenceThreeTests, LongestCommonSubsequenceThreeFixture, testing::ValuesIn(
    Loader<LongestCommonSubsequenceThreeData>()(find_path("dynamic_programming/data/longest_common_subsequence_three.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
