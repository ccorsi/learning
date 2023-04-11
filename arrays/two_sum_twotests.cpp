/**
 * @file two_sum_twotests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains tests to the problem https://www.techiedelight.com/?problem=TwoSumII
 * @version 0.1
 * @date 2023-04-05
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include <iostream>
#include <set>

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "paths.h"
#include "loaders.h"
#include "two_sum_two.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::utils;
using namespace valhalla::arrays::two_sum_two;

// Test Fixture Data Class
class TwoSumTwoData {
    std::vector<int> m_input;
    std::set<std::pair<int,int>> m_expected;
    int m_target;
public:
    TwoSumTwoData() = default;

    std::vector<int> const & get_input() { return m_input; }
    std::set<std::pair<int,int>> const & get_expected() { return m_expected; }
    int get_target() { return m_target; }

    friend std::ostream& operator<<(std::ostream&, const TwoSumTwoData &);
    friend std::istream& operator>>(std::istream&, TwoSumTwoData &);

};

std::ostream& operator<<(std::ostream& out, const TwoSumTwoData & data) {
    out << "TwoSumTwoData [ input=[";
    for (int value : data.m_input)
        out << " " << value;
    out << " ] target=" << data.m_target << " expected={";
    for (std::pair<int,int> expected : data.m_expected)
        out << " (" << expected.first << "," << expected.second << ")";
    out << " } ]";

    return out;
}

std::istream& operator>>(std::istream& in, TwoSumTwoData &data) {
    ::loaders::vectors::vectorLoader<
      int,
      std::vector<int>,
      char,
      ::checkers::is_space_or<','>
    > inputLoader(data.m_input,'[', ']');
    in >> inputLoader;

    ::checkers::skip_spaces<char,::checkers::is_space_or<','>> skipSpace;

    skipSpace(in);
    in >> data.m_target;
    skipSpace(in);

    if (static_cast<char>(in.peek()) == '{') {
        in.get(); // read '{' character
        skipSpace(in);

        while (static_cast<char>(in.peek()) != '}') {
            std::pair<int,int> value;

            ::loaders::pairs::pairLoader<
            int,
            int,
            char,
            '(',
            ')',
            ::checkers::is_space_or<','>
            > expectedLoader(value);
            in >> expectedLoader;

            data.m_expected.insert(value);
        } // while

        in.get(); // read '}' character
        skipSpace(in);

        return in;
    } // if

    throw std::runtime_error("Invalid input format");
}

// Test Fixture Class
class TwoSumTwoFixture :
    public testing::TestWithParam<TwoSumTwoData> {
};

// Parameterized Test Definition
TEST_P(TwoSumTwoFixture, TwoSumTwoTests) {
    TwoSumTwoData data = GetParam();

    Solution solution;

    std::pair<int,int> actual = solution.findPair(data.get_input(), data.get_target());

    ASSERT_THAT(actual, ::testing::AnyOfArray(data.get_expected()));
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(TwoSumTwoTests, TwoSumTwoFixture, testing::ValuesIn(
    Loader<TwoSumTwoData>()(find_path("arrays/data/two_sum_two.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
