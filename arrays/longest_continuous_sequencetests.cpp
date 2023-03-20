/**
 * @file longest_continuous_sequencetests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains tests to the problem https://www.techiedelight.com/?problem=LongestContinuousSequence
 * @version 0.1
 * @date 2023-03-19
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
#include "longest_continuous_sequence.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::utils;
using namespace valhalla::arrays::longest_continuous_sequence;

// Test Fixture Data Class
class LongestContinuousSequenceData {
    std::vector<int> m_x_input;
    std::vector<int> m_y_input;
    int m_expected;
public:
    LongestContinuousSequenceData() = default;

    std::vector<int> const & get_x_input() { return m_x_input; }
    std::vector<int> const & get_y_input() { return m_y_input; }
    int get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const LongestContinuousSequenceData &);
    friend std::istream& operator>>(std::istream&, LongestContinuousSequenceData &);

};

std::ostream& operator<<(std::ostream& out, const LongestContinuousSequenceData & data) {
    out << "LongestContinuousSequenceData [ X=[";
    for (int value : data.m_x_input)
        out << " " << value;
    out << " ] Y=[";
    for (int value : data.m_y_input)
        out << " " << value;
    out << " ] expected=" << data.m_expected << " ]";

    return out;
}

std::istream& operator>>(std::istream& in, LongestContinuousSequenceData &data) {
    ::loaders::vectors::vectorLoader<
        int,
        std::vector<int>,
        char,
        ::checkers::is_space_or<','>
    > inputXLoader(data.m_x_input, '[', ']');
    in >> inputXLoader;

    ::loaders::vectors::vectorLoader<
        int,
        std::vector<int>,
        char,
        ::checkers::is_space_or<','>
    > inputYLoader(data.m_y_input, '[', ']');
    in >> inputYLoader;

    in >> data.m_expected;

    ::checkers::is_space isSpace;

    // skip spaces
    while (isSpace(in.peek())) in.get();

    return in;
}

// Test Fixture Class
class LongestContinuousSequenceFixture :
    public testing::TestWithParam<LongestContinuousSequenceData> {
};

// Parameterized Test Definition
TEST_P(LongestContinuousSequenceFixture, LongestContinuousSequenceTests) {
    LongestContinuousSequenceData data = GetParam();

    Solution solution;

    int actual = solution.findMaxSubarrayLength(data.get_x_input(), data.get_y_input());

    ASSERT_EQ(actual, data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(LongestContinuousSequenceTests, LongestContinuousSequenceFixture, testing::ValuesIn(
    Loader<LongestContinuousSequenceData>()(find_path("arrays/data/longest_continuous_sequence.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
