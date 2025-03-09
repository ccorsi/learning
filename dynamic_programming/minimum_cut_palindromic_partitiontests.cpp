/**
 * @file minimum_cut_palindromic_partitiontests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains tests to the problem https://www.techiedelight.com/?problem=MinimumCutPalindromicPartition
 * @version 0.1
 * @date 2025-02-23
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
#include "minimum_cut_palindromic_partition.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::utils::readers;
using namespace valhalla::utils;
using namespace valhalla::dynamic_programming::minimum_cut_palindromic_partition;

// Test Fixture Data Class
class MinimumCutPalindromicPartitionData {
    std::string m_input;
    int m_expected;
public:
    MinimumCutPalindromicPartitionData() = default;

    std::string get_input() { return m_input; }
    int get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const MinimumCutPalindromicPartitionData &);
    friend std::istream& operator>>(std::istream&, MinimumCutPalindromicPartitionData &);

    friend struct CombinedReader;
};

std::ostream& operator<<(std::ostream& out, const MinimumCutPalindromicPartitionData & data) {
    out << "MinimumCutPalindromicPartitionData [ s=\"" << data.m_input << "\", expected=" << data.m_expected;
    out << " ]";

    return out;
}

struct CombinedReader {
    std::basic_istream<char> & operator()(std::basic_istream<char> & in, MinimumCutPalindromicPartitionData & data, int state) {
        switch (state) {
            case 0:
            {
                ::loaders::loader::v6::dataLoader<
                    std::string,
                    char,
                    StringReader,
                    1,
                    ::checkers::is_character<char, '"'>,
                    ::checkers::is_character<char, '"'>,
                    ::checkers::is_space_or<','>,
                    ::checkers::is_space_noop<char>
                > InputLoader(data.m_input);
                in >> InputLoader;
            }
            break;
            case 1:
                in >> data.m_expected;
            break;
            default:
                throw std::runtime_error("INVALID STATE PASSED");
        } // switch (state)

        return in;
    }
};

std::istream& operator>>(std::istream& in, MinimumCutPalindromicPartitionData &data) {
    ::loaders::loader::v6::dataLoader<
        MinimumCutPalindromicPartitionData,
        char,
        CombinedReader,
        2,
        ::checkers::is_character_noop<char>,
        ::checkers::is_no_character<char>,
        ::checkers::is_space_or<','>
    > CombinedLoader(data);
    return in >> CombinedLoader;
}

// Test Fixture Class
class MinimumCutPalindromicPartitionFixture :
    public testing::TestWithParam<MinimumCutPalindromicPartitionData> {
};

// Parameterized Test Definition
TEST_P(MinimumCutPalindromicPartitionFixture, MinimumCutPalindromicPartitionTests) {
    MinimumCutPalindromicPartitionData data = GetParam();

    Solution solution;

    ASSERT_EQ(solution.findMinimumCuts(data.get_input()), data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(MinimumCutPalindromicPartitionTests, MinimumCutPalindromicPartitionFixture, testing::ValuesIn(
    Loader<MinimumCutPalindromicPartitionData>()(find_path("dynamic_programming/data/minimum_cut_palindromic_partition.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
