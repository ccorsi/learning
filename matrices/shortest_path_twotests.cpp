/**
 * @file shortest_path_twotests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains tests to the problem https://www.techiedelight.com/?problem=ShortestPathII
 * @version 0.1
 * @date 2023-06-14
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
#include "shortest_path_two.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::utils;
using namespace valhalla::matrices::shortest_path_two;

// Test Fixture Data Class
class ShortestPathTwoData {
    std::vector<std::vector<int>> m_input;
    int m_expected;
public:
    ShortestPathTwoData() = default;

    std::vector<std::vector<int>> const & get_input() { return m_input; }
    int get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const ShortestPathTwoData &);
    friend std::istream& operator>>(std::istream&, ShortestPathTwoData &);

};

std::ostream& operator<<(std::ostream& out, const ShortestPathTwoData & data) {
    out << "ShortestPathTwoData [ input=[";
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
  std::basic_istream<char> & operator()(std::basic_istream<char> & in, std::vector<int> & type, int state) {
     int entry;

     ::loaders::loader::v4::dataLoader<
       int,
       char,
       ::loaders::loader::v4::reader<int,char>,
       1,
       ::checkers::is_character_noop<char>,
       ::checkers::is_no_character<char>,
       ::checkers::is_space_or<','>
     > inputLoader(entry);
     in >> inputLoader;

     type.push_back(entry);

     return in;
   }
};

struct VectorVectorReader {
  std::basic_istream<char> & operator()(std::basic_istream<char> & in, std::vector<std::vector<int>> & type, int state) {
     std::vector<int> entry;

     ::loaders::loader::v4::dataLoader<
       std::vector<int>,
       char,
       VectorReader,
       1,
       ::checkers::is_character<char,'['>,
       ::checkers::is_character<char,']'>,
       ::checkers::is_space_or<','>
     > entryLoader(entry);
     in >> entryLoader;

     type.push_back(entry);

     return in;
   }
};

std::istream& operator>>(std::istream& in, ShortestPathTwoData &data) {
    ::loaders::loader::v4::dataLoader<
      std::vector<std::vector<int>>,
      char,
      VectorVectorReader,
      1,
      ::checkers::is_character<char,'['>,
      ::checkers::is_character<char,']'>,
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
class ShortestPathTwoFixture :
    public testing::TestWithParam<ShortestPathTwoData> {
};

// Parameterized Test Definition
TEST_P(ShortestPathTwoFixture, ShortestPathTwoTests) {
    ShortestPathTwoData data = GetParam();

    Solution solution;

    std::vector<std::vector<int>> input = data.get_input();

    int actual = solution.findShortestDistance(input);

    ASSERT_EQ(actual, data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(ShortestPathTwoTests, ShortestPathTwoFixture, testing::ValuesIn(
    Loader<ShortestPathTwoData>()(find_path("matrices/data/shortest_path_two.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
