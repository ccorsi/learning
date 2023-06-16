/**
 * @file matrix_path_sixtests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains tests to the problem https://www.techiedelight.com/?problem=MatrixPathVI
 * @version 0.1
 * @date 2023-06-16
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
#include "matrix_path_six.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::utils;
using namespace valhalla::matrices::matrix_path_six;

// Test Fixture Data Class
class MatrixPathSixData {
    int m_m, m_n;
    long m_expected;
public:
    MatrixPathSixData() = default;

    int get_m() { return m_m; }
    int get_n() { return m_n; }
    long get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const MatrixPathSixData &);
    friend std::istream& operator>>(std::istream&, MatrixPathSixData &);

};

std::ostream& operator<<(std::ostream& out, const MatrixPathSixData & data) {
    return out << "MatrixPathSixData [ m=" << data.m_m << " n=" << data.m_n
        << " expected=" << data.m_expected << " ]";
}

std::istream& operator>>(std::istream& in, MatrixPathSixData &data) {
    ::loaders::loader::v4::dataLoader<
        int,
        char,
        loader::v4::reader<int,char>,
        1,
        ::checkers::is_character_noop<char>,
        ::checkers::is_no_character<char>,
        ::checkers::is_space_or<','>
    > mLoader(data.m_m);
    in >> mLoader;

    ::loaders::loader::v4::dataLoader<
        int,
        char,
        loader::v4::reader<int,char>,
        1,
        ::checkers::is_character_noop<char>,
        ::checkers::is_no_character<char>,
        ::checkers::is_space_or<','>
    > nLoader(data.m_n);
    in >> nLoader;

    ::loaders::loader::v4::dataLoader<
        long,
        char,
        loader::v4::reader<long,char>,
        1,
        ::checkers::is_character_noop<char>,
        ::checkers::is_no_character<char>,
        ::checkers::is_space_or<','>
    > expectedLoader(data.m_expected);
    in >> expectedLoader;

    return in;
}

// Test Fixture Class
class MatrixPathSixFixture :
    public testing::TestWithParam<MatrixPathSixData> {
};

// Parameterized Test Definition
TEST_P(MatrixPathSixFixture, MatrixPathSixTests) {
    MatrixPathSixData data = GetParam();

    Solution solution;

    long actual = solution.countPaths(data.get_m(), data.get_n());

    ASSERT_EQ(actual, data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(MatrixPathSixTests, MatrixPathSixFixture, testing::ValuesIn(
    Loader<MatrixPathSixData>()(find_path("matrices/data/matrix_path_six.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
