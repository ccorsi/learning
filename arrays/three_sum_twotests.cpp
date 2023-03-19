/**
 * @file three_sum_twotests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains tests to the problem https://www.techiedelight.com/?problem=3SumII
 * @version 0.1
 * @date 2023-03-18
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
#include "three_sum_two.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::utils;
using namespace valhalla::arrays::three_sum_two;

// Test Fixture Data Class
class ThreeSumTwoData {
    std::vector<int> m_input;
    int m_k;
    std::set<std::vector<int>> m_expected;
public:
    ThreeSumTwoData() = default;

    std::vector<int> const & get_input() { return m_input; }
    int get_k() { return m_k; }
    std::set<std::vector<int>> const & get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const ThreeSumTwoData &);
    friend std::istream& operator>>(std::istream&, ThreeSumTwoData &);

};

std::ostream& operator<<(std::ostream& out, const ThreeSumTwoData & data) {
    out << "ThreeSumTwoData [ input=[";
    out << " ] k=" << data.m_k << " expected={";
    for (std::vector<int> values : data.m_expected) {
        out << " [";
        for (int value : values)
            out << " " << value;
        out << " ]";
    } // for
    out << " } ]";

    return out;
}

std::istream& operator>>(std::istream& in, ThreeSumTwoData &data) {
    ::loaders::vectors::vectorLoader<
        int,
        std::vector<int>,
        char,
        ::checkers::is_space_or<','>
    > inputLoader(data.m_input, '[', ']');
    in >> inputLoader;

    in >> data.m_k;

    ::checkers::is_space isSpace;

    // skip spaces
    while (isSpace(in.peek())) in.get();

    if (static_cast<char>(in.peek()) == '{') {
        in.get(); // read '{'

        // skip spaces
        while (isSpace(in.peek())) in.get();

        while (static_cast<char>(in.peek()) != '}') {
            std::vector<int> values;

            ::loaders::vectors::vectorLoader<
                int,
                std::vector<int>,
                char,
                ::checkers::is_space_or<','>
            > expectedLoader(values, '[', ']');
            in >> expectedLoader;

            data.m_expected.insert(values);
        } // while

        in.get(); // read the '}' character

        // skip spaces
        while (isSpace(in.peek())) in.get();

        return in;
    } // if

    throw std::runtime_error("Invalid input format");
}

// Test Fixture Class
class ThreeSumTwoFixture :
    public testing::TestWithParam<ThreeSumTwoData> {
};

// Parameterized Test Definition
TEST_P(ThreeSumTwoFixture, ThreeSumTwoTests) {
    ThreeSumTwoData data = GetParam();

    Solution solution;

    std::vector<int> input(data.get_input());

    std::vector<int> actual = solution.findTriplets(input, data.get_k());

    ASSERT_THAT(actual, ::testing::AnyOfArray(data.get_expected()));
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(ThreeSumTwoTests, ThreeSumTwoFixture, testing::ValuesIn(
    Loader<ThreeSumTwoData>()(find_path("arrays/data/three_sum_two.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
