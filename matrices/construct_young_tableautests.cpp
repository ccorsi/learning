/**
 * @file construct_young_tableautests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains tests to the problem https://www.techiedelight.com/?problem=ConstructYoungTableau
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
#include "construct_young_tableau.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::utils;
using namespace valhalla::matrices::construct_young_tableau;

// Test Fixture Data Class
class ConstructYoungTableauData {
    std::vector<int> m_input;
    std::set<std::vector<std::vector<int>>> m_expected;
public:
    ConstructYoungTableauData() = default;

    std::vector<int> const & get_input() { return m_input; }
    std::set<std::vector<std::vector<int>>> const & get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const ConstructYoungTableauData &);
    friend std::istream& operator>>(std::istream&, ConstructYoungTableauData &);

};

std::ostream& operator<<(std::ostream& out, const ConstructYoungTableauData & data) {
    out << "ConstructYoungTableauData [ input=[";
    for (int value : data.m_input) {
        out << " " << value;
    } // for
    out << " ] expected={";
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

std::istream& operator>>(std::istream& in, ConstructYoungTableauData &data) {
    ::loaders::loader::v4::dataLoader<
        std::vector<int>,
        char,
        VectorReader,
        1,
        ::checkers::is_character<char,'['>,
        ::checkers::is_character<char,']'>,
        ::checkers::is_space_or<','>
    > inputLoader(data.m_input);
    in >> inputLoader;

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
class ConstructYoungTableauFixture :
    public testing::TestWithParam<ConstructYoungTableauData> {
};

// Parameterized Test Definition
TEST_P(ConstructYoungTableauFixture, ConstructYoungTableauTests) {
    ConstructYoungTableauData data = GetParam();

    Solution solution;

    std::vector<std::vector<int>> actual = solution.constructYoungTableau(data.get_input());

    ASSERT_THAT(actual, testing::AnyOfArray(data.get_expected()));
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(ConstructYoungTableauTests, ConstructYoungTableauFixture, testing::ValuesIn(
    Loader<ConstructYoungTableauData>()(find_path("matrices/data/construct_young_tableau.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
