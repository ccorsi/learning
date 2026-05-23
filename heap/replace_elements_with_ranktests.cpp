/**
 * @file replace_elements_with_ranktests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains the tests to the problem https://www.techiedelight.com/?problem=ReplaceElementsWithRank
 * @version 0.1
 * @date 2026-05-02
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
#include "replace_elements_with_rank.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::utils::readers;
using namespace valhalla::utils;
using namespace valhalla::heap::replace_elements_with_rank;

// Test Fixture Data Class
class ReplaceElementsWithRankData {
    std::vector<int> m_input, m_expected;
public:
    ReplaceElementsWithRankData() = default;

    std::vector<int> const & get_input() { return m_input; }
    std::vector<int> const & get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const ReplaceElementsWithRankData &);
    friend std::istream& operator>>(std::istream&, ReplaceElementsWithRankData &);

    friend struct CombinedReader;
};

std::ostream& operator<<(std::ostream& out, const ReplaceElementsWithRankData & data) {
    out << "ReplaceElementsWithRankData [ input=[";
    for (auto v : data.m_input) {
        out << " " << v;
    } // for (auto v : data.m_input)
    out << " ] expected=[";
    for (auto v : data.m_expected) {
        out << " " << v;
    } // for (auto v : data.m_expected)
    out << " ] ]";

    return out;
}

std::istream& operator>>(std::istream& in, ReplaceElementsWithRankData &data) {
    ::loaders::loader::v6::dataLoader<
        ReplaceElementsWithRankData,
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

struct CombinedReader {
    std::basic_istream<char> & operator()(std::basic_istream<char> & in, ReplaceElementsWithRankData & data, int state) {
        switch (state) {
            case 0: {
                ::loaders::loader::v6::dataLoader<
                    std::vector<int>,
                    char,
                    VectorReader<int>,
                    1,
                    ::checkers::is_character<char, '{'>,
                    ::checkers::is_character<char, '}'>,
                    ::checkers::is_space_or<','>
                > VectorLoader(data.m_input);
                in >> VectorLoader;
                break;
            }
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
                break;
            }
            default:
                throw std::runtime_error("INVALID STATE");
        } // switch (state)
        return in;
    }
};
// Test Fixture Class
class ReplaceElementsWithRankFixture :
    public testing::TestWithParam<ReplaceElementsWithRankData> {
};

// Parameterized Test Definition
TEST_P(ReplaceElementsWithRankFixture, ReplaceElementsWithRankTests) {
    ReplaceElementsWithRankData data = GetParam();

    Solution solution;

    std::vector<int> input =  data.get_input();
    solution.transform(input);

    ASSERT_EQ(input, data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(ReplaceElementsWithRankTests, ReplaceElementsWithRankFixture, testing::ValuesIn(
    Loader<ReplaceElementsWithRankData>()(find_path("heap/data/replace_elements_with_rank.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
