/**
 * @file merge_sorted_liststests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief 
 * @version 0.1
 * @date 2026-04-24
 * 
 * @copyright Copyright (c) 2026 Claudio Corsi
 * 
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include <iostream>

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "paths.h"
#include "loaders.h"
#include "readers.h"
#include "merge_sorted_lists.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::utils::readers;
using namespace valhalla::utils;
using namespace valhalla::heap::merge_sorted_lists;

// Test Fixture Data Class
class MergeSortedListsData {
    std::vector<std::vector<int>> m_input;
    std::vector<int> m_expected;
public:
    MergeSortedListsData() = default;

    std::vector<std::vector<int>> const & get_input() { return m_input; }
    std::vector<int> const & get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const MergeSortedListsData &);
    friend std::istream& operator>>(std::istream&, MergeSortedListsData &);

    friend struct CombinedReader;
};

struct VectorVectorReader {
    std::basic_istream<char> & operator()(std::basic_istream<char> & in, std::vector<std::vector<int>> & vecvec, int state) {
        switch (state) {
            case 0: {
                std::vector<int> vec;
                ::loaders::loader::v6::dataLoader<
                    std::vector<int>,
                    char,
                    VectorReader<int>,
                    1,
                    ::checkers::is_character<char, '{'>,
                    ::checkers::is_character<char, '}'>,
                    ::checkers::is_space_or<','>
                > VectorLoader(vec);
                in >> VectorLoader;
                vecvec.push_back(vec);
            }
            break;
            default:
                throw std::runtime_error("INVALID STATE");
        } // switch (state)

        return in;
    }
};

struct CombinedReader {
    std::basic_istream<char> & operator()(std::basic_istream<char> & in, MergeSortedListsData & data, int state) {
        switch (state) {
            case 0: {
                ::loaders::loader::v6::dataLoader<
                    std::vector<std::vector<int>>,
                    char,
                    VectorVectorReader,
                    1,
                    ::checkers::is_character<char, '{'>,
                    ::checkers::is_character<char, '}'>,
                    ::checkers::is_space_or<','>
                > VectorVectorLoader(data.m_input);
                in >> VectorVectorLoader;
            }
            break;
            case 1: {
                ::loaders::loader::v6::dataLoader<
                    std::vector<int>,
                    char,
                    VectorReader<int>,
                    1,
                    ::checkers::is_character<char, '{'>,
                    ::checkers::is_character<char, '}'>,
                    ::checkers::is_space_or<','>
                > VectorLoader(data.m_expected);
                in >> VectorLoader;
            }
            break;
            default:
                throw std::runtime_error("INVALID STATE");
        } // switch (state)

        return in;
    }
};
std::ostream& operator<<(std::ostream& out, const MergeSortedListsData & data) {
    out << "MergeSortedListsData [ input=[";
    for (auto & vec : data.m_input) {
        out << " [";
        for (auto & value : vec) {
            out << " " << value;
        } // for (auto & value : vec)
        out << " ]";
    } // for (auto & vec : data.m_input)
    out << " ], expected=[";
    for (auto & val : data.m_expected) {
        out << " " << val;
    } // for (auto & val : data.m_expected)
    out << " ] ]";

    return out;
}

std::istream& operator>>(std::istream& in, MergeSortedListsData &data) {
    ::loaders::loader::v6::dataLoader<
        MergeSortedListsData,
        char,
        CombinedReader,
        2,
        ::checkers::is_character<char, '{'>,
        ::checkers::is_character<char, '}'>,
        ::checkers::is_space_or<','>
    > DataLoader(data);
    in >> DataLoader;

    return in;
}

// Test Fixture Class
class MergeSortedListsFixture :
    public testing::TestWithParam<MergeSortedListsData> {
};

// Parameterized Test Definition
TEST_P(MergeSortedListsFixture, MergeSortedListsTests) {
    MergeSortedListsData data = GetParam();

    Solution solution;

    ASSERT_EQ(solution.mergeSortedLists(data.get_input()), data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(MergeSortedListsTests, MergeSortedListsFixture, testing::ValuesIn(
    Loader<MergeSortedListsData>()(find_path("heap/data/merge_sorted_lists.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
