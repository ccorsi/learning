/**
 * @file three_sumtests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains tests to the problem https://www.techiedelight.com/?problem=3Sum
 * @version 0.1
 * @date 2023-03-18
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
#include "three_sum.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::utils;
using namespace valhalla::arrays::three_sum;

// Test Fixture Data Class
class ThreeSumData {
    std::vector<int> m_input;
    std::set<std::vector<int>> m_expected;
public:
    ThreeSumData() = default;

    std::vector<int> const & get_input() { return m_input; }
    std::set<std::vector<int>> const & get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const ThreeSumData &);
    friend std::istream& operator>>(std::istream&, ThreeSumData &);

};

std::ostream& operator<<(std::ostream& out, const ThreeSumData & data) {
    out << "ThreeSumData [ input=[";
    for (int value : data.m_input)
        out << " " << value;
    out << " ] expected={";
    for(std::vector<int> values : data.m_expected) {
        out << " [";
        for (int value : values)
            out << " " << value;
        out << " ]";
    } // for
    out << " } ]";

    return out;
}

std::istream& operator>>(std::istream& in, ThreeSumData &data) {
    ::loaders::vectors::vectorLoader<
        int,
        std::vector<int>,
        char,
        ::checkers::is_space_or<','>
    > inputLoader(data.m_input, '[', ']');
    in >> inputLoader;

    ::checkers::is_space IsSpace;

    // skip spaces
    while (IsSpace(in.peek())) in.get();

    if (static_cast<char>(in.peek()) == '{') {
        in.get(); // read '{' character

        // skip spaces
        while (IsSpace(in.peek())) in.get();

        while (static_cast<char>(in.peek() != '}')) {
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
            while (IsSpace(in.peek())) in.get();

        } // while

        in.get(); // read the '}' character
        std::string line;
        std::getline(in, line); // read end of line

        return in;
    } // if

    throw std::runtime_error("Invalid input format");
}

// Test Fixture Class
class ThreeSumFixture :
    public testing::TestWithParam<ThreeSumData> {
};

// Parameterized Test Definition
TEST_P(ThreeSumFixture, ThreeSumTests) {
    ThreeSumData data = GetParam();

    Solution solution;

    std::vector<int> input(data.get_input());

    std::vector<int> actual = solution.findTriplets(input);

    ASSERT_THAT(actual, ::testing::AnyOfArray(data.get_expected()));
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(ThreeSumTests, ThreeSumFixture, testing::ValuesIn(
    Loader<ThreeSumData>()(find_path("arrays/data/three_sum.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
