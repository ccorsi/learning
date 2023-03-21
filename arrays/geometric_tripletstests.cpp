/**
 * @file geometric_tripletstests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains tests to the problem https://www.techiedelight.com/?problem=GeometricTriplets
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
#include "geometric_triplets.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::utils;
using namespace valhalla::arrays::geometric_triplets;

// Test Fixture Data Class
class GeometricTripletsData {
    std::vector<int> m_input;
    std::set<std::vector<int>> m_expected;
public:
    GeometricTripletsData() = default;

    std::vector<int> const & get_input() { return m_input; }
    std::set<std::vector<int>> const & get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const GeometricTripletsData &);
    friend std::istream& operator>>(std::istream&, GeometricTripletsData &);

};

std::ostream& operator<<(std::ostream& out, const GeometricTripletsData & data) {
    out << "GeometricTripletsData [ input=[";
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

std::istream& operator>>(std::istream& in, GeometricTripletsData &data) {
    ::loaders::vectors::vectorLoader<
        int,
        std::vector<int>,
        char,
        ::checkers::is_space_or<','>
    > inputLoader(data.m_input, '[', ']');
    in >> inputLoader;

    ::checkers::skip_spaces<char,::checkers::is_space_or<','>> skipSpaces;

    skipSpaces(in);

    if (static_cast<char>(in.peek()) == '{') {
        in.get(); // read '{' character
        skipSpaces(in);

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
        } // while

        in.get(); // read '}' character
        skipSpaces(in);

        return in;
    } // if

    throw std::runtime_error("Invalid input format");
}

// Test Fixture Class
class GeometricTripletsFixture :
    public testing::TestWithParam<GeometricTripletsData> {
};

// Parameterized Test Definition
TEST_P(GeometricTripletsFixture, GeometricTripletsTests) {
    GeometricTripletsData data = GetParam();

    Solution solution;

    std::set<std::vector<int>> actual = solution.findTriplets(data.get_input());

    ASSERT_EQ(actual, data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(GeometricTripletsTests, GeometricTripletsFixture, testing::ValuesIn(
    Loader<GeometricTripletsData>()(find_path("arrays/data/geometric_triplets.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
