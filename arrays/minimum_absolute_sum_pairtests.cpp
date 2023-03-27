/**
 * @file minimum_absolute_sum_pairtests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains tests to the problem https://www.techiedelight.com/?problem=MinimumAbsoluteSumPair
 * @version 0.1
 * @date 2023-03-27
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
#include "minimum_absolute_sum_pair.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::utils;
using namespace valhalla::arrays::minimum_absolute_sum_pair;

// Test Fixture Data Class
class MinimumAbsoluteSumPairData {
    std::vector<int> m_input;
    std::set<std::pair<int,int>> m_expected;
public:
    MinimumAbsoluteSumPairData() = default;

    std::vector<int> const & get_input() { return m_input; }
    std::set<std::pair<int,int>> const & get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const MinimumAbsoluteSumPairData &);
    friend std::istream& operator>>(std::istream&, MinimumAbsoluteSumPairData &);

};

std::ostream& operator<<(std::ostream& out, const MinimumAbsoluteSumPairData & data) {
    out << "MinimumAbsoluteSumPairData [ input=[";
    for (int value : data.m_input)
        out << " " << value;
    out << " ] expected={";
    for (std::pair<int,int> expected : data.m_expected)
        out << " (" << expected.first << "," << expected.second << ")";
    out << " } ]";

    return out;
}

std::istream& operator>>(std::istream& in, MinimumAbsoluteSumPairData &data) {
    ::loaders::vectors::vectorLoader<
        int,
        std::vector<int>,
        char,
        ::checkers::is_space_or<','>
    > inputLoader(data.m_input, '[', ']');
    in >> inputLoader;

    ::checkers::skip_spaces<char, ::checkers::is_space_or<','>> skipSpace;

    skipSpace(in);

    if (static_cast<char>(in.peek()) == '{') {
        in.get(); // read '{' character
        skipSpace(in);

        while (static_cast<char>(in.peek()) != '}') {
            std::pair<int,int> expected;
            ::loaders::pairs::pairLoader<
                int, int, char, '(', ')', ::checkers::is_space_or<','>
            > expectedLoader(expected);
            in >> expectedLoader;

            data.m_expected.insert(expected);

            skipSpace(in);
        } // while
        in.get(); // read '}' character
        skipSpace(in);

        return in;
    } // if

    throw std::runtime_error("Invalid input format");
}

// Test Fixture Class
class MinimumAbsoluteSumPairFixture :
    public testing::TestWithParam<MinimumAbsoluteSumPairData> {
};

// Parameterized Test Definition
TEST_P(MinimumAbsoluteSumPairFixture, MinimumAbsoluteSumPairTests) {
    MinimumAbsoluteSumPairData data = GetParam();

    Solution solution;

    std::pair<int,int> actual = solution.findPair(data.get_input());

    ASSERT_THAT(actual, ::testing::AnyOfArray(data.get_expected()));
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(MinimumAbsoluteSumPairTests, MinimumAbsoluteSumPairFixture, testing::ValuesIn(
    Loader<MinimumAbsoluteSumPairData>()(find_path("arrays/data/minimum_absolute_sum_pair.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
