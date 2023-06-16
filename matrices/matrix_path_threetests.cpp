/**
 * @file matrix_path_threetests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains tests to the problem https://www.techiedelight.com/?problem=MatrixPathIII
 * @version 0.1
 * @date 2023-06-16
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
#include "matrix_path_three.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::utils;
using namespace valhalla::matrices::matrix_path_three;

// Test Fixture Data Class
class MatrixPathThreeData {
    std::vector<std::vector<int>> m_input;
    std::pair<int,int> m_src, m_dest;
    int m_expected;
public:
    MatrixPathThreeData() = default;

    std::vector<std::vector<int>> const & get_input() { return m_input; }
    std::pair<int,int> const & get_src() { return m_src; }
    std::pair<int,int> const & get_dest() { return m_dest; }
    int get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const MatrixPathThreeData &);
    friend std::istream& operator>>(std::istream&, MatrixPathThreeData &);

};

std::ostream& operator<<(std::ostream& out, const MatrixPathThreeData & data) {
    out << "MatrixPathThreeData [ input=[";
    for (std::vector<int> values : data.m_input) {
        out << " [";
        for (int value : values) {
            out << " " << value;
        } // for
        out << " ]";
    } // for

    return out << " ] src=(" << data.m_src.first << "," << data.m_src.second << ") dest=("
        << data.m_dest.first << "," << data.m_dest.second << ") expected="
        << data.m_expected << " ]";
}


struct VectorReader {
    std::basic_istream<char> & operator()(std::basic_istream<char> & in, std::vector<int> & type, int state) {
        int entry;

        ::loaders::loader::v4::dataLoader<
        int,
        char,
        ::loader::v4::reader<int,char>,
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
        default:
            throw std::runtime_error("Invalid state");
     } // switch

     return in;
   }
};

std::istream& operator>>(std::istream& in, MatrixPathThreeData &data) {
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
      std::pair<int,int>,
      char,
      PairReader,
      2,
      ::checkers::is_character<char,'('>,
      ::checkers::is_character<char,')'>,
      ::checkers::is_space_or<','>
    > srcLoader(data.m_src);
    in >> srcLoader;

    ::loaders::loader::v4::dataLoader<
      std::pair<int,int>,
      char,
      PairReader,
      2,
      ::checkers::is_character<char,'('>,
      ::checkers::is_character<char,')'>,
      ::checkers::is_space_or<','>
    > destLoader(data.m_dest);
    in >> destLoader;

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
class MatrixPathThreeFixture :
    public testing::TestWithParam<MatrixPathThreeData> {
};

// Parameterized Test Definition
TEST_P(MatrixPathThreeFixture, MatrixPathThreeTests) {
    MatrixPathThreeData data = GetParam();

    Solution solution;

    int actual = solution.countPaths(data.get_input(), data.get_src(), data.get_dest());

    ASSERT_EQ(actual, data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(MatrixPathThreeTests, MatrixPathThreeFixture, testing::ValuesIn(
    Loader<MatrixPathThreeData>()(find_path("matrices/data/matrix_path_three.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
