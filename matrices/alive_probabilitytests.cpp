/**
 * @file alive_probabilitytests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains tests to the problem https://www.techiedelight.com/?problem=AliveProbability
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
#include "alive_probability.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::utils;
using namespace valhalla::matrices::alive_probability;

// Test Fixture Data Class
class AliveProbabilityData {
    int m_N, m_n, m_x, m_y;
    double m_expected;
public:
    AliveProbabilityData() = default;

    int get_N() { return m_N; }
    int get_n() { return m_n; }
    int get_x() { return m_x; }
    int get_y() { return m_y; }
    double get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const AliveProbabilityData &);
    friend std::istream& operator>>(std::istream&, AliveProbabilityData &);

};

std::ostream& operator<<(std::ostream& out, const AliveProbabilityData & data) {
    return out << "AliveProbabilityData [ N=" << data.m_N << " n=" << data.m_n << " x="
        << data.m_x << " y=" << data.m_y << " expected=" << data.m_expected
        << " ]";
}

std::istream& operator>>(std::istream& in, AliveProbabilityData &data) {
    ::loaders::loader::v4::dataLoader<
        int,
        char,
        loader::v4::reader<int,char>,
        1,
        ::checkers::is_character_noop<char>,
        ::checkers::is_no_character<char>,
        ::checkers::is_space_or<','>
    > NLoader(data.m_N);
    in >> NLoader;

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
    > xLoader(data.m_x);
    in >> xLoader;

    ::loaders::loader::v4::dataLoader<
        int,
        char,
        loader::v4::reader<int,char>,
        1,
        ::checkers::is_character_noop<char>,
        ::checkers::is_no_character<char>,
        ::checkers::is_space_or<','>
    > yLoader(data.m_y);
    in >> yLoader;

    ::loaders::loader::v4::dataLoader<
        double,
        char,
        loader::v4::reader<double,char>,
        1,
        ::checkers::is_character_noop<char>,
        ::checkers::is_no_character<char>,
        ::checkers::is_space_or<','>
    > expectedLoader(data.m_expected);
    in >> expectedLoader;

    return in;
}

// Test Fixture Class
class AliveProbabilityFixture :
    public testing::TestWithParam<AliveProbabilityData> {
};

// Parameterized Test Definition
TEST_P(AliveProbabilityFixture, AliveProbabilityTests) {
    AliveProbabilityData data = GetParam();

    Solution solution;

    double actual = solution.findProbability(data.get_N(), data.get_n(), data.get_x(), data.get_y());

    ASSERT_DOUBLE_EQ(actual, data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(AliveProbabilityTests, AliveProbabilityFixture, testing::ValuesIn(
    Loader<AliveProbabilityData>()(find_path("matrices/data/alive_probability.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
