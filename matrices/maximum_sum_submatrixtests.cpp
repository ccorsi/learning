/**
 * @file maximum_sub_submatrixtests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains tests to the problem https://www.techiedelight.com/?problem=MaximumSumSubmatrix
 * @version 0.1
 * @date 2023-06-20
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
#include "maximum_sum_submatrix.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::utils;
using namespace valhalla::matrices::maximum_sum_submatrix;

// Test Fixture Data Class
class MaximumSumSubmatrixData {
    std::vector<std::vector<int>> m_input;
    int m_k;
    std::vector<std::vector<int>> m_expected;
public:
    MaximumSumSubmatrixData() = default;

    std::vector<std::vector<int>> const & get_input() { return m_input; }
    int get_k() { return m_k; }
    std::vector<std::vector<int>> const & get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const MaximumSumSubmatrixData &);
    friend std::istream& operator>>(std::istream&, MaximumSumSubmatrixData &);

};

std::ostream& operator<<(std::ostream& out, const MaximumSumSubmatrixData & data) {
    out << "MaximumSumSubmatrixData [ input=[";
    for (std::vector<int> values : data.m_input) {
        out << " [";
        for (int value : values) {
            out << " " << value;
        } // for
        out << " ]";
    } // for
    out << " ] k=" << data.m_k << " expected=[";
    for (std::vector<int> values : data.m_expected) {
        out << " [";
        for (int value : values) {
            out << " " << value;
        } // for
        out << " ]";
    } // for
    return out << " ] ]";
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

std::istream& operator>>(std::istream& in, MaximumSumSubmatrixData &data) {
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
    > kLoader(data.m_k);
    in >> kLoader;

    ::loaders::loader::v4::dataLoader<
        std::vector<std::vector<int>>,
        char,
        VectorVectorReader,
        1,
        ::checkers::is_character<char,'['>,
        ::checkers::is_character<char,']'>,
        ::checkers::is_space_or<','>
    > expectedLoader(data.m_expected);
    in >> expectedLoader;

    return in;
}

// Test Fixture Class
class MaximumSumSubmatrixFixture :
    public testing::TestWithParam<MaximumSumSubmatrixData> {
};

// Parameterized Test Definition
TEST_P(MaximumSumSubmatrixFixture, MaximumSumSubmatrixTests) {
    MaximumSumSubmatrixData data = GetParam();

    Solution solution;

    std::vector<std::vector<int>> actual = solution.findMaxSumSubmatrix(data.get_input(), data.get_k());

    ASSERT_EQ(actual, data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(MaximumSumSubmatrixTests, MaximumSumSubmatrixFixture, testing::ValuesIn(
    Loader<MaximumSumSubmatrixData>()(find_path("matrices/data/maximum_sum_submatrix.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
