/**
 * @file sort_with_young_tableautests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains tests to the problem https://www.techiedelight.com/?problem=SortWithYoungTableau
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
#include "sort_with_young_tableau.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::utils;
using namespace valhalla::matrices::sort_with_young_tableau;

// Test Fixture Data Class
class SortWithYoungTableauData {
    std::vector<int> m_input, m_expected;
public:
    SortWithYoungTableauData() = default;

    std::vector<int> const & get_input() { return m_input; }
    std::vector<int> const & get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const SortWithYoungTableauData &);
    friend std::istream& operator>>(std::istream&, SortWithYoungTableauData &);

};

std::ostream& operator<<(std::ostream& out, const SortWithYoungTableauData & data) {
    out << "SortWithYoungTableauData [ input=[";
    for (int value : data.m_input) {
        out << " " << value;
    } // for
    out << " ] expected=[";
    for (int value : data.m_expected) {
        out << " " << value;
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

std::istream& operator>>(std::istream& in, SortWithYoungTableauData &data) {
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
        std::vector<int>,
        char,
        VectorReader,
        1,
        ::checkers::is_character<char,'['>,
        ::checkers::is_character<char,']'>,
        ::checkers::is_space_or<','>
    > expectedLoader(data.m_expected);
    in >> expectedLoader;

    return in;
}

// Test Fixture Class
class SortWithYoungTableauFixture :
    public testing::TestWithParam<SortWithYoungTableauData> {
};

// Parameterized Test Definition
TEST_P(SortWithYoungTableauFixture, SortWithYoungTableauTests) {
    SortWithYoungTableauData data = GetParam();

    Solution solution;

    std::vector<int> actual = data.get_input();

    solution.sort(actual);

    ASSERT_EQ(actual, data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(SortWithYoungTableauTests, SortWithYoungTableauFixture, testing::ValuesIn(
    Loader<SortWithYoungTableauData>()(find_path("matrices/data/sort_with_young_tableau.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
