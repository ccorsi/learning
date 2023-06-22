/**
 * @file replace_element_in_young_tableautests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains tests to the problem https://www.techiedelight.com/?problem=ReplaceElementInYoungTableau
 * @version 0.1
 * @date 2023-06-21
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
#include "replace_element_in_young_tableau.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::utils;
using namespace valhalla::matrices::replace_element_in_young_tableau;

// Test Fixture Data Class
class ReplaceElementInYoungTableauData {
    std::vector<std::vector<int>> m_input;
    int m_x, m_y;
    std::set<std::vector<std::vector<int>>> m_expected;
public:
    ReplaceElementInYoungTableauData() = default;

    std::vector<std::vector<int>> const & get_input() { return m_input; }
    int get_x() { return m_x; }
    int get_y() { return m_y; }
    std::set<std::vector<std::vector<int>>> const & get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const ReplaceElementInYoungTableauData &);
    friend std::istream& operator>>(std::istream&, ReplaceElementInYoungTableauData &);

};

std::ostream& operator<<(std::ostream& out, const ReplaceElementInYoungTableauData & data) {
    out << "ReplaceElementInYoungTableauData [ input=[";
    for (std::vector<int> values : data.m_input) {
        out << " [";
        for (int value : values) {
            out << " " << value;
        } // for
        out << " ]";
    } // for
    out << " ] x=" << data.m_x << " y=" << data.m_y << " expected={";
    for (std::vector<std::vector<int>> values : data.m_expected) {
        out << " [";
        for (std::vector<int> value : values) {
            out << " [";
            for (int v : value) {
                out << " " << v;
            } // for
            out << " ]";
        } // for
        out << " ]";
    } // for
    return out << " } ]";
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

struct SetVectorVectorReader {
    std::basic_istream<char> & operator()(std::basic_istream<char> & in, std::set<std::vector<std::vector<int>>> & setvecvec, int state) {
        std::vector<std::vector<int>> entry;

        ::loaders::loader::v4::dataLoader<
            std::vector<std::vector<int>>,
            char,
            VectorVectorReader,
            1,
            ::checkers::is_character<char,'['>,
            ::checkers::is_character<char,']'>,
            ::checkers::is_space_or<','>
        > entryLoader(entry);
        in >> entryLoader;

        setvecvec.insert(entry);

        return in;
    }
};

std::istream& operator>>(std::istream& in, ReplaceElementInYoungTableauData &data) {
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
        std::set<std::vector<std::vector<int>>>,
        char,
        SetVectorVectorReader,
        1,
        ::checkers::is_character<char,'{'>,
        ::checkers::is_character<char,'}'>,
        ::checkers::is_space_or<','>
    > expectedLoader(data.m_expected);
    in >> expectedLoader;

    return in;
}

// Test Fixture Class
class ReplaceElementInYoungTableauFixture :
    public testing::TestWithParam<ReplaceElementInYoungTableauData> {
};

// Parameterized Test Definition
TEST_P(ReplaceElementInYoungTableauFixture, ReplaceElementInYoungTableauTests) {
    ReplaceElementInYoungTableauData data = GetParam();

    Solution solution;

    std::vector<std::vector<int>> actual = data.get_input();

    solution.replaceInYoungTableau(actual, data.get_x(), data.get_y());

    ASSERT_THAT(actual, testing::AnyOfArray(data.get_expected()));
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(ReplaceElementInYoungTableauTests, ReplaceElementInYoungTableauFixture, testing::ValuesIn(
    Loader<ReplaceElementInYoungTableauData>()(find_path("matrices/data/replace_element_in_young_tableau.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
