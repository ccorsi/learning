/**
 * @file maximum_product_triplettests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains tests to the problem https://www.techiedelight.com/?problem=MaximumProductTriplet
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
#include "maximum_product_triplet.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::utils;
using namespace valhalla::arrays::maximum_product_triplet;

// Test Fixture Data Class
class MaximumProductTripletData {
    std::vector<int> m_input;
    std::set<std::vector<int>> m_expected;
public:
    MaximumProductTripletData() = default;

    std::vector<int> const & get_input() { return m_input; }
    std::set<std::vector<int>> const & get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const MaximumProductTripletData &);
    friend std::istream& operator>>(std::istream&, MaximumProductTripletData &);

};

std::ostream& operator<<(std::ostream& out, const MaximumProductTripletData & data) {
    out << "MaximumProductTripletData [ input=[";
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

std::istream& operator>>(std::istream& in, MaximumProductTripletData &data) {
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
        in.get(); // read the '{' character
        skipSpace(in);

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

            skipSpace(in);
        } // while
        in.get(); // read '}' character
        skipSpace(in);

        return in;
    } // if

    throw std::runtime_error("Invalid input format");
}

// Test Fixture Class
class MaximumProductTripletFixture :
    public testing::TestWithParam<MaximumProductTripletData> {
};

// Parameterized Test Definition
TEST_P(MaximumProductTripletFixture, MaximumProductTripletTests) {
    MaximumProductTripletData data = GetParam();

    Solution solution;

    std::vector<int> actual = solution.findTriplet(data.get_input());

    ASSERT_THAT(actual, ::testing::AnyOfArray(data.get_expected()));
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(MaximumProductTripletTests, MaximumProductTripletFixture, testing::ValuesIn(
    Loader<MaximumProductTripletData>()(find_path("arrays/data/maximum_product_triplet.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
