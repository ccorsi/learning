/**
 * @file longest_continuous_sequence_twotests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains tests to the problem https://www.techiedelight.com/?problem=LongestContinuousSequenceII
 * @version 0.1
 * @date 2023-06-19
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
#include "longest_continuous_sequence_two.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::utils;
using namespace valhalla::matrices::longest_continuous_sequence_two;

// Test Fixture Data Class
class LongestContinuousSequenceTwoData {
    std::vector<std::vector<int>> m_input;
    std::vector<int> m_expected;
public:
    LongestContinuousSequenceTwoData() = default;

    std::vector<std::vector<int>> const & get_input() { return m_input; }
    std::vector<int> const & get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const LongestContinuousSequenceTwoData &);
    friend std::istream& operator>>(std::istream&, LongestContinuousSequenceTwoData &);

};

std::ostream& operator<<(std::ostream& out, const LongestContinuousSequenceTwoData & data) {
    out << "LongestContinuousSequenceTwoData [ input=[";
    for (std::vector<int> values : data.m_input) {
        out << " [";
        for (int value : values) {
            out << " " << value;
        } // for
        out << " ]";
    } // for
    out << " ] expected=[";
    for (int value : data.m_expected) {
        out << " " << value;
    } // for
    out << " ] ]";

    return out;
}

struct VectorReader {
    std::basic_istream<char> & operator()(std::basic_istream<char> & in, std::vector<int> & vec, int state) {
        int entry;

        ::loaders::loader::v4::dataLoader<
            int,
            char,
            loader::v4::reader<int,char>,
            1,
            ::checkers::is_character_noop<char>,
            ::checkers::is_no_character<char>,
            ::checkers::is_space_or<','>
        > entryLoader(entry);
        in >> entryLoader;

        vec.push_back(entry);

        return in;
    }
};

struct VectorVectorReader {
    std::basic_istream<char> & operator()(std::basic_istream<char> & in, std::vector<std::vector<int>> & vecvec, int state) {
        std::vector<int> entry;

        ::loaders::loader::v4::dataLoader<
            std::vector<int>,
            char,
            VectorReader,
            1,
            ::checkers::is_character<char,'['>,
            ::checkers::is_character<char,']'>,
            ::checkers::is_space_or<','>
        > entryLoader(entry);
        in >> entryLoader;

        vecvec.push_back(entry);

        return in;
    }
};

std::istream& operator>>(std::istream& in, LongestContinuousSequenceTwoData &data) {
    ::loaders::loader::v4::dataLoader<
        std::vector<std::vector<int>>,
        char,
        VectorVectorReader,
        1,
        ::checkers::is_character<char,'['>,
        ::checkers::is_character<char,']'>,
        ::checkers::is_space_or<','>
    > inputLoader(data.m_input);
    in >> inputLoader;

    ::loaders::loader::v4::dataLoader<
        std::vector<int>,
        char,
        VectorReader,
        1,
        ::checkers::is_character<char,'['>,
        ::checkers::is_character<char,']'>,
        ::checkers::is_space_or<','>
    > expectedLoader(data.m_expected);
    in >> expectedLoader;

    return in;
}

// Test Fixture Class
class LongestContinuousSequenceTwoFixture :
    public testing::TestWithParam<LongestContinuousSequenceTwoData> {
};

// Parameterized Test Definition
TEST_P(LongestContinuousSequenceTwoFixture, LongestContinuousSequenceTwoTests) {
    LongestContinuousSequenceTwoData data = GetParam();

    Solution solution;

    std::vector<int> actual = solution.findLongestPath(data.get_input());

    ASSERT_EQ(actual, data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(LongestContinuousSequenceTwoTests, LongestContinuousSequenceTwoFixture, testing::ValuesIn(
    Loader<LongestContinuousSequenceTwoData>()(find_path("matrices/data/longest_continuous_sequence_two.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
