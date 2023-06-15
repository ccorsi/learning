/**
 * @file matrix_pathtests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains tests to the problem https://www.techiedelight.com/?problem=MatrixPath
 * @version 0.1
 * @date 2023-06-15
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
#include "matrix_path.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::utils;
using namespace valhalla::matrices::matrix_path;

// Test Fixture Data Class
class MatrixPathData {
    std::vector<std::vector<int>> m_input;
    std::set<std::vector<int>> m_expected;
public:
    MatrixPathData() = default;

    std::vector<std::vector<int>> const & get_input() { return m_input; }
    std::set<std::vector<int>> const & get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const MatrixPathData &);
    friend std::istream& operator>>(std::istream&, MatrixPathData &);

};

std::ostream& operator<<(std::ostream& out, const MatrixPathData & data) {
    out << "MatrixPathData [ input=[";
    for (std::vector<int> values : data.m_input) {
        out << " [";
        for (int value : values) {
            out << " " << value;
        } // for
        out << " ]";
    } // for
    out << " ] expected={";
    for (std::vector<int> values : data.m_expected) {
        out << " [";
        for (int value : values) {
            out << " " << value;
        } // for
        out << " ]";
    } // for
    out << " } ]";

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
     > inputLoader(entry);
     in >> inputLoader;

     type.push_back(entry);

     return in;
   }
};

struct SetVectorReader {
  std::basic_istream<char> & operator()(std::basic_istream<char> & in, std::set<std::vector<int>> & type, int state) {
     std::vector<int> entry;

     ::loaders::loader::v4::dataLoader<
       std::vector<int>,
       char,
       VectorReader,
       1,
       ::checkers::is_character<char,'['>,
       ::checkers::is_character<char,']'>,
       ::checkers::is_space_or<','>
     > inputLoader(entry);
     in >> inputLoader;

     type.insert(entry);

     return in;
   }
};

std::istream& operator>>(std::istream& in, MatrixPathData &data) {
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
      std::set<std::vector<int>>,
      char,
      SetVectorReader,
      1,
      ::checkers::is_character<char,'{'>,
      ::checkers::is_character<char,'}'>,
      ::checkers::is_space_or<','>
    > expectedLoader(data.m_expected);
    in >> expectedLoader;

    return in;
}

// Test Fixture Class
class MatrixPathFixture :
    public testing::TestWithParam<MatrixPathData> {
};

// Parameterized Test Definition
TEST_P(MatrixPathFixture, MatrixPathTests) {
    MatrixPathData data = GetParam();

    Solution solution;

    std::set<std::vector<int>> actual = solution.findAllPaths(data.get_input());

    ASSERT_EQ(actual, data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(MatrixPathTests, MatrixPathFixture, testing::ValuesIn(
    Loader<MatrixPathData>()(find_path("matrices/data/matrix_path.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
