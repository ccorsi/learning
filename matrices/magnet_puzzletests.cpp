/**
 * @file magnet_puzzletests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains tests to the problem https://www.techiedelight.com/?problem=MagnetPuzzle
 * @version 0.1
 * @date 2023-06-22
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
#include "magnet_puzzle.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::utils;
using namespace valhalla::matrices::magnet_puzzle;

// Test Fixture Data Class
class MagnetPuzzleData {
    std::vector<std::vector<char>> m_rules, m_expected;
    std::vector<int> m_top, m_bottom, m_left, m_right;
public:
    MagnetPuzzleData() = default;

    std::vector<std::vector<char>> const & get_rules() { return m_rules; }
    std::vector<int> const & get_top() { return m_top; }
    std::vector<int> const & get_bottom() { return m_bottom; }
    std::vector<int> const & get_left() { return m_left; }
    std::vector<int> const & get_right() { return m_right; }
    std::vector<std::vector<char>> const & get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const MagnetPuzzleData &);
    friend std::istream& operator>>(std::istream&, MagnetPuzzleData &);

};

std::ostream& operator<<(std::ostream& out, const MagnetPuzzleData & data) {
    out << "MagnetPuzzleData [ rules=[";
    for (std::vector<char> values : data.m_rules) {
        out << " [";
        for (char value : values) {
            out << " '" << value << "'";
        } // for
        out << " ]";
    } // for
    out << " ] top=[";
    for (int value : data.m_top) {
        out << " " << value;
    } // for
    out << " ] bottom=[";
    for (int value : data.m_bottom) {
        out << " " << value;
    } // for
    out << " ] left=[";
    for (int value : data.m_left) {
        out << " " << value;
    } // for
    out << " ] right=[";
    for (int value : data.m_right) {
        out << " " << value;
    } // for
    out << " ] expected=[";
    for (std::vector<char> values : data.m_expected) {
        out << " [";
        for (char value : values) {
            out << " '" << value << "'";
        } // for
        out << " ]";
    } // for
    return out << " ] ]";
}

template<typename Type>
struct VectorReader {
    std::basic_istream<char> & operator()(std::basic_istream<char> & in, std::vector<Type> & vec, int state) {
        Type entry;

        ::loaders::loader::v4::dataLoader<
            Type,
            char,
            loader::v4::reader<Type,char>,
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
            VectorReader<char>,
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

std::istream& operator>>(std::istream& in, MagnetPuzzleData &data) {
    ::loaders::loader::v4::dataLoader<
        std::vector<std::vector<char>>,
        char,
        VectorVectorReader,
        1,
        ::checkers::is_character<char,'['>,
        ::checkers::is_character<char,']'>,
        ::checkers::is_space_or<','>
    > rulesLoader(data.m_rules);
    in >> rulesLoader;

    ::loaders::loader::v4::dataLoader<
        std::vector<int>,
        char,
        VectorReader<int>,
        1,
        ::checkers::is_character<char,'['>,
        ::checkers::is_character<char,']'>,
        ::checkers::is_space_or<','>
    > topLoader(data.m_top);
    in >> topLoader;

    ::loaders::loader::v4::dataLoader<
        std::vector<int>,
        char,
        VectorReader<int>,
        1,
        ::checkers::is_character<char,'['>,
        ::checkers::is_character<char,']'>,
        ::checkers::is_space_or<','>
    > bottomLoader(data.m_bottom);
    in >> bottomLoader;

    ::loaders::loader::v4::dataLoader<
        std::vector<int>,
        char,
        VectorReader<int>,
        1,
        ::checkers::is_character<char,'['>,
        ::checkers::is_character<char,']'>,
        ::checkers::is_space_or<','>
    > leftLoader(data.m_left);
    in >> leftLoader;

    ::loaders::loader::v4::dataLoader<
        std::vector<int>,
        char,
        VectorReader<int>,
        1,
        ::checkers::is_character<char,'['>,
        ::checkers::is_character<char,']'>,
        ::checkers::is_space_or<','>
    > rightLoader(data.m_right);
    in >> rightLoader;

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
class MagnetPuzzleFixture :
    public testing::TestWithParam<MagnetPuzzleData> {
};

// Parameterized Test Definition
TEST_P(MagnetPuzzleFixture, MagnetPuzzleTests) {
    MagnetPuzzleData data = GetParam();

    Solution solution;

    std::vector<std::vector<char>> actual = solution.solveMagnetPuzzle(data.get_rules(),
        data.get_top(), data.get_bottom(), data.get_left(),data.get_right());

    ASSERT_EQ(actual, data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(MagnetPuzzleTests, MagnetPuzzleFixture, testing::ValuesIn(
    Loader<MagnetPuzzleData>()(find_path("matrices/data/magnet_puzzle.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
