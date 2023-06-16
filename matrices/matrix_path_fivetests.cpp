/**
 * @file matrix_path_fivetests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains tests to the problem https://www.techiedelight.com/?problem=MatrixPathV
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
#include "matrix_path_five.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::utils;
using namespace valhalla::matrices::matrix_path_five;

// Test Fixture Data Class
class MatrixPathFiveData {
    int m_m, m_n, m_k, m_expected;
public:
    MatrixPathFiveData() = default;

    int get_expected() { return m_expected; }
    int get_m() { return m_m; }
    int get_n() { return m_n; }
    int get_k() { return m_k; }

    friend std::ostream& operator<<(std::ostream&, const MatrixPathFiveData &);
    friend std::istream& operator>>(std::istream&, MatrixPathFiveData &);

};

std::ostream& operator<<(std::ostream& out, const MatrixPathFiveData & data) {
    return out << "MatrixPathFiveData [ M=" << data.m_m << " N=" << data.m_n << " k="
        << data.m_k << " expected=" << data.m_expected << " ]";
}

std::istream& operator>>(std::istream& in, MatrixPathFiveData &data) {
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
class MatrixPathFiveFixture :
    public testing::TestWithParam<MatrixPathFiveData> {
};

// Parameterized Test Definition
TEST_P(MatrixPathFiveFixture, MatrixPathFiveTests) {
    MatrixPathFiveData data = GetParam();

    Solution solution;

    int actual = solution.findTotalWays(data.get_m(), data.get_n(), data.get_k());

    ASSERT_EQ(actual, data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(MatrixPathFiveTests, MatrixPathFiveFixture, testing::ValuesIn(
    Loader<MatrixPathFiveData>()(find_path("matrices/data/matrix_path_five.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
