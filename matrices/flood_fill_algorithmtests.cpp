/**
 * @file flood_fill_algorithmtests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains tests to the problem https://www.techiedelight.com/?problem=FloodFillAlgorithm
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
#include "flood_fill_algorithm.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::utils;
using namespace valhalla::matrices::flood_fill_algorithm;

// Test Fixture Data Class
class FloodFillAlgorithmData {
    std::vector<std::vector<char>> m_input, m_expected;
    int m_x, m_y;
    char m_replacement;
public:
    FloodFillAlgorithmData() = default;

    std::vector<std::vector<char>> const & get_input() { return m_input; }
    std::vector<std::vector<char>> const & get_expected() { return m_expected; }
    int get_x() { return m_x; }
    int get_y() { return m_y; }
    char get_replacement() { return m_replacement; }

    friend std::ostream& operator<<(std::ostream&, const FloodFillAlgorithmData &);
    friend std::istream& operator>>(std::istream&, FloodFillAlgorithmData &);

};

std::ostream& operator<<(std::ostream& out, const FloodFillAlgorithmData & data) {
    out << "FloodFillAlgorithmData [ input=[";
    for (std::vector<char> values : data.m_input) {
        out << " [";
        for (char value : values) {
            out << " '" << value << "'";
        } // for
        out << " ]";
    } // for
    out << " ] x=" << data.m_x << " y=" << data.m_y << " replacement='" << data.m_replacement << "' expected=[";
    for (std::vector<char> values : data.m_expected) {
        out << " [";
        for (char value : values) {
            out << " '" << value << "'";
        } // for
        out << " ]";
    } // for
    return out << " ] ]";
}

struct VectorReader {
    std::basic_istream<char> & operator()(std::basic_istream<char> & in, std::vector<char> & vec, int state) {
        char entry;

        ::loaders::loader::v4::dataLoader<
            char,
            char,
            loader::v4::reader<char,char>,
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

std::istream& operator>>(std::istream& in, FloodFillAlgorithmData &data) {
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
        char,
        char,
        loader::v4::reader<char,char>,
        1,
        ::checkers::is_character_noop<char>,
        ::checkers::is_no_character<char>,
        ::checkers::is_space_or<','>
    > replacementLoader(data.m_replacement);
    in >> replacementLoader;

    ::loaders::loader::v4::dataLoader<
        std::vector<std::vector<char>>,
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
class FloodFillAlgorithmFixture :
    public testing::TestWithParam<FloodFillAlgorithmData> {
};

// Parameterized Test Definition
TEST_P(FloodFillAlgorithmFixture, FloodFillAlgorithmTests) {
    FloodFillAlgorithmData data = GetParam();

    Solution solution;

    std::vector<std::vector<char>> actual = data.get_input();

    solution.floodfill(actual, data.get_x(), data.get_y(), data.get_replacement());

    ASSERT_EQ(actual, data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(FloodFillAlgorithmTests, FloodFillAlgorithmFixture, testing::ValuesIn(
    Loader<FloodFillAlgorithmData>()(find_path("matrices/data/flood_fill_algorithm.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
