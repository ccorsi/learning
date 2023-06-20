/**
 * @file largest_plustests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains tests to the problem https://www.techiedelight.com/?problem=LargestPlus
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
#include "largest_plus.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::utils;
using namespace valhalla::matrices::largest_plus;

// Test Fixture Data Class
class LargestPlusData {
    std::vector<std::vector<int>> m_input;
    int m_expected;
public:
    LargestPlusData() = default;

    std::vector<std::vector<int>> const & get_input() { return m_input; }
    int get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const LargestPlusData &);
    friend std::istream& operator>>(std::istream&, LargestPlusData &);

};

std::ostream& operator<<(std::ostream& out, const LargestPlusData & data) {
    out << "LargestPlusData [ input=[";
    for (std::vector<int> values : data.m_input) {
        out << " [";
        for (int value : values) {
            out << " " << value;
        } // for
        out << " ]";
    } // for
    return out << " ]" << " ] expected=" << data.m_expected << " ]";
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

std::istream& operator>>(std::istream& in, LargestPlusData &data) {
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
class LargestPlusFixture :
    public testing::TestWithParam<LargestPlusData> {
};

// Parameterized Test Definition
TEST_P(LargestPlusFixture, LargestPlusTests) {
    LargestPlusData data = GetParam();

    Solution solution;

    int actual = solution.findLargestPlus(data.get_input());

    ASSERT_EQ(actual, data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(LargestPlusTests, LargestPlusFixture, testing::ValuesIn(
    Loader<LargestPlusData>()(find_path("matrices/data/largest_plus.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
