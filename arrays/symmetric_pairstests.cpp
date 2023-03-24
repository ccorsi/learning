/**
 * @file symmetric_pairstests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains tests to the problem https://www.techiedelight.com/?problem=SymmetricPairs
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
#include "symmetric_pairs.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::utils;
using namespace valhalla::arrays::symmetric_pairs;

// Test Fixture Data Class
class SymmetricPairsData {
    std::set<std::pair<int,int>> m_input;
    std::set<std::set<std::pair<int,int>>> m_expected;

public:
    SymmetricPairsData() = default;

    std::set<std::pair<int,int>> const & get_input() { return m_input; }
    std::set<std::set<std::pair<int,int>>> const & get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const SymmetricPairsData &);
    friend std::istream& operator>>(std::istream&, SymmetricPairsData &);

};

std::ostream& operator<<(std::ostream& out, const SymmetricPairsData & data) {
    out << "SymmetricPairsData [ input={";
    for (std::pair<int,int> point : data.m_input)
        out << " (" << point.first << "," << point.second << ")";
    out << " } expected={";
    for (std::set<std::pair<int,int>> points : data.m_expected) {
        out << " {";
        for (std::pair<int,int> point : points) {
            out << " (" << point.first << "," << point.second << ")";
        } // for
        out << " }";
    } // for
    out << " } ]";

    return out;
}

std::istream& operator>>(std::istream& in, SymmetricPairsData &data) {
    ::checkers::skip_spaces<char, ::checkers::is_space_or<','>> skipSpace;

    skipSpace(in);

    if (static_cast<char>(in.peek()) == '{') {
        in.get(); // read '{' character
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
            > pairLoader(point);
            in >> pairLoader;

            data.m_input.insert(point);

            skipSpace(in);
        } // while

        in.get(); // read the '}' character
        skipSpace(in);

        if (static_cast<char>(in.peek()) == '{') {
            in.get();  // read '{' character
            skipSpace(in);

            while (static_cast<char>(in.peek()) != '}') {
                if (static_cast<char>(in.peek()) == '{') {
                    in.get(); // read '(' character
                    skipSpace(in);

                    std::set<std::pair<int,int>> points;

                    while (static_cast<char>(in.peek()) != '}') {
                        std::pair<int,int> point;
                        ::loaders::pairs::pairLoader<
                            int,
                            int,
                            char,
                            '(',
                            ')',
                            ::checkers::is_space_or<','>
                        > pairLoader(point);
                        in >> pairLoader;
                        points.insert(point);
                        skipSpace(in);
                    } // while
                    in.get(); // read '}' character
                    skipSpace(in);

                    data.m_expected.insert(points);
                } // if
            } // while
            in.get(); // read '}' character
            skipSpace(in);

            return in;
        } // if
    } // if

    throw std::runtime_error("Invalid input format");
}

// Test Fixture Class
class SymmetricPairsFixture :
    public testing::TestWithParam<SymmetricPairsData> {
};

// Parameterized Test Definition
TEST_P(SymmetricPairsFixture, SymmetricPairsTests) {
    SymmetricPairsData data = GetParam();

    Solution solution;

    std::set<std::set<std::pair<int,int>>> actual = solution.findSymmetricPairs(data.get_input());

    ASSERT_EQ(actual, data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(SymmetricPairsTests, SymmetricPairsFixture, testing::ValuesIn(
    Loader<SymmetricPairsData>()(find_path("arrays/data/symmetric_pairs.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
