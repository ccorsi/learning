/**
 * @file distinct_elements_counttests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains tests to the problem https://www.techiedelight.com/?problem=DistinctElementsCount
 * @version 0.1
 * @date 2023-03-26
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
#include "distinct_elements_count.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::utils;
using namespace valhalla::arrays::distinct_elements_count;

// Test Fixture Data Class
class DistinctElementsCountData {
    std::vector<int> m_input;
    int m_k;
    std::vector<int> m_expected;
public:
    DistinctElementsCountData() = default;

    std::vector<int> const & get_input() { return m_input; }
    int get_k() { return m_k; }
    std::vector<int> const & get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const DistinctElementsCountData &);
    friend std::istream& operator>>(std::istream&, DistinctElementsCountData &);

};

std::ostream& operator<<(std::ostream& out, const DistinctElementsCountData & data) {
    out << "DistinctElementsCountData [ input=[";
    for (int value : data.m_input)
        out << " " << value;
    out <<" ] k=" << data.m_k << " expected=[";
    for (int value : data.m_expected)
        out  << " " << value;
    out << " ] ]";

    return out;
}

std::istream& operator>>(std::istream& in, DistinctElementsCountData &data) {
    ::loaders::vectors::vectorLoader<
        int,
        std::vector<int>,
        char,
        ::checkers::is_space_or<','>
    > inputLoader(data.m_input, '[', ']');
    in >> inputLoader;

    in >> data.m_k;

    ::checkers::skip_spaces<char, ::checkers::is_space_or<','>> skipSpace;

    skipSpace(in);

    ::loaders::vectors::vectorLoader<
        int,
        std::vector<int>,
        char,
        ::checkers::is_space_or<','>
    > expectedLoader(data.m_expected, '[', ']');
    in >> expectedLoader;

    return in;
}

// Test Fixture Class
class DistinctElementsCountFixture :
    public testing::TestWithParam<DistinctElementsCountData> {
};

// Parameterized Test Definition
TEST_P(DistinctElementsCountFixture, DistinctElementsCountTests) {
    DistinctElementsCountData data = GetParam();

    Solution solution;

    std::vector<int> actual = solution.findDistinctCount(data.get_input(), data.get_k());

    ASSERT_EQ(actual, data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(DistinctElementsCountTests, DistinctElementsCountFixture, testing::ValuesIn(
    Loader<DistinctElementsCountData>()(find_path("arrays/data/distinct_elements_count.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
