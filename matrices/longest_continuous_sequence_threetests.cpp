/**
 * @file longest_continuous_sequence_threetests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains tests to the problem https://www.techiedelight.com/?problem=LongestContinuousSequenceIII
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
#include "longest_continuous_sequence_three.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::utils;
using namespace valhalla::matrices::longest_continuous_sequence_three;

// Test Fixture Data Class
class LongestContinuousSequenceThreeData {
    std::vector<std::vector<char>> m_input;
    char m_ch;
    int m_expected;
public:
    LongestContinuousSequenceThreeData() = default;

    std::vector<std::vector<char>> const & get_input() { return m_input; }
    char get_ch() { return m_ch; }
    int get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const LongestContinuousSequenceThreeData &);
    friend std::istream& operator>>(std::istream&, LongestContinuousSequenceThreeData &);

};

std::ostream& operator<<(std::ostream& out, const LongestContinuousSequenceThreeData & data) {
    out << "LongestContinuousSequenceThreeData [ input[";
    for (std::vector<char> values : data.m_input) {
        out << " [";
        for (char value : values) {
            out << " '" << value << "'";
        } // for
        out << " ]";
    } // for
    return out << " ] ch='" <<  data.m_ch << "' expected=" << data.m_expected << " ]";
}

struct VectorReader {
    std::basic_istream<char> & operator()(std::basic_istream<char> & in, std::vector<char> & vec, int state) {
        char entry;

        ::loaders::loader::v4::dataLoader<
            char,
            char,
            loader::v4::reader<char,char>,
            1,
            ::checkers::is_character<char,'\''>,
            ::checkers::is_character<char,'\''>,
            ::checkers::is_space_or<','>
        > entryLoader(entry);
        in >> entryLoader;

        vec.push_back(entry);

        return in;
    }
};

struct VectorVectorReader {
    std::basic_istream<char> & operator()(std::basic_istream<char> & in, std::vector<std::vector<char>> & vecvec, int state) {
        std::vector<char> entry;

        ::loaders::loader::v4::dataLoader<
            std::vector<char>,
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

std::istream& operator>>(std::istream& in, LongestContinuousSequenceThreeData &data) {
    ::loaders::loader::v4::dataLoader<
        std::vector<std::vector<char>>,
        char,
        VectorVectorReader,
        1,
        ::checkers::is_character<char,'['>,
        ::checkers::is_character<char,']'>,
        ::checkers::is_space_or<','>
    > inputLoader(data.m_input);
    in >> inputLoader;

    ::loaders::loader::v4::dataLoader<
        char,
        char,
        loader::v4::reader<char,char>,
        1,
        ::checkers::is_character<char,'\''>,
        ::checkers::is_character<char,'\''>,
        ::checkers::is_space_or<','>
    > charLoader(data.m_ch);
    in >> charLoader;

    ::loaders::loader::v4::dataLoader<
        int,
        char,
        loader::v4::reader<int,char>,
        1,
        ::checkers::is_character_noop<char>,
        ::checkers::is_no_character<char>,
        ::checkers::is_space_or<','>
    > expectedLoader(data.m_expected);
    in >> expectedLoader;

    return in;
}

// Test Fixture Class
class LongestContinuousSequenceThreeFixture :
    public testing::TestWithParam<LongestContinuousSequenceThreeData> {
};

// Parameterized Test Definition
TEST_P(LongestContinuousSequenceThreeFixture, LongestContinuousSequenceThreeTests) {
    LongestContinuousSequenceThreeData data = GetParam();

    Solution solution;

    int actual = solution.findMaxLength(data.get_input(), data.get_ch());

    ASSERT_EQ(actual, data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(LongestContinuousSequenceThreeTests, LongestContinuousSequenceThreeFixture, testing::ValuesIn(
    Loader<LongestContinuousSequenceThreeData>()(find_path("matrices/data/longest_continuous_sequence_three.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
