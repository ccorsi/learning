/**
 * @file submatrix_sumtests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains tests to the problem https://www.techiedelight.com/?problem=SubmatrixSum
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
#include "submatrix_sum.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::utils;
using namespace valhalla::matrices::submatrix_sum;

// Test Fixture Data Class
class SubmatrixSumData {
    std::vector<std::vector<int>> m_input;
    int m_p, m_q, m_r, m_s, m_expected;
public:
    SubmatrixSumData() = default;

    std::vector<std::vector<int>> const & get_input() { return m_input; }
    int get_p() { return m_p; }
    int get_q() { return m_q; }
    int get_r() { return m_r; }
    int get_s() { return m_s; }
    int get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const SubmatrixSumData &);
    friend std::istream& operator>>(std::istream&, SubmatrixSumData &);

};

std::ostream& operator<<(std::ostream& out, const SubmatrixSumData & data) {
    out << "SubmatrixSumData [ input=[";
    for (std::vector<int> values : data.m_input) {
        out << " [";
        for (int value : values) {
            out << " " << value;
        } // for
        out << " ]";
    } // for
    return out << " ] p=" << data.m_p << " q=" << data.m_q << " r=" << data.m_r << " s=" << data.m_s
        << " expected=" << data.m_expected << " ]";
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

std::istream& operator>>(std::istream& in, SubmatrixSumData &data) {
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
    > pLoader(data.m_p);
    in >> pLoader;

    ::loaders::loader::v4::dataLoader<
        int,
        char,
        loader::v4::reader<int,char>,
        1,
        ::checkers::is_character_noop<char>,
        ::checkers::is_no_character<char>,
        ::checkers::is_space_or<','>
    > qLoader(data.m_q);
    in >> qLoader;

    ::loaders::loader::v4::dataLoader<
        int,
        char,
        loader::v4::reader<int,char>,
        1,
        ::checkers::is_character_noop<char>,
        ::checkers::is_no_character<char>,
        ::checkers::is_space_or<','>
    > rLoader(data.m_r);
    in >> rLoader;

    ::loaders::loader::v4::dataLoader<
        int,
        char,
        loader::v4::reader<int,char>,
        1,
        ::checkers::is_character_noop<char>,
        ::checkers::is_no_character<char>,
        ::checkers::is_space_or<','>
    > sLoader(data.m_s);
    in >> sLoader;

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
class SubmatrixSumFixture :
    public testing::TestWithParam<SubmatrixSumData> {
};

// Parameterized Test Definition
TEST_P(SubmatrixSumFixture, SubmatrixSumTests) {
    SubmatrixSumData data = GetParam();

    Solution solution;

    int actual = solution.findSubmatrixSum(data.get_input(), data.get_p(), data.get_q(), data.get_r(), data.get_s());

    ASSERT_EQ(actual, data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(SubmatrixSumTests, SubmatrixSumFixture, testing::ValuesIn(
    Loader<SubmatrixSumData>()(find_path("matrices/data/submatrix_sum.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
