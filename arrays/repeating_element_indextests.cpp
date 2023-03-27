/**
 * @file repeating_element_indextests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains tests to the problem https://www.techiedelight.com/?problem=RepeatingElementIndex
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
#include "repeating_element_index.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::utils;
using namespace valhalla::arrays::repeating_element_index;

// Test Fixture Data Class
class RepeatingElementIndexData {
    std::vector<int> m_input;
    int m_expected;
public:
    RepeatingElementIndexData() = default;

    std::vector<int> const & get_input() { return m_input; }
    int get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const RepeatingElementIndexData &);
    friend std::istream& operator>>(std::istream&, RepeatingElementIndexData &);

};

std::ostream& operator<<(std::ostream& out, const RepeatingElementIndexData & data) {
    out << "RepeatingElementIndexData [ input=[";
    for (int value : data.m_input)
        out << " " << value;
    out << " ] expected=" << data.m_expected << " ]";

    return out;
}

std::istream& operator>>(std::istream& in, RepeatingElementIndexData &data) {
    ::loaders::vectors::vectorLoader<
        int,
        std::vector<int>,
        char,
        ::checkers::is_space_or<','>
    > inputLoader(data.m_input, '[', ']');
    in >> inputLoader;

    ::checkers::skip_spaces<char, ::checkers::is_space_or<','>> skipSpace;

    skipSpace(in);

    in >> data.m_expected;

    skipSpace(in);

    return in;
}

// Test Fixture Class
class RepeatingElementIndexFixture :
    public testing::TestWithParam<RepeatingElementIndexData> {
};

// Parameterized Test Definition
TEST_P(RepeatingElementIndexFixture, RepeatingElementIndexTests) {
    RepeatingElementIndexData data = GetParam();

    Solution solution;

    int actual = solution.findMinIndex(data.get_input());

    ASSERT_EQ(actual, data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(RepeatingElementIndexTests, RepeatingElementIndexFixture, testing::ValuesIn(
    Loader<RepeatingElementIndexData>()(find_path("arrays/data/repeating_element_index.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
