/**
 * @file largest_rectangle_areatests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains tests to the problem https://www.techiedelight.com/?problem=LargestRectangleArea
 * @version 0.1
 * @date 2023-06-13
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
#include "largest_rectangle_area.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::utils;
using namespace valhalla::matrices::largest_rectangle_area;

// Test Fixture Data Class
class LargestRectangleAreaData {
    std::vector<std::vector<int>> m_input;
    int m_expected;
public:
    LargestRectangleAreaData() = default;

    std::vector<std::vector<int>> const & get_input() { return m_input; }
    int get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const LargestRectangleAreaData &);
    friend std::istream& operator>>(std::istream&, LargestRectangleAreaData &);

};

std::ostream& operator<<(std::ostream& out, const LargestRectangleAreaData & data) {
    out << "LargestRectangleAreaData [ input=[";
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

struct VectorReader {
  std::basic_istream<char> & operator()(std::basic_istream<char> & in, std::vector<int> & vec, int state) {
     int value;

     ::loaders::loader::v4::dataLoader<
       int,
       char,
       ::loaders::loader::v4::reader<int,char>,
       1,
       ::checkers::is_character_noop<char>,
       ::checkers::is_no_character<char>,
       ::checkers::is_space_or<','>
     > valueLoader(value);
     in >> valueLoader;

     vec.push_back(value);

     return in;
   }
};

struct VectorVectorReader {
  std::basic_istream<char> & operator()(std::basic_istream<char> & in, std::vector<std::vector<int>> & vecvec, int state) {
     std::vector<int> vec;

     ::loaders::loader::v4::dataLoader<
       std::vector<int>,
       char,
       VectorReader,
       1,
       ::checkers::is_character<char, '['>,
       ::checkers::is_character<char, ']'>,
       ::checkers::is_space_or<','>
     > vectorLoader(vec);
     in >> vectorLoader;

     vecvec.push_back(vec);

     return in;
   }
};

std::istream& operator>>(std::istream& in, LargestRectangleAreaData &data) {

    ::loaders::loader::v4::dataLoader<
      std::vector<std::vector<int>>,
      char,
      VectorVectorReader,
      1,
      ::checkers::is_character<char, '['>,
      ::checkers::is_character<char, ']'>,
      ::checkers::is_space_or<','>
    > inputLoader(data.m_input);
    in >> inputLoader;

    ::loaders::loader::v4::dataLoader<
      int,
      char,
      ::loaders::loader::v4::reader<int,char>,
      1,
      ::checkers::is_character_noop<char>,
      ::checkers::is_no_character<char>,
      ::checkers::is_space_or<','>
    > expectedLoader(data.m_expected);
    in >> expectedLoader;

    return in;
}

// Test Fixture Class
class LargestRectangleAreaFixture :
    public testing::TestWithParam<LargestRectangleAreaData> {
};

// Parameterized Test Definition
TEST_P(LargestRectangleAreaFixture, LargestRectangleAreaTests) {
    LargestRectangleAreaData data = GetParam();

    Solution solution;

    std::vector<std::vector<int>> input = data.get_input();

    int actual = solution.findLargestRectangleArea(input);

    ASSERT_EQ(actual, data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(LargestRectangleAreaTests, LargestRectangleAreaFixture, testing::ValuesIn(
    Loader<LargestRectangleAreaData>()(find_path("matrices/data/largest_rectangle_area.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
