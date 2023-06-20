/**
 * @file duplicate_rowstests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains tests to the problem https://www.techiedelight.com/?problem=DuplicateRows
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
#include "duplicate_rows.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::utils;
using namespace valhalla::matrices::duplicate_rows;

// Test Fixture Data Class
class DuplicateRowsData {
    std::vector<std::vector<int>> m_input;
    std::unordered_set<int> m_expected;
public:
    DuplicateRowsData() = default;

    std::vector<std::vector<int>> const & get_input() { return m_input; }
    std::unordered_set<int> const & get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const DuplicateRowsData &);
    friend std::istream& operator>>(std::istream&, DuplicateRowsData &);

};

std::ostream& operator<<(std::ostream& out, const DuplicateRowsData & data) {
    out << "DuplicateRowsData [ input=[";
    for (std::vector<int> values : data.m_input) {
        out << " [";
        for (int value : values) {
            out << " " << value;
        } // for
        out << " ]";
    } // for
    out << " ] expected={";
    for (int value : data.m_expected) {
        out << " " << value;
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

struct UnorderedSetReader {
    std::basic_istream<char> & operator()(std::basic_istream<char> & in, std::unordered_set<int> & uset, int state) {
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

        uset.insert(entry);

        return in;
    }
};

std::istream& operator>>(std::istream& in, DuplicateRowsData &data) {
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
        std::unordered_set<int>,
        char,
        UnorderedSetReader,
        1,
        ::checkers::is_character<char,'{'>,
        ::checkers::is_character<char,'}'>,
        ::checkers::is_space_or<','>
    > expectedLoader(data.m_expected);
    in >> expectedLoader;

    return in;
}

// Test Fixture Class
class DuplicateRowsFixture :
    public testing::TestWithParam<DuplicateRowsData> {
};

// Parameterized Test Definition
TEST_P(DuplicateRowsFixture, DuplicateRowsTests) {
    DuplicateRowsData data = GetParam();

    Solution solution;

    std::unordered_set<int> actual = solution.findDuplicateRows(data.get_input());

    ASSERT_EQ(actual, data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(DuplicateRowsTests, DuplicateRowsFixture, testing::ValuesIn(
    Loader<DuplicateRowsData>()(find_path("matrices/data/duplicate_rows.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
