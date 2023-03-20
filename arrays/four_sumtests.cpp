/**
 * @file four_sumtests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains tests to the problem https://www.techiedelight.com/?problem=4Sum
 * @version 0.1
 * @date 2023-03-20
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
#include "four_sum.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::utils;
using namespace valhalla::arrays::four_sum;

// Test Fixture Data Class
class FourSumData {
    std::vector<int> m_input;
    int m_target;
    std::set<std::vector<int>> m_expected;
public:
    FourSumData() = default;

    std::vector<int> const & get_input() { return m_input; }
    int get_target() { return m_target; }
    std::set<std::vector<int>> const & get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const FourSumData &);
    friend std::istream& operator>>(std::istream&, FourSumData &);

};

std::ostream& operator<<(std::ostream& out, const FourSumData & data) {
    out << "FourSumData [ input=[";
    for (int value : data.m_input)
        out << " " << value;
    out << " ] target=" << data.m_target << " expected={";
    for (std::vector<int> values : data.m_expected) {
        out << " [";
        for (int value : values)
            out << " " << value;
        out << " ]";
    }
    out << " } ]";

    return out;
}

std::istream& operator>>(std::istream& in, FourSumData &data) {
    ::loaders::vectors::vectorLoader<
        int,
        std::vector<int>,
        char,
        ::checkers::is_space_or<','>
    > inputLoader(data.m_input, '[', ']');
    in >> inputLoader;

    in >> data.m_target;

    ::checkers::is_space_or<','> isSpace;

    // skip spaces
    while (isSpace(in.peek())) in.get();

    if (static_cast<char>(in.peek()) == '{') {
        in.get(); // read '{' character

        // skip spaces
        while (isSpace(in.peek())) in.get();

        while (static_cast<char>(in.peek()) != '}') {
            // skip spaces
            while (isSpace(in.peek())) in.get();

            std::vector<int> values;
            ::loaders::vectors::vectorLoader<
                int,
                std::vector<int>,
                char,
                ::checkers::is_space_or<','>
            > expectedLoader(values, '[', ']');
            in >> expectedLoader;

            data.m_expected.insert(values);

            // skip spaces
            while (isSpace(in.peek())) in.get();
        } // while

        in.get(); // read '}' character

        // skip spaces
        while (isSpace(in.peek())) in.get();

        return in;
    } // if

    throw std::runtime_error("Invalid input format");
}

// Test Fixture Class
class FourSumFixture :
    public testing::TestWithParam<FourSumData> {
};

// Parameterized Test Definition
TEST_P(FourSumFixture, FourSumTests) {
    FourSumData data = GetParam();

    Solution solution;

    std::set<std::vector<int>> actual = solution.findQuadruplets(data.get_input(), data.get_target());

    ASSERT_EQ(actual, data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(FourSumTests, FourSumFixture, testing::ValuesIn(
    Loader<FourSumData>()(find_path("arrays/data/four_sum.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
