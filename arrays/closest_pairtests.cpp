/**
 * @file closest_pairtests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains tests to the problem https://www.techiedelight.com/?problem=ClosestPair
 * @version 0.1
 * @date 2023-03-23
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
#include "closest_pair.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::utils;
using namespace valhalla::arrays::closest_pair;

// Test Fixture Data Class
class ClosestPairData {
    std::vector<int> m_x_input;
    std::vector<int> m_y_input;
    int m_k;
    std::vector<std::pair<int,int>> m_expected;
public:
    ClosestPairData() = default;

    std::vector<int> const & get_x_input() { return m_x_input; }
    std::vector<int> const & get_y_input() { return m_y_input; }
    int get_k() { return m_k; }
    std::vector<std::pair<int,int>> const & get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const ClosestPairData &);
    friend std::istream& operator>>(std::istream&, ClosestPairData &);

};

std::ostream& operator<<(std::ostream& out, const ClosestPairData & data) {
    out << "ClosestPairData [ X=[";
    for (int value : data.m_x_input)
        out << " " << value;
    out << " ] Y=[";
    for (int value : data.m_y_input)
        out << " " << value;
    out << " ] k=" << data.m_k << " expected={";
    for (std::pair<int,int> point : data.m_expected)
        out << " (" << point.first << "," << point.second << ")";
    out << " ]";

    return out;
}

std::istream& operator>>(std::istream& in, ClosestPairData &data) {
    ::checkers::skip_spaces<char,::checkers::is_space_or<','>> skipSpace;
    skipSpace(in);

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

    in >> data.m_k;
    skipSpace(in);

    if (static_cast<char>(in.peek()) == '{') {
        in.get(); // read the '{' character
        skipSpace(in);

        while (static_cast<char>(in.peek()) != '}') {
            std::pair<int,int> point;
            ::loaders::pairs::pairLoader<
                int,
                int,
                char,
                '(',
                ')',
                ::checkers::is_space_or<','>
            > expectedLoader(point);
            in >> expectedLoader;

            data.m_expected.push_back(point);
        } // while
        in.get();
        skipSpace(in);

        return in;
    } // if

    throw std::runtime_error("Invalid input format");
}

// Test Fixture Class
class ClosestPairFixture :
    public testing::TestWithParam<ClosestPairData> {
};

// Parameterized Test Definition
TEST_P(ClosestPairFixture, ClosestPairTests) {
    ClosestPairData data = GetParam();

    Solution solution;

    std::pair<int,int> actual = solution.findClosestPair(data.get_x_input(), data.get_y_input(), data.get_k());

    ASSERT_THAT(actual, ::testing::AnyOfArray(data.get_expected()));
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(ClosestPairTests, ClosestPairFixture, testing::ValuesIn(
    Loader<ClosestPairData>()(find_path("arrays/data/closest_pair.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
