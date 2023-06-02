/**
 * @file largest_square_submatrixtests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains tests to the problem https://www.techiedelight.com/?problem=LargestSquareSubmatrix
 * @version 0.1
 * @date 2023-06-01
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
#include "largest_square_submatrix.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::utils;
using namespace valhalla::matrices::largest_square_submatrix;

// Test Fixture Data Class
class LargestSquareSubmatrixData {
    std::vector<std::vector<int>> m_input;
    int m_expected;
public:
    LargestSquareSubmatrixData() = default;

    std::vector<std::vector<int>> const & get_input() { return m_input; }
    int get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const LargestSquareSubmatrixData &);
    friend std::istream& operator>>(std::istream&, LargestSquareSubmatrixData &);

};

std::ostream& operator<<(std::ostream& out, const LargestSquareSubmatrixData & data) {
    out << "LargestSquareSubmatrixData [ input=[";
    for (std::vector<int> values : data.m_input) {
        out << " [";
        for (int value : values) {
            out << " " << value;
        } // for
        out << " ]";
    } // for
    out << " ] expected=" << data.m_expected << " ]";

    return out;
}

std::istream& operator>>(std::istream& in, LargestSquareSubmatrixData &data) {
    ::loaders::matrix::matrixLoader<
      int,
      std::vector<int>,
      std::vector<std::vector<int>>,
      char,
      ::checkers::is_space_or<','>
    > inputLoader(data.m_input, '[', ']');
    in >> inputLoader;

    ::checkers::skip_spaces<char, checkers::is_space_or<','>> skipSpaces;

    skipSpaces(in);

    in >> data.m_expected;

    skipSpaces(in);

    return in;
}

// Test Fixture Class
class LargestSquareSubmatrixFixture :
    public testing::TestWithParam<LargestSquareSubmatrixData> {
};

// Parameterized Test Definition
TEST_P(LargestSquareSubmatrixFixture, LargestSquareSubmatrixTests) {
    LargestSquareSubmatrixData data = GetParam();

    Solution solution;

    int actual = solution.findLargestSquareMatrix(data.get_input());

    ASSERT_EQ(actual, data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(LargestSquareSubmatrixTests, LargestSquareSubmatrixFixture, testing::ValuesIn(
    Loader<LargestSquareSubmatrixData>()(find_path("matrices/data/largest_square_submatrix.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
