/**
 * @file arithmetic_tripletstests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains tests to the problem https://www.techiedelight.com/?problem=ArithmeticTriplets
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
#include "arithmetic_triplets.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::utils;
using namespace valhalla::arrays::arithmetic_triplets;

// Test Fixture Data Class
class ArithmeticTripletsData {
    std::vector<int> m_input;
    std::set<std::vector<int>> m_expected;
public:
    ArithmeticTripletsData() = default;

    std::vector<int> const & get_input() { return m_input; }
    std::set<std::vector<int>> const & get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const ArithmeticTripletsData &);
    friend std::istream& operator>>(std::istream&, ArithmeticTripletsData &);

};

std::ostream& operator<<(std::ostream& out, const ArithmeticTripletsData & data) {
    out << "ArithmeticTripletsData [ input=[";
    for (int value : data.m_input)
        out << " " << value;
    out << " ] expected={";
    for (std::vector<int> values : data.m_expected) {
        out << " [";
        for (int value : values)
            out << " " << value;
        out << " ]";
    } // for
    out << " } ]";

    return out;
}

std::istream& operator>>(std::istream& in, ArithmeticTripletsData &data) {
    ::loaders::vectors::vectorLoader<
        int,
        std::vector<int>,
        char,
        ::checkers::is_space_or<','>
    > inputLoader(data.m_input, '[', ']');
    in >> inputLoader;

    ::checkers::is_space_or<','> isSpace;

    // skip spaces
    while (isSpace(in.peek())) in.get();

    if (static_cast<char>(in.peek()) == '{') {
        in.get(); // read '{' character

        // skip spaces
        while (isSpace(in.peek())) in.get();

        while (static_cast<char>(in.peek()) != '}') {
            std::vector<int> expected;
            ::loaders::vectors::vectorLoader<
                int,
                std::vector<int>,
                char,
                ::checkers::is_space_or<','>
            > expectedLoader(expected, '[', ']');
            in >> expectedLoader;

            data.m_expected.insert(expected);

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
class ArithmeticTripletsFixture :
    public testing::TestWithParam<ArithmeticTripletsData> {
};

// Parameterized Test Definition
TEST_P(ArithmeticTripletsFixture, ArithmeticTripletsTests) {
    ArithmeticTripletsData data = GetParam();

    Solution solution;

    std::set<std::vector<int>> actual = solution.findTriplets(data.get_input());

    ASSERT_EQ(actual, data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(ArithmeticTripletsTests, ArithmeticTripletsFixture, testing::ValuesIn(
    Loader<ArithmeticTripletsData>()(find_path("arrays/data/arithmetic_triplets.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
