/**
 * @file two_difftests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains tests to the problem https://www.techiedelight.com/?problem=2Diff
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
#include "two_diff.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::utils;
using namespace valhalla::arrays::two_diff;

// Test Fixture Data Class
class TwoDiffData {
    std::vector<int> m_input;
    int m_k;
    std::set<std::pair<int,int>> m_expected;
public:
    TwoDiffData() = default;

    std::vector<int> const & get_input() { return m_input; }
    int get_k() { return m_k; }
    std::set<std::pair<int,int>> const & get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const TwoDiffData &);
    friend std::istream& operator>>(std::istream&, TwoDiffData &);

};

std::ostream& operator<<(std::ostream& out, const TwoDiffData & data) {
    out << "TwoDiffData [ input=[";
    for (int value : data.m_input)
        out << " " << value;
    out << " ] k=" << data.m_k << " expected={";
    for (std::pair<int,int> diff : data.m_expected)
        out << " (" << diff.first << "," << diff.second << ")";
    out << " } ]";

    return out;
}

std::istream& operator>>(std::istream& in, TwoDiffData &data) {
    ::loaders::vectors::vectorLoader<
        int,
        std::vector<int>,
        char,
        ::checkers::is_space_or<','>
    > inputLoaders(data.m_input, '[', ']');
    in >> inputLoaders;

    in >> data.m_k;

    ::checkers::is_space isSpace;

    // skip spaces
    while (isSpace(in.peek())) in.get();

    if (static_cast<char>(in.peek()) == '{') {
        in.get(); // read '{' character

        // skip spaces
        while (isSpace(in.peek())) in.get();

        while (static_cast<char>(in.peek()) != '}') {
            std::pair<int,int> diff;

            ::loaders::pairs::pairLoader<
                int,
                int,
                char,
                '(',
                ')',
                ::checkers::is_space_or<','>
            > expectedLoader(diff);
            in >> expectedLoader;

            data.m_expected.insert(diff);

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
class TwoDiffFixture :
    public testing::TestWithParam<TwoDiffData> {
};

// Parameterized Test Definition
TEST_P(TwoDiffFixture, TwoDiffTests) {
    TwoDiffData data = GetParam();

    Solution solution;

    std::set<std::pair<int,int>> actual = solution.findPairs(data.get_input(), data.get_k());

    ASSERT_EQ(actual, data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(TwoDiffTests, TwoDiffFixture, testing::ValuesIn(
    Loader<TwoDiffData>()(find_path("arrays/data/two_diff.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
