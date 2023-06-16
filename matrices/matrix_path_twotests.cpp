/**
 * @file matrix_path_twotests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains tests to the problem https://www.techiedelight.com/?problem=MatrixPathII
 * @version 0.1
 * @date 2023-06-16
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */
#include <iostream>
#include <set>

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "paths.h"
#include "loaders.h"
#include "matrix_path_two.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::utils;
using namespace valhalla::matrices::matrix_path_two;

// Test Fixture Data Class
class MatrixPathTwoData {
    std::vector<std::vector<int>> m_input;
    std::set<std::vector<std::pair<int,int>>> m_expected;
public:
    MatrixPathTwoData() = default;

    std::vector<std::vector<int>> const & get_input() { return m_input; }
    std::set<std::vector<std::pair<int,int>>> const & get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const MatrixPathTwoData &);
    friend std::istream& operator>>(std::istream&, MatrixPathTwoData &);

};

std::ostream& operator<<(std::ostream& out, const MatrixPathTwoData & data) {
    out << "MatrixPathTwoData [ input=[";
    for (std::vector<int> values : data.m_input) {
        out << " [";
        for (int value : values) {
            out << " " << value;
        } // for
        out << " ]";
    } // for
    out << " ] expected={";
    for (std::vector<std::pair<int,int>> values : data.m_expected) {
        out << " [";
        for (std::pair<int,int> value : values) {
            out << " (" << value.first << "," <<  value.second << ")";
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

struct PairReader {
    std::basic_istream<char> & operator()(std::basic_istream<char> & in, std::pair<int,int> & type, int state) {
        switch(state) {
            case 0:
                in >> type.first;
                break;
            case 1:
                in >> type.second;
                break;
        } // switch

        return in;
    }
};

struct VectorPairReader {
  std::basic_istream<char> & operator()(std::basic_istream<char> & in, std::vector<std::pair<int,int>> & type, int state) {
     std::pair<int,int> entry;

     ::loaders::loader::v4::dataLoader<
       std::pair<int,int>,
       char,
       PairReader,
       2,
       ::checkers::is_character<char,'('>,
       ::checkers::is_character<char,')'>,
       ::checkers::is_space_or<','>
     > inputLoader(entry);
     in >> inputLoader;

     type.push_back(entry);

     return in;
   }
};

struct SetVectorPairReader {
  std::basic_istream<char> & operator()(std::basic_istream<char> & in, std::set<std::vector<std::pair<int,int>>> & type, int state) {
        std::vector<std::pair<int,int>> entry;

        ::loaders::loader::v4::dataLoader<
            std::vector<std::pair<int,int>>,
            char,
            VectorPairReader,
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

std::istream& operator>>(std::istream& in, MatrixPathTwoData &data) {
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
      std::set<std::vector<std::pair<int,int>>>,
      char,
      SetVectorPairReader,
      1,
      ::checkers::is_character<char,'{'>,
      ::checkers::is_character<char,'}'>,
      ::checkers::is_space_or<','>
    > expectedLoader(data.m_expected);
    in >> expectedLoader;

    return in;
}

// Test Fixture Class
class MatrixPathTwoFixture :
    public testing::TestWithParam<MatrixPathTwoData> {
};

// Parameterized Test Definition
TEST_P(MatrixPathTwoFixture, MatrixPathTwoTests) {
    MatrixPathTwoData data = GetParam();

    Solution solution;

    std::vector<std::pair<int,int>> actual = solution.findPath(data.get_input());

    ASSERT_THAT(actual, testing::AnyOfArray(data.get_expected()));
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(MatrixPathTwoTests, MatrixPathTwoFixture, testing::ValuesIn(
    Loader<MatrixPathTwoData>()(find_path("matrices/data/matrix_path_two.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
